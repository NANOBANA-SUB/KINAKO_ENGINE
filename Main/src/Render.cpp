#include "../include/Render.h"
#include <GL/include/glew.h>

void Render::setupColors()
{
    glClearColor(0.1f, 0.0f, 0.25f, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glDepthFunc(GL_LEQUAL);
}

void Render::setupLights()
{
    glEnable(GL_LIGHTING);

        PxReal ambientColor[] = { 0.0f, 0.1f, 0.2f, 0.0f };
        PxReal diffuseColor[] = { 1.0f, 1.0f, 1.0f, 0.0f };
        PxReal specularColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        PxReal position[] = { 30.0f, 50.0f, -50.0f, 1.0f };
        
        glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
        glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
        glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHT0);
}

void Render::renderActors(PxRigidActor** actors, const PxU32 numActors, bool shadows, const PxVec3& color)
{
    const PxVec3 shadowDir(0.0f, -0.7071067f, -0.7071067f);
    const PxReal shadowMat[] = { 1, 0, 0, 0, -shadowDir.x / shadowDir.y, 0, -shadowDir.z / shadowDir.y, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

    PxShape* shapes[MAX_NUM_ACTOR_SHAPES];
}