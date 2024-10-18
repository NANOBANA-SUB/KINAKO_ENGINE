#include "../include/Render.h"
#include <GL/include/glew.h>
#include <GL/include/

const int MAX_NUM_SHAPES = 128;

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

void Render::renderActor(PxRigidActor* actor, bool shadows)
{
    // 影計算用行列
    const PxVec3 shadowDir(0.0f, -0.7071067f, -0.7071067f);
    const PxReal shadowMat[] = { 1, 0, 0, 0, -shadowDir.x / shadowDir.y, 0, -shadowDir.z / shadowDir.y, 0, 0, 0, 1, 0, 0, 0, 0, 1 };

    PxShape* shapes[MAX_NUM_SHAPES];
    const PxU32 numShapes = actor->getNbShapes();

    // シェイプの数を取得
    actor->getShapes(shapes, numShapes);

    // シェイプごとに描画
    for A(PxU32 i = 0; i < numShapes; i++)
    {
        // シェイプのポーズを取得
        const PxMat44 shapePose(PxShapeExt::getGlobalPose(*shapes[i], *actor));
        const PxGeometryHolder geomHolder = shapes[i]->getGeometry();

        // シェイプの種類に応じたレンダリング処理
        glPushMatrix();
        glMultMatrixf(&shapePose.column0.x);

        // シェイプの色設定(とりあえず、固定色)
        glColor3f(0.8f, 0.7f, 0.5f, 1.0f);

        // シェイプのジオメトリを描画
        switch (geomHolder.getType())
        {
        case PxGeometryType::eBOX:
            break;
        
        default:
            break;
        }

        glPopMatrix()
    }
}

void Render::RenderBox(const PxBoxGeometry& boxGem)
{
    const PxVec3 halfExtents = boxGem.halfExtents;
    glScalef(halfExtents.x * 2, halfExtents.y * 2, halfExtents.z * 2);
}