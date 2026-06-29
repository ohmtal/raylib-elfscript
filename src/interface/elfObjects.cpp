#include "elfObjects.h"
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
//-----------------------------------------------------------------------------
// RenderTextureObject
//-----------------------------------------------------------------------------
// * RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
// *  BeginTextureMode(target);
// *  EndTextureMode();


IMPLEMENT_CONOBJECT(RenderTextureObject);
//-----------------------------------------------------------------------------
bool RenderTextureObject::onAdd(){
    if (!Parent::onAdd() || mWidth <=0 || mHeight <=0) return false;
    mRenderTexture = LoadRenderTexture(mWidth, mHeight);
    if (!IsRenderTextureValid(mRenderTexture)) return false;

    mTextureId = ElfResource::TextureMap.add(mRenderTexture.texture);

    return true;
}
//-----------------------------------------------------------------------------
void RenderTextureObject::onRemove(){
    ElfResource::TextureMap.removeId(mTextureId);
    UnloadRenderTexture(mRenderTexture);
    Parent::onRemove();
}
//-----------------------------------------------------------------------------
bool RenderTextureObject::resize(S32 width, S32 height, bool copyContent, Color copyColor) {
     if (width <= 0 || height <= 0 ) return false;

    // 1. sav old data:
    S32 oldId = mTextureId;
    RenderTexture oldTexture = mRenderTexture;
    if (!IsRenderTextureValid(mRenderTexture)) {
        mRenderTexture = oldTexture;
        return false;
    }

    // 2. update size
    mWidth = width;
    mHeight = height;

    // 3. create new:
    mRenderTexture = LoadRenderTexture(mWidth, mHeight);
    if (!IsRenderTextureValid(mRenderTexture)) return false;
    mTextureId = ElfResource::TextureMap.add(mRenderTexture.texture);

    // 3. draw old content on the new texture;
    if (copyContent) {
        BeginTextureMode(mRenderTexture);
        ClearBackground(copyColor);

        Rectangle source = { 0, 0, (float)oldTexture.texture.width, -(float)oldTexture.texture.height };
        Rectangle dest = { 0, 0, (float)mWidth, (float)mHeight };
        Vector2 origin = { 0, 0 };

        DrawTexturePro(oldTexture.texture, source, dest, origin, 0.0f, WHITE);
        EndTextureMode();
    }

    // 4. remove old stuff
    ElfResource::TextureMap.removeId(oldId);
    UnloadRenderTexture(oldTexture);

    return true;
}

//-----------------------------------------------------------------------------
DefineEngineMethod(RenderTextureObject, Resize, bool
        , (S32 width,S32 height, bool copyImage, Color copyColor) , (true, WHITE)
        , "resize (recreate) a render texture") {
    return object->resize(width, height, copyImage, copyColor);
}

DefineEngineMethod(RenderTextureObject, BeginTextureMode, void, (), , "Begins drawing to render texture") {
    BeginTextureMode(object->mRenderTexture);
}
DefineEngineMethod(RenderTextureObject, EndTextureMode, void, (),, " End drawing to render texture") {
    EndTextureMode();
}
// //-----------------------------------------------------------------------------
// // TextureObject
// //-----------------------------------------------------------------------------
// IMPLEMENT_CONOBJECT(TextureObject);
