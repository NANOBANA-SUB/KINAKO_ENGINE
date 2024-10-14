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