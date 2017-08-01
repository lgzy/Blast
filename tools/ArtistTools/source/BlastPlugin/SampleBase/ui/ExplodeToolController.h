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
// Copyright (c) 2008-2017 NVIDIA Corporation. All rights reserved.


#ifndef EXPLODE_TOOL_CONTROLLER_H
#define EXPLODE_TOOL_CONTROLLER_H

#include "SampleManager.h"
#include "PxVec2.h"
#include "PxVec3.h"
#include "DebugRenderBuffer.h"
#include "BlastFamily.h"
#include "NvBlastExtPxManager.h"
#include "BlastSceneTree.h"

class Renderable;
class RenderMaterial;

namespace Nv
{
namespace Blast
{
class ExtPxActor;
}
}

namespace physx
{
	class PxScene;
}

class ExplodeToolController : public ISampleController
{
public:
	ExplodeToolController();
	virtual ~ExplodeToolController();

	virtual LRESULT MsgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual void Animate(double dt);
	void drawUI();

	virtual void onInitialize();
	virtual void onSampleStart();
	virtual void onSampleStop();

private:
	ExplodeToolController& operator= (ExplodeToolController&);

	//////// private methods ////////

	//////// used controllers ////////

	Renderer& getRenderer() const
	{
		return getManager()->getRenderer();
	}

	PhysXController& getPhysXController() const
	{
		return getManager()->getPhysXController();
	}

	BlastController& getBlastController() const
	{
		return getManager()->getBlastController();
	}

	void _explode(float value);
	//////// internal data ////////

	float m_previousExplodeValue;
	PxVec2 m_mouseStartPoint;
	bool m_starDrag;
};

#endif // EXPLODE_TOOL_CONTROLLER_H