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


#ifndef NVBLASTEXTSCOPEDRESOURCE_H
#define NVBLASTEXTSCOPEDRESOURCE_H

#include <PxAssert.h>


#pragma warning(push)
#pragma warning(disable:4512)

namespace nvidia
{
namespace apex
{
class ApexSDK;
class Asset;
class DestructibleAsset;
class AssetAuthoring;
class ModuleDestructible;
class RenderMeshAssetAuthoring;
class DestructibleAssetAuthoring;
}
}

namespace Nv
{
namespace Blast
{

namespace ApexImporter
{

template <class T>
class DefaultReleaser
{
public:
	DefaultReleaser() { }
	PX_INLINE void release(T& t) { t.release(); }
};

class ApexReleaser
{
public:
	ApexReleaser() : mApex(nullptr) { }
	ApexReleaser(nvidia::apex::ApexSDK& apex) : mApex(&apex) { }

	void	release(nvidia::apex::RenderMeshAssetAuthoring&);
	void	release(nvidia::apex::DestructibleAssetAuthoring&);
	void	release(nvidia::apex::ModuleDestructible&);

protected:
	bool					mbValid;
	nvidia::apex::ApexSDK*	mApex;
};

template< class Releasable, class Releaser = DefaultReleaser<Releasable> >
class ScopedResource
{
public:
	ScopedResource()
		: mpReleasable(nullptr), mIsReleasable(true){}

	ScopedResource(Releasable* pReleasable, const Releaser& releaser)
		: mpReleasable(pReleasable),
		mReleaser(releaser), mIsReleasable(true) { }

	ScopedResource(Releasable* pReleasable, bool isReleasable = true)
		: mpReleasable(pReleasable), mIsReleasable(isReleasable) { }

	~ScopedResource()
	{
		destroy();
	}

	PX_INLINE operator bool() const
	{
		return (nullptr != mpReleasable);
	}

	PX_INLINE Releasable* get() const
	{
		return mpReleasable;
	}

	PX_INLINE Releasable* release()
	{
		Releasable* pReleasable = mpReleasable;
		mpReleasable = nullptr;
		return pReleasable;
	}

	PX_INLINE Releasable& operator* () const
	{
		PX_ASSERT(*this);
		return *mpReleasable;
	}

	PX_INLINE Releasable* operator-> () const
	{
		return mpReleasable;
	}

	PX_INLINE bool operator==(const ScopedResource& b) const
	{
		return mpReleasable == b.mpReleasable;
	}

	PX_INLINE bool operator!=(const ScopedResource& b) const
	{
		return !(*this == b);
	}

	PX_INLINE void reset(Releasable* pReleasable, bool isReleasable = true)
	{
		if (mpReleasable == pReleasable) return;
		destroy();
		mpReleasable = pReleasable;
		mIsReleasable = isReleasable;
	}

	PX_INLINE void reset(Releasable* pReleasable, const Releaser& releaser, bool isReleasable = true)
	{
		reset(pReleasable);
		mReleaser = releaser;
		mIsReleasable = isReleasable;
	}

private:

	void destroy()
	{
		if (*this && mIsReleasable)
			mReleaser.release(*mpReleasable);
	}

	ScopedResource(const ScopedResource&);
	ScopedResource& operator=(const ScopedResource&);

	Releasable*	mpReleasable;
	Releaser	mReleaser;
	bool		mIsReleasable;
};

} // namespace ApexImporter

} // namespace Blast
} // namespace Nv

#pragma warning(pop)

#endif // NVBLASTEXTSCOPEDRESOURCE_H
