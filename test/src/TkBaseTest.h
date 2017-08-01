// This code contains NVIDIA Confidential Information and is disclosed to you
// under a form of NVIDIA software license agreement provided separately to you.
//
// Notice
// NVIDIA Corporation and its licensors retain all intellectual property and
// proprietary rights in and to this software and related documentation and
// any modifications thereto. Any use, reproduction, disclosure, or
// distribution of this software and related documentation without an express
// license agreement from NVIDIA Corporation is strictly prohibited.
//
// ALL NVIDIA DESIGN SPECIFICATIONS, CODE ARE PROVIDED "AS IS.". NVIDIA MAKES
// NO WARRANTIES, EXPRESSED, IMPLIED, STATUTORY, OR OTHERWISE WITH RESPECT TO
// THE MATERIALS, AND EXPRESSLY DISCLAIMS ALL IMPLIED WARRANTIES OF NONINFRINGEMENT,
// MERCHANTABILITY, AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Information and code furnished is believed to be accurate and reliable.
// However, NVIDIA Corporation assumes no responsibility for the consequences of use of such
// information or for any infringement of patents or other rights of third parties that may
// result from its use. No license is granted by implication or otherwise under any patent
// or patent rights of NVIDIA Corporation. Details are subject to change without notice.
// This code supersedes and replaces all information previously supplied.
// NVIDIA Corporation products are not authorized for use as critical
// components in life support devices or systems without express written approval of
// NVIDIA Corporation.
//
// Copyright (c) 2016-2017 NVIDIA Corporation. All rights reserved.


#ifndef TKBASETEST_H
#define TKBASETEST_H


#include "NvBlastTk.h"
#include "NvBlastTkActor.h"
#include "NvBlastPxCallbacks.h"

#include "BlastBaseTest.h"

#include "NvBlastExtDamageShaders.h"

#include "NvBlastIndexFns.h"
#include "NvBlastExtCustomProfiler.h"
#include "TestProfiler.h"
#include "NvBlastExtPxTask.h"

#include "PxCpuDispatcher.h"
#include "PxTask.h"
#include "PxFoundation.h"
#include "PxFoundationVersion.h"

#include <thread>
#include <algorithm>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <atomic>


#define USE_PHYSX_DISPATCHER 0

#if USE_PHYSX_DISPATCHER
#include "PxDefaultCpuDispatcher.h"
#endif


using namespace Nv::Blast;
using namespace physx;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//													Helpers
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

NV_INLINE void ExpectArrayMatch(TkObject** arr0, size_t size0, TkObject** arr1, size_t size1)
{
	EXPECT_TRUE(size0 == size1);
	std::set<TkObject*> set0(arr0, arr0 + size0);
	std::set<TkObject*> set1(arr1, arr1 + size1);
	EXPECT_TRUE(set0 == set1);
}

class TestCpuDispatcher : public physx::PxCpuDispatcher
{
	struct SharedContext
	{
		std::queue<PxBaseTask*>	workQueue;
		std::condition_variable cv;
		std::mutex mutex;
		std::atomic<bool> quit;
	};

	void submitTask(PxBaseTask& task) override
	{
		if (m_threads.size() > 0)
		{
			std::unique_lock<std::mutex> lk(m_context.mutex);
			m_context.workQueue.push(&task);
			lk.unlock();
			m_context.cv.notify_one();
		}
		else
		{
			TEST_ZONE_BEGIN(task.getName());
			task.run();
			TEST_ZONE_END(task.getName());
			task.release();
		}
	}

	uint32_t getWorkerCount() const override { return (uint32_t)m_threads.size(); }

	static void execute(SharedContext& context)
	{
		while (!context.quit)
		{
			std::unique_lock<std::mutex> lk(context.mutex);
			if (!context.workQueue.empty())
			{
				PxBaseTask& task = *context.workQueue.front();
				context.workQueue.pop();
				lk.unlock();
				TEST_ZONE_BEGIN(task.getName());
				task.run();
				TEST_ZONE_END(task.getName());
				task.release();
			}
			else
			{
				// shared variables must be modified under the mutex in order
				// to correctly publish the modification to the waiting thread
				context.cv.wait(lk, [&]{ return !context.workQueue.empty() || context.quit; });
			}
		}
	}

