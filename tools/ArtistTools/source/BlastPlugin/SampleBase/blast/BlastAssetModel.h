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


#ifndef BLAST_ASSET_MODEL_H
#define BLAST_ASSET_MODEL_H

#include "BlastAsset.h"
#include "BlastModel.h"


namespace physx
{
class PxPhysics;
class PxCooking;
}

namespace Nv
{
namespace Blast
{
class TkFramework;
class ExtSerialization;
}
}


class BlastAssetModel : public BlastAsset
{
public:
	//////// ctor ////////

	BlastAssetModel(TkFramework& framework, PxPhysics& physics, PxCooking& cooking, ExtSerialization& serialization, Renderer& renderer, const char* modelName, const char* modelPath = NULL);
	BlastAssetModel(ExtPxAsset* pExtPxAsset, BlastModel* pBlastModel, Renderer& renderer);
	virtual ~BlastAssetModel();


	//////// data getters  ////////

	const BlastModel& getModel() const
	{
// Add By Lixu Begin
		return *m_model;
// Add By Lixu End
	}

private:
	//////// private internal data ////////

	BlastModelPtr	m_model;
};

#endif //BLAST_ASSET_MODEL_H