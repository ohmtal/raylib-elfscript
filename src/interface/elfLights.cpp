//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "console/engineAPI.h"
#include "raylib.h"
#include "ConsoleTypes.h"
#include "elfResource.h"

#define RLIGHTS_IMPLEMENTATION
#include "rayspice/rlights.h"

static S32 gLightsCount = 0;

class LightObject : public SimObject
{
    typedef SimObject Parent;
public:
    DECLARE_CONOBJECT(LightObject);

    Light mLight = { 0 };
    S32 mShaderId = 0;;

    bool onAdd() override ;
    void onRemove() override;

    static void initPersistFields()
    {
        addField("shaderId", TypeS32, Offset(mShaderId, LightObject), "Id of the shader object");
        addField("type", TypeS32, Offset(mLight.type, LightObject), "Type of Light:LIGHT_DIRECTIONAL=0 LIGHT_POINT=1");
        addField("enabled", TypeBool, Offset(mLight.enabled, LightObject), "is enabled");
        addField("position", TypeVector3, Offset(mLight.position, LightObject), "position of the light");
        addField("target", TypeVector3, Offset(mLight.target, LightObject), "target of the light");
        addField("color", TypeColor,  Offset(mLight.color, LightObject), "color of the light");
        addField("attenuation", TypeF32,  Offset(mLight.attenuation, LightObject), "attenuation of the light");

    }

};
IMPLEMENT_CONOBJECT(LightObject);
// -----------------------------------------------------------------------------
bool LightObject::onAdd() {
    if (!Parent::onAdd() || gLightsCount >= MAX_LIGHTS) return false;
    Shader* shader = ElfResource::ShadersMap.get(mShaderId);
    if (!shader) return false;


    // NOTE: Lighting shader naming must be the provided ones
    mLight.enabledLoc = GetShaderLocation(*shader, TextFormat("lights[%i].enabled", gLightsCount));
    mLight.typeLoc = GetShaderLocation(*shader, TextFormat("lights[%i].type", gLightsCount));
    mLight.positionLoc = GetShaderLocation(*shader, TextFormat("lights[%i].position", gLightsCount));
    mLight.targetLoc = GetShaderLocation(*shader, TextFormat("lights[%i].target", gLightsCount));
    mLight.colorLoc = GetShaderLocation(*shader, TextFormat("lights[%i].color", gLightsCount));

    UpdateLightValues(*shader, mLight);

    gLightsCount++;

    return true;
}

// -----------------------------------------------------------------------------
void LightObject::onRemove() {
    gLightsCount--;
    Parent::onRemove();
}
// -----------------------------------------------------------------------------
DefineEngineMethod(LightObject, update, bool, (), ,"Update the shader with the current values") {
    auto shader = ElfResource::ShadersMap.get(object->mShaderId);
    if (!shader) return false;
    UpdateLightValues(*shader, object->mLight);
    return true;
}