	SharedContext m_context;
	std::vector<std::thread> m_threads;

public:
	TestCpuDispatcher(uint32_t numWorkers)
	{
		m_context.quit = false;
		for (uint32_t i = 0; i < numWorkers; ++i)
		{
			m_threads.push_back(std::thread(execute, std::ref(m_context)));
		}
	}

	void release()
	{
		std::unique_lock<std::mutex> lk(m_context.mutex);
		m_context.quit = true;
		lk.unlock();
		m_context.cv.notify_all();
		for (std::thread& t : m_threads)
		{
			t.join();
		}
		delete this;
	}
};


struct CSParams
{
	CSParams(uint32_t axis_, float coord_) : axis(axis_), coord(coord_) {}
	uint32_t axis;
	float coord;
};

static void CubeSlicer(NvBlastFractureBuffers* outbuf, const NvBlastGraphShaderActor* actor, const NvBlastProgramParams* params)
{
	uint32_t bondFractureCount = 0;
	uint32_t bondFractureCountMax = outbuf->bondFractureCount;

	for (size_t i = 0; i < params->damageDescCount; ++i)
	{
		const CSParams& p = (reinterpret_cast<const CSParams*> (params->damageDescBuffer))[i];

		uint32_t currentNodeIndex = actor->firstGraphNodeIndex;
		while (!Nv::Blast::isInvalidIndex(currentNodeIndex))
		{
			for (uint32_t adj = actor->adjacencyPartition[currentNodeIndex]; adj < actor->adjacencyPartition[currentNodeIndex + 1]; ++adj)
			{
				if (currentNodeIndex < actor->adjacentNodeIndices[adj])
				{
					if (actor->assetBonds[actor->adjacentBondIndices[adj]].centroid[p.axis] == p.coord && bondFractureCount < bondFractureCountMax)
					{
						NvBlastBondFractureData& data = outbuf->bondFractures[bondFractureCount++];
						data.userdata = 0;
						data.nodeIndex0 = currentNodeIndex;
						data.nodeIndex1 = actor->adjacentNodeIndices[adj];
						data.health = 1.0f;
					}
				}
			}
			currentNodeIndex = actor->graphNodeIndexLinks[currentNodeIndex];
		}
	}

	outbuf->bondFractureCount = bondFractureCount;
	outbuf->chunkFractureCount = 0;

	//printf("slicer outcount %d\n", bondFractureCount);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//												TkBaseTest Class
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<int FailLevel, int Verbosity>
class TkBaseTest : public BlastBaseTest<FailLevel, Verbosity>
{
public:
	TkBaseTest() : m_cpuDispatcher(), m_taskman(nullptr), m_foundation(nullptr)
	{
	}

	virtual void SetUp() override
	{
		m_foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, NvBlastGetPxAllocatorCallback(), NvBlastGetPxErrorCallback());

		NvBlastProfilerSetCallback(&m_profiler);
		NvBlastProfilerSetDetail(Nv::Blast::ProfilerDetail::LOW);
		m_profiler.setPlatformEnabled(true);

#if USE_PHYSX_DISPATCHER
		PxU32 affinity[] = { 1, 2, 4, 8 };
		m_cpuDispatcher = PxDefaultCpuDispatcherCreate(4, affinity);
		m_cpuDispatcher->setRunProfiled(false);
#else
		m_cpuDispatcher = new TestCpuDispatcher(4);
#endif

		m_taskman = PxTaskManager::createTaskManager(NvBlastGetPxErrorCallback(), m_cpuDispatcher, nullptr);
		m_groupTM = ExtGroupTaskManager::create(*m_taskman);
	}

	virtual void TearDown() override
	{
		m_groupTM->release();
		m_cpuDispatcher->release();
		if (m_taskman) m_taskman->release();
		if (m_foundation) m_foundation->release();
	}
	
	void createFramework()
	{
		TkFramework* framework = NvBlastTkFrameworkCreate();
		EXPECT_TRUE(framework != nullptr);
		EXPECT_EQ(framework, NvBlastTkFrameworkGet());
	}

	void releaseFramework()
	{
		TkFramework* framework = NvBlastTkFrameworkGet();
		framework->release();
		EXPECT_TRUE(NvBlastTkFrameworkGet() == nullptr);
	}

	void createTestAssets(bool addInternalJoints = false)
	{
		const uint8_t cube1BondDescFlags_internalJoints[12] =
		{
			TkAssetDesc::NoFlags,
			TkAssetDesc::NoFlags,
			TkAssetDesc::NoFlags,
			TkAssetDesc::NoFlags,

			TkAssetDesc::NoFlags,
			TkAssetDesc::NoFlags,
			TkAssetDesc::NoFlags,
			TkAssetDesc::NoFlags,

			TkAssetDesc::BondJointed,
			TkAssetDesc::BondJointed,
			TkAssetDesc::BondJointed,
			TkAssetDesc::BondJointed
		};

		const uint32_t assetDescCount = sizeof(g_assetDescs) / sizeof(g_assetDescs[0]);
		TkFramework* framework = NvBlastTkFrameworkGet();
		for (uint32_t i = 0; i < assetDescCount; ++i)
		{
			TkAssetDesc desc;
			reinterpret_cast<NvBlastAssetDesc&>(desc) = g_assetDescs[i];
			desc.bondFlags = addInternalJoints ? cube1BondDescFlags_internalJoints : nullptr;
			testAssets.push_back(framework->createAsset(desc));
			EXPECT_TRUE(testAssets[i] != nullptr);
		}
	}

	TkAsset* createCubeAsset(size_t maxDepth, size_t width, int32_t supportDepth = -1, bool addInternalJoints = false)
	{
		TkFramework* framework = NvBlastTkFrameworkGet();
		GeneratorAsset cube;
		TkAssetDesc assetDesc;
		generateCube(cube, assetDesc, maxDepth, width, supportDepth);
		std::vector<uint8_t> bondFlags(assetDesc.bondCount);
		std::fill(bondFlags.begin(), bondFlags.end(), addInternalJoints ? 1 : 0);
		assetDesc.bondFlags = bondFlags.data();
		TkAsset* cubeAsset = framework->createAsset(assetDesc);
		testAssets.push_back(cubeAsset);
		return cubeAsset;
	}

	void releaseTestAssets()
	{
		for (uint32_t i = 0; i < testAssets.size(); ++i)
		{
			testAssets[i]->release();
		}
		testAssets.clear();
	}

	NvBlastExtRadialDamageDesc getRadialDamageDesc(float x, float y, float z, float minRadius = 10.0f, float maxRadius = 10.0f, float damage = 1.0f)
	{
		NvBlastExtRadialDamageDesc desc;
		desc.position[0] = x;
		desc.position[1] = y;
		desc.position[2] = z;

		desc.minRadius = minRadius;
		desc.maxRadius = maxRadius;
		desc.damage = damage;
		return desc;
	}

	NvBlastExtShearDamageDesc getShearDamageDesc(float x, float y, float z, float shearX = 1.0f, float shearY = 0.0f, float shearZ = 0.0f, float minRadius = 10.0f, float maxRadius = 10.0f, float damage = 1.0f)
	{
		NvBlastExtShearDamageDesc desc;
		desc.position[0] = x;
		desc.position[1] = y;
		desc.position[2] = z;

		desc.normal[0] = shearX;
		desc.normal[1] = shearY;
		desc.normal[2] = shearZ;

		desc.minRadius = minRadius;
		desc.maxRadius = maxRadius;
		desc.damage = damage;

		return desc;
	}

	static const NvBlastDamageProgram& getCubeSlicerProgram()
	{
		static NvBlastDamageProgram  program = { CubeSlicer, nullptr };
		return program;
	}

	static const NvBlastDamageProgram& getFalloffProgram()
	{
		static NvBlastDamageProgram program = { NvBlastExtFalloffGraphShader, NvBlastExtFalloffSubgraphShader };
		return program;
	}

	static const NvBlastDamageProgram& getShearProgram()
	{
		static NvBlastDamageProgram program = { NvBlastExtShearGraphShader, NvBlastExtShearSubgraphShader };
		return program;
	}

	static const NvBlastExtMaterial* getDefaultMaterial()
	{
		static NvBlastExtMaterial material;
		return &material;
	};

	TkFamily* familySerialization(TkFamily* family);


	std::vector<TkAsset*> testAssets;

#if USE_PHYSX_DISPATCHER
	PxDefaultCpuDispatcher* m_cpuDispatcher;
#else
	TestCpuDispatcher*		m_cpuDispatcher;
#endif

	PxTaskManager*			m_taskman;
	PxFoundation*			m_foundation;

	ExtGroupTaskManager*	m_groupTM;
	ExtCustomProfiler		m_profiler;
};


