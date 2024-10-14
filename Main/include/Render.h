#pragma once
#include "PxPhysicsAPI.h"

using namespace physx;

namespace Render
{
    void setupColors();
    void setupLights();
    void renderActors(PxRigidActor** actors, const PxU32 numActors, bool shadows, const PxVec3& color);
    PX_FORCE_INLINE void renderGeometryHolder(const PxGeometryHolder& h);
} // namespace Render
