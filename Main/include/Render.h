#pragma once
#include "Engine.h"
#include "PxTransform.h"
#include "PxPhysicsAPI.h"
#include <quill/Backend.h>
#include <quill/Frontend.h>

using namespace physx;

class Render
{
public:
    Render(Engine engine):mEngine(engine), mLogger(mEngine->GetLogger()) {}
    void Initialize();
    void setupColors();
    void setupLights();
    void renderActors(PxRigidActor** actors, const PxU32 numActors, bool shadows, const PxVec3& color);
    PX_FORCE_INLINE void renderGeometryHolder(const PxGeometryHolder& h);

private:
    Engine* mEngine;
    quill::Logger* mLogger;
};