#define TkPxErrorMask	(PxErrorCode::eINVALID_PARAMETER | PxErrorCode::eINVALID_OPERATION | PxErrorCode::eOUT_OF_MEMORY | PxErrorCode::eINTERNAL_ERROR | PxErrorCode::eABORT)
#define TkPxWarningMask	(PxErrorCode::eDEBUG_WARNING | PxErrorCode::ePERF_WARNING)

typedef TkBaseTest<NvBlastMessage::Error, 1> TkTestAllowWarnings;
typedef TkBaseTest<NvBlastMessage::Warning, 1> TkTestStrict;


class TestFamilyTracker : public TkEventListener
{
public:
	TestFamilyTracker() {}

	typedef std::pair<TkFamily*, uint32_t> Actor;

	virtual void receive(const TkEvent* events, uint32_t eventCount) override
	{
		TEST_ZONE_BEGIN("TestFamilyTracker");
		for (size_t i = 0; i < eventCount; ++i)
		{
			const TkEvent& e = events[i];
			switch (e.type)
			{
			case (TkEvent::Split):
			{
				const TkSplitEvent* splitEvent = e.getPayload<TkSplitEvent>();
				EXPECT_EQ((size_t)1, actors.erase(Actor(splitEvent->parentData.family, splitEvent->parentData.index)));
				for (size_t i = 0; i < splitEvent->numChildren; ++i)
				{
					TkActor* a = splitEvent->children[i];
					EXPECT_TRUE(actors.insert(Actor(&a->getFamily(), a->getIndex())).second);
				}
				break;
			}
			case (TkEvent::FractureCommand):
			{
				const TkFractureCommands* fracEvent = e.getPayload<TkFractureCommands>();
				EXPECT_TRUE(!isInvalidIndex(fracEvent->tkActorData.index));
#if 0
				printf("chunks broken: %d\n", fracEvent->buffers.chunkFractureCount);
				printf("bonds  broken: %d\n", fracEvent->buffers.bondFractureCount);
				for (uint32_t t = 0; t < fracEvent->buffers.bondFractureCount; t++)
				{
					//printf("%x ", fracEvent->buffers.bondFractures[t].userdata);
				}
				//printf("\n");
#endif
				break;
			}
			case (TkEvent::FractureEvent):
			{
				const TkFractureEvents* fracEvent = e.getPayload<TkFractureEvents>();
				EXPECT_TRUE(!isInvalidIndex(fracEvent->tkActorData.index));
				break;
			}
			case (TkEvent::JointUpdate):
			{
				const TkJointUpdateEvent* jointEvent = e.getPayload<TkJointUpdateEvent>();
				TkJoint* joint = jointEvent->joint;
				EXPECT_TRUE(joint != nullptr);

				switch (jointEvent->subtype)
				{
				case TkJointUpdateEvent::External:
					EXPECT_TRUE(joints.end() == joints.find(joint));	// We should not have this joint yet
					joints.insert(joint);
					break;
				case TkJointUpdateEvent::Changed:
					break;
				case TkJointUpdateEvent::Unreferenced:
					EXPECT_EQ(1, joints.erase(joint));
					joint->release();
					break;
				}
				break;
			}
			default:
				break;
			}
		}
		TEST_ZONE_END("TestFamilyTracker");
	}

	void insertActor(const TkActor* actor)
	{
		actors.insert(TestFamilyTracker::Actor(&actor->getFamily(), actor->getIndex()));
	}
		
	void eraseActor(const TkActor* actor)
	{
		actors.erase(TestFamilyTracker::Actor(&actor->getFamily(), actor->getIndex()));
	}

	std::set<Actor> actors;
	std::set<TkJoint*> joints;
};


#endif // #ifndef TKBASETEST_H
