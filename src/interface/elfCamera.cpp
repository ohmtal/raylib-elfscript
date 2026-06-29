//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Camera Objects
//-----------------------------------------------------------------------------
#include "elfCamera.h"
#include "math/mMathFn.h"
#include "ConsoleTypes.h"
#include "elfResource.h"
// ------------- MODE2D and Camera2D --------------------------
IMPLEMENT_CONOBJECT(Camera2DObject);

DefineEngineMethod(Camera2DObject, getWorldToScreen, Vector2, (Vector2 position), , "Get 2D screen space position for a 2D camera world space position") {
    return GetWorldToScreen2D(position, object->mCamera);
}

DefineEngineMethod(Camera2DObject, getScreenToWorld, Vector2, (Vector2 position), , "Get 2D world space position for a 2D camera screen space position (e.g. mouse to world)") {
    return GetScreenToWorld2D(position, object->mCamera);
}

DefineEngineMethod(Camera2DObject, getCameraMatrix, Matrix, (), , "Get the 2D camera transform matrix") {
    return GetCameraMatrix2D(object->mCamera);
}


DefineEngineFunction( BeginMode2D, void, (S32 cameraId), , "Begins 2D mode with a Camera2DObject object") {
    Camera2DObject* camObj = dynamic_cast<Camera2DObject*>(Sim::findObject(cameraId));
    if (!camObj) {
        Con::errorf("BeginMode2D: Invalid Camera2D object ID: %d", cameraId);
        return;
    }
    BeginMode2D(camObj->mCamera);
}

DefineEngineFunction(EndMode2D, void, (),,"End 2D mode with custom camera") {
    EndMode2D();
}
// ------------- MODE3D and Camera3D --------------------------
IMPLEMENT_CONOBJECT(Camera3DObject);

DefineEngineMethod(Camera3DObject, update, void, (int mode), , "Update camera position for selected mode (e.g. $CAMERA_FIRST_PERSON, $CAMERA_FREE)") {
    UpdateCamera(&object->mCamera, mode);
}

DefineEngineMethod(Camera3DObject, updatePro, void, (Vector3 movement, Vector3 rotation, float zoom), , "Update camera movement/rotation with pro parameters") {
    UpdateCameraPro(&object->mCamera, movement, rotation, zoom);
}

DefineEngineMethod(Camera3DObject, getScreenToWorldRay, Ray, (Vector2 position), , "Get a 3D ray trace from a screen position (e.g. mouse)") {
    return GetScreenToWorldRay(position, object->mCamera);
}

DefineEngineMethod(Camera3DObject, getScreenToWorldRayEx, Ray, (Vector2 position, int width, int height), , "Get a 3D ray trace from a screen position within a specific custom viewport size") {
    return GetScreenToWorldRayEx(position, object->mCamera, width, height);
}

DefineEngineMethod(Camera3DObject, getWorldToScreen, Vector2, (Vector3 position), , "Get 2D screen space position for a 3D world space position") {
    return GetWorldToScreen(position, object->mCamera);
}

DefineEngineMethod(Camera3DObject, getWorldToScreenEx, Vector2, (Vector3 position, int width, int height), , "Get 2D screen space position for a 3D world space position inside a specific custom viewport size") {
    return GetWorldToScreenEx(position, object->mCamera, width, height);
}

DefineEngineMethod(Camera3DObject, getCameraMatrix, Matrix, (), , "Get the 3D camera transform matrix (view matrix)") {
    return GetCameraMatrix(object->mCamera);
}


// RLAPI void BeginMode3D(Camera3D camera);
DefineEngineFunction( BeginMode3D, void, (S32 cameraId), , "Begins 3D mode with a Camera3DObject") {
    Camera3DObject* camObj = dynamic_cast<Camera3DObject*>(Sim::findObject(cameraId));
    if (!camObj) {
        Con::errorf("BeginMode3D: Invalid Camera3DObject ID: %d", cameraId);
        return;
    }
    BeginMode3D(camObj->mCamera);
}

DefineEngineFunction(EndMode3D, void, (),,"End 3D mode with custom camera") {
    EndMode3D();
}

// //-----------------------------------------------------------------------------
// // TextureObject
// //-----------------------------------------------------------------------------
// IMPLEMENT_CONOBJECT(TextureObject);
