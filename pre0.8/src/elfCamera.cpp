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
#include "rcamera.h"
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
// -----------------------------------------------------------------------------
//      ------------------ MODE3D and Camera3D --------------------------
// -----------------------------------------------------------------------------
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


DefineEngineMethod(Camera3DObject, Begin, void, (), , "BeginMode3D - Begins 3D mode with a Camera3DObject") {
    BeginMode3D(object->mCamera);
}

DefineEngineMethod(Camera3DObject, End, void, (),,"EndMode3D - End 3D mode with custom camera") {
    EndMode3D();
}

// ----- from rcamera.h

// RLAPI Vector3 GetCameraForward(Camera *camera);
DefineEngineMethod(Camera3DObject, getForwardVector, Vector3, (),
         , "GetCameraForward") {
    return ::GetCameraForward(&object->mCamera);
}

// RLAPI Vector3 GetCameraUp(Camera *camera);
DefineEngineMethod(Camera3DObject, getUpVector, Vector3, (),
         , "GetCameraUp") {
    return ::GetCameraUp(&object->mCamera);
}
// RLAPI Vector3 GetCameraRight(Camera *camera);
DefineEngineMethod(Camera3DObject, getRightVector, Vector3, (),
         , "GetCameraRight") {
    return ::GetCameraRight(&object->mCamera);
}

// RLAPI void CameraMoveForward(Camera *camera, float distance, bool moveInWorldPlane);
DefineEngineMethod(Camera3DObject, moveForward, void, (F32 distance, bool moveInWorldPlane), ,
                   "Moves the camera forward/backward based on distance. If moveInWorldPlane is true, movement is locked to the XZ plane.") {
    ::CameraMoveForward(&object->mCamera, distance, moveInWorldPlane);
}

// RLAPI void CameraMoveUp(Camera *camera, float distance);
DefineEngineMethod(Camera3DObject, moveUp, void, (F32 distance), ,
                   "Moves the camera up/down along its local up vector.") {
    ::CameraMoveUp(&object->mCamera, distance);
}

// RLAPI void CameraMoveRight(Camera *camera, float distance, bool moveInWorldPlane);
DefineEngineMethod(Camera3DObject, moveRight, void, (F32 distance, bool moveInWorldPlane), ,
                   "Moves the camera right/left based on distance. If moveInWorldPlane is true, movement is locked to the XZ plane.") {
    ::CameraMoveRight(&object->mCamera, distance, moveInWorldPlane);
}

// RLAPI void CameraMoveToTarget(Camera *camera, float delta);
DefineEngineMethod(Camera3DObject, moveToTarget, void, (F32 delta), ,
                   "Moves the camera closer or further away from its target point.") {
    ::CameraMoveToTarget(&object->mCamera, delta);
}

// RLAPI void CameraYaw(Camera *camera, float angle, bool rotateAroundTarget);
DefineEngineMethod(Camera3DObject, yaw, void, (F32 angle, bool rotateAroundTarget), ,
                   "Rotates the camera horizontally (yaw) around its own axis or around the target point (angle in radians).") {
    ::CameraYaw(&object->mCamera, angle, rotateAroundTarget);
}

// RLAPI void CameraPitch(Camera *camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp);
DefineEngineMethod(Camera3DObject, pitch, void, (F32 angle, bool lockView, bool rotateAroundTarget, bool rotateUp), ,
                   "Rotates the camera vertically (pitch) with optional view locking (angle in radians).") {
    ::CameraPitch(&object->mCamera, angle, lockView, rotateAroundTarget, rotateUp);
}

// RLAPI void CameraRoll(Camera *camera, float angle);
DefineEngineMethod(Camera3DObject, roll, void, (F32 angle), ,
                   "Tilts the camera (roll) along its view axis (angle in radians).") {
    ::CameraRoll(&object->mCamera, angle);
}

// RLAPI Matrix GetCameraViewMatrix(Camera *camera);
DefineEngineMethod(Camera3DObject, getViewMatrix, Matrix, (), ,
                   "Returns the camera's view matrix.") {
    return ::GetCameraViewMatrix(&object->mCamera);
}

// RLAPI Matrix GetCameraProjectionMatrix(Camera *camera, float aspect);
DefineEngineMethod(Camera3DObject, getProjectionMatrix, Matrix, (F32 aspect), ,
                   "Returns the camera's projection matrix based on the given aspect ratio.") {
    return ::GetCameraProjectionMatrix(&object->mCamera, aspect);
}



// ----------------- functions ------------------

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
