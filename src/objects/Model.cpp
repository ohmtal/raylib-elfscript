//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Model
// [ ] TODO add SceneObjectStub  Class
// [ ] TODO add getRayCollision , maybe rename to rayCast
//-----------------------------------------------------------------------------

#include "console/engineAPI.h"
#include "interface/ConsoleTypes.h"
#include "raylib.h"
#include "raymath.h"
#include "math/mMathRand.h"
#include "interface/elfResource.h"
#include "console/simSet.h"

namespace ElfObjects {

class ModelObject : public SimGroup
{
    typedef SimGroup Parent;
public:
    DECLARE_CONOBJECT(ModelObject);

    Vector3 mPosition = { 0.0f, 0.0f, 0.0f };
    Vector3 mRotation = { 0.0f, 0.0f, 0.0f }; // rotation angle degree (X, Y, Z)
    Vector3 mScale = {1.0f, 1.0f, 1.0f};
    S32 mModelId = 0;

    static void initPersistFields() {
        addField("Position", TypeVector3, Offset(mPosition, ModelObject), "World position of the model.");
        addField("Rotation", TypeVector3, Offset(mRotation, ModelObject), "Rotation in degrees.");
        addField("Scale", TypeVector3, Offset(mScale, ModelObject), "Scale multiplier.");
        addField("ModelId", TypeS32, Offset(mModelId, ModelObject), "The script ID of the raylib model.");
        Parent::initPersistFields();
    }

    void draw(bool recursive = false);
};

IMPLEMENT_CONOBJECT(ModelObject);
//-----------------------------------------------------------------------------
void ModelObject::draw(bool recursive) {
    if (mModelId <= 0) return;

    Model* baseModel = ElfResource::ModelMap.get(mModelId);
    if (!baseModel || baseModel->meshCount <= 0) return;

    Matrix oldTransform = baseModel->transform;

    Matrix matScale = MatrixScale(mScale.x, mScale.y, mScale.z);
    Matrix matRotX = MatrixRotateX(mRotation.x * DEG2RAD);
    Matrix matRotY = MatrixRotateY(mRotation.y * DEG2RAD);
    Matrix matRotZ = MatrixRotateZ(mRotation.z * DEG2RAD);
    Matrix matTrans = MatrixTranslate(mPosition.x, mPosition.y, mPosition.z);

    Matrix matRot = MatrixMultiply(MatrixMultiply(matRotX, matRotY), matRotZ);
    baseModel->transform = MatrixMultiply(MatrixMultiply(matScale, matRot), matTrans);

    ::DrawModel(*baseModel, Vector3{0.0f, 0.0f, 0.0f}, 1.0f, WHITE);

    baseModel->transform = oldTransform;

    // WARNING may end in endless loop.
    if (recursive) {
        lock();
        SimSet::iterator itr;
        for(itr = begin(); itr != end(); itr++)
        {
            SimObject *obj = *itr;
            if (obj == NULL) continue;
            ModelObject* child = dynamic_cast<ModelObject *>(obj);
            if (child != nullptr) {
                child->draw(true);
            }
        }
        unlock();
    }

}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

DefineEngineMethod(ModelObject, draw, void, (bool recursive),(false) ,
    "Draws this object instance using its assigned model."
    "@param recursive draw it's childs and their childs if any "
) {
    object->draw(recursive);
}

} //namespace
