#include "elfObjects.h"
#include "math/mMathFn.h"
#include "ConsoleTypes.h"

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

// -------------------------------------------------------------------------------------------
// BatchRender
//
// -------------------------------------------------------------------------------------------
class BatchRender : public SimObject {
    typedef SimObject Parent;

public:
    // Flat memory layout holding Raylib Matrix structures
    Vector<Matrix> mElement;

    DECLARE_CONOBJECT(BatchRender);

    // Safely resize the internal Torque vector allocation
    void setBufferSize(S32 size) {
        // NOTE: Torque uses setSize() instead of resize() for its Vector
        mElement.setSize(size);
        dMemset(mElement.address(), 0, mElement.size() * sizeof(Matrix));
    }

    static bool _setBufferSize(void* obj,const char* , const char* data) {
        BatchRender* object = static_cast<BatchRender*>(obj);
        if (!object || !data) return false;
        S32 size = dAtoi(data);
        if ( size >= 0 ) {
          object->setBufferSize(size);
          //NOT! return true;
        }
        return false;
    }
    static const char *_getBufferSize(void* obj, const char* data) {
        BatchRender* object = static_cast<BatchRender*>(obj);
        if (!object) return "";
        return Con::getIntArg(object->mElement.size());
    }

    static void initPersistFields() {
        addProtectedField("count", TypeS32, 0, &_setBufferSize,&_getBufferSize, "Set the buffersize (element count).");
        Parent::initPersistFields();
    }

    // BATCH DRAW 1: Render circles using rectangle coordinates
    void drawCircles(S32 count, Color color) {
        S32 safeCount = getMin(count, mElement.size());
        for (S32 i = 0; i < safeCount; ++i) {
            DrawCircle(mElement[i].m0, mElement[i].m1, mElement[i].m2, color);
        }
    }

    // BATCH DRAW 2: Render solid rectangles directly
    void drawRects(S32 count, Color color) {
        S32 safeCount = getMin(count, mElement.size());
        for (S32 i = 0; i < safeCount; ++i) {
            // Passing the clean Rectangle structure directly to native Raylib
            DrawRectangleRec({mElement[i].m0, mElement[i].m1, mElement[i].m2, mElement[i].m3}, color);
        }
    }

    // BATCH DRAW 3: Render lines interpreting components as start/end vectors
    void drawLines(S32 count, Color color) {
        S32 safeCount = getMin(count, mElement.size());
        for (S32 i = 0; i < safeCount; ++i) {
            DrawLine(mElement[i].m0, mElement[i].m1, mElement[i].m2, mElement[i].m3, color);

        }
    }
};

IMPLEMENT_CONOBJECT(BatchRender);

// --- Console Method Bindings ---

DefineEngineMethod(BatchRender, setBufferSize, void, (S32 size),, "Resizes the internal buffers safely") {
    object->setBufferSize(size);
}



DefineEngineMethod(BatchRender, setVector2, void, (S32 index, F32 x, F32 y),
                   , "Sets data at a specific index") {
    if (index >= 0 && index < object->mElement.size()) {
        object->mElement[index].m0 = x;
        object->mElement[index].m1 = y;
    }
}
DefineEngineMethod(BatchRender, setVector2v, void, (S32 index, Vector2 vec),
                   , "Sets data at a specific index") {
    if (index >= 0 && index < object->mElement.size()) {
        object->mElement[index].m0 = vec.x;
        object->mElement[index].m1 = vec.y;
    }
}


DefineEngineMethod(BatchRender, setVector3, void, (S32 index, F32 x, F32 y, F32 z),
                   , "Sets data at a specific index") {
    if (index >= 0 && index < object->mElement.size()) {
        object->mElement[index].m0 = x;
        object->mElement[index].m1 = y;
        object->mElement[index].m2 = z;
    }
}

DefineEngineMethod(BatchRender, setVector4, void, (S32 index, F32 x, F32 y, F32 w, F32 h),
                   , "Sets data at a specific index") {
    if (index >= 0 && index < object->mElement.size()) {
        object->mElement[index].m0 = x;
        object->mElement[index].m1 = y;
        object->mElement[index].m2 = w;
        object->mElement[index].m3 = h;
    }
}

DefineEngineMethod(BatchRender, setVector4_1, void, (S32 index
,  F32 m4, F32 m5, F32 m6, F32 m7),
, "Sets data at a specific index") {
    if (index >= 0 && index < object->mElement.size()) {
        object->mElement[index].m4 = m4;
        object->mElement[index].m5 = m5;
        object->mElement[index].m6 = m6;
        object->mElement[index].m7 = m7;
    }
}
DefineEngineMethod(BatchRender, setVector4_2, void, (S32 index
    , F32 m8, F32 m9, F32 m10, F32 m11),
    , "Sets data at a specific index") {
    if (index >= 0 && index < object->mElement.size()) {
        object->mElement[index].m8 = m8;
        object->mElement[index].m9 = m9;
        object->mElement[index].m10 = m10;
        object->mElement[index].m11 = m11;
    }
}
DefineEngineMethod(BatchRender, setVector4_3, void, (S32 index
, F32 m12, F32 m13, F32 m14, F32 m15),
, "Sets data at a specific index") {
    if (index >= 0 && index < object->mElement.size()) {
        object->mElement[index].m12 = m12;
        object->mElement[index].m13 = m13;
        object->mElement[index].m14 = m14;
        object->mElement[index].m15 = m15;
    }
}


DefineEngineMethod(BatchRender, setVector8, void, (S32 index
, F32 m0, F32 m1, F32 m2, F32 m3, F32 m4, F32 m5, F32 m6, F32 m7),
, "Sets data at a specific index") {
    if (index >= 0 && index < object->mElement.size()) {
        object->mElement[index].m0 = m0;
        object->mElement[index].m1 = m1;
        object->mElement[index].m2 = m2;
        object->mElement[index].m3 = m3;
        object->mElement[index].m4 = m4;
        object->mElement[index].m5 = m5;
        object->mElement[index].m6 = m6;
        object->mElement[index].m7 = m7;
    }
}

DefineEngineMethod(BatchRender, getX, F32, (S32 index),, "Get x position by index") {
    return object->mElement[index].m0;
}

DefineEngineMethod(BatchRender, getY, F32, (S32 index),, "Get y position by index") {
    return object->mElement[index].m1;
}

// Purposefully mapping width to Z-depth for script-side math optimization
DefineEngineMethod(BatchRender, getZ, F32, (S32 index),, "Get z (width) by index") {
    return object->mElement[index].m2;
}

DefineEngineMethod(BatchRender, getW, F32, (S32 index),, "Get width by index") {
    return object->mElement[index].m2;
}

DefineEngineMethod(BatchRender, getH, F32, (S32 index),, "Get height by index") {
    return object->mElement[index].m3;
}

DefineEngineMethod(BatchRender, getVector2, Vector3, (S32 index),, "Get full Vector2 structure by index") {
    return { object->mElement[index].m0, object->mElement[index].m1 };
}

DefineEngineMethod(BatchRender, getVector3, Vector3, (S32 index),, "Get full Vector3 structure by index") {
    return { object->mElement[index].m0, object->mElement[index].m1, object->mElement[index].m2 };
}

DefineEngineMethod(BatchRender, getVector4, Vector4, (S32 index),, "Get Vector4 structure by index") {
   return { object->mElement[index].m0, object->mElement[index].m1, object->mElement[index].m2 , object->mElement[index].m3};
}

DefineEngineMethod(BatchRender, getVector4_1, Vector4, (S32 index),, "Get second Vector4 structure by index") {
    return { object->mElement[index].m4, object->mElement[index].m5, object->mElement[index].m6 , object->mElement[index].m7};
}
DefineEngineMethod(BatchRender, getVector4_2, Vector4, (S32 index),, "Get third Vector4 structure by index") {
    return { object->mElement[index].m8, object->mElement[index].m9, object->mElement[index].m10 , object->mElement[index].m11};
}
DefineEngineMethod(BatchRender, getVector4_3, Vector4, (S32 index),, "Get fourth Vector4 structure by index") {
    return { object->mElement[index].m12, object->mElement[index].m13, object->mElement[index].m14 , object->mElement[index].m15};
}

DefineEngineMethod(BatchRender, getMatrix, Matrix, (S32 index),, "Get the Matrix structure by index") {
    return object->mElement[index];
}


DefineEngineMethod(BatchRender, drawCircles, void, (S32 count, Color color),, "Batch draw circles using first Vector3 x,y,radius") {
    object->drawCircles(count, color);
}

DefineEngineMethod(BatchRender, drawRects, void, (S32 count, Color color),, "Batch draw rectangles using first Vector4 x,y,width,height") {
    object->drawRects(count, color);
}

DefineEngineMethod(BatchRender, drawLines, void, (S32 count, Color color),, "Batch draw lines using first Vector4 x1,y1,x2,y2") {
    object->drawLines(count, color);
}

// -------------------------------------------------------------------------------------
// set named global variables for x, y, z
DefineEngineMethod(BatchRender, getVector2GlobalV, void,
                   (S32 index, String varX, String varY),
                   , "Fetches X, Yto global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) Con::setFloatVariable(varX, object->mElement[index].m0);
        if (varY) Con::setFloatVariable(varY, object->mElement[index].m1);
    }
}

// this ? not DefineEngineMethod(BatchRender, feedVector2GlobalV, void,


// FIXME also the others ? --- guess not it's not that fast
DefineEngineMethod(BatchRender, setVector2GlobalV, void,
                   (S32 index, String varX, String varY),
                   , "Fetches X, Y FROM global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) object->mElement[index].m0 = Con::getFloatVariable(varX);
        if (varY) object->mElement[index].m1 = Con::getFloatVariable(varY);
    }
}

DefineEngineMethod(BatchRender, getVector3GlobalV, void,
                   (S32 index, String varX, String varY, String varW),
                   , "Fetches X, Y, Z to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) Con::setFloatVariable(varX, object->mElement[index].m0);
        if (varY) Con::setFloatVariable(varY, object->mElement[index].m1);
        if (varW) Con::setFloatVariable(varW, object->mElement[index].m2);
    }
}
DefineEngineMethod(BatchRender, getVector4GlobalV, void,
        (S32 index, String varX, String varY, String varW, String varH),
            , "Fetches X, Y, W, H to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) Con::setFloatVariable(varX, object->mElement[index].m0);
        if (varY) Con::setFloatVariable(varY, object->mElement[index].m1);
        if (varW) Con::setFloatVariable(varW, object->mElement[index].m2);
        if (varH) Con::setFloatVariable(varH, object->mElement[index].m3);
    }
}

DefineEngineMethod(BatchRender, setVector4GlobalV, void,
                   (S32 index, String varX, String varY, String varW, String varH),
                   , "Fetches X, Y, W, H to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) object->mElement[index].m0 = Con::getFloatVariable(varX);
        if (varY) object->mElement[index].m1 = Con::getFloatVariable(varY);
        if (varW) object->mElement[index].m2 = Con::getFloatVariable(varW);
        if (varH) object->mElement[index].m3 = Con::getFloatVariable(varH);

    }
}

DefineEngineMethod(BatchRender, getVector4_1GlobalV, void,
                   (S32 index, String varX, String varY, String varW, String varH),
                   , "Fetches X, Y, W, H to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) Con::setFloatVariable(varX, object->mElement[index].m4);
        if (varY) Con::setFloatVariable(varY, object->mElement[index].m5);
        if (varW) Con::setFloatVariable(varW, object->mElement[index].m6);
        if (varH) Con::setFloatVariable(varH, object->mElement[index].m7);
    }
}

DefineEngineMethod(BatchRender, setVector4_1GlobalV, void,
                   (S32 index, String varX, String varY, String varW, String varH),
                   , "Fetches X, Y, W, H to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) object->mElement[index].m4 = Con::getFloatVariable(varX);
        if (varY) object->mElement[index].m5 = Con::getFloatVariable(varY);
        if (varW) object->mElement[index].m6 = Con::getFloatVariable(varW);
        if (varH) object->mElement[index].m7 = Con::getFloatVariable(varH);

    }
}

DefineEngineMethod(BatchRender, getVector4_2GlobalV, void,
                   (S32 index, String varX, String varY, String varW, String varH),
                   , "Fetches X, Y, W, H to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) Con::setFloatVariable(varX, object->mElement[index].m8);
        if (varY) Con::setFloatVariable(varY, object->mElement[index].m9);
        if (varW) Con::setFloatVariable(varW, object->mElement[index].m10);
        if (varH) Con::setFloatVariable(varH, object->mElement[index].m11);
    }
}
DefineEngineMethod(BatchRender, setVector4_2GlobalV, void,
                   (S32 index, String varX, String varY, String varW, String varH),
                   , "Fetches X, Y, W, H to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) object->mElement[index].m8 = Con::getFloatVariable(varX);
        if (varY) object->mElement[index].m9 = Con::getFloatVariable(varY);
        if (varW) object->mElement[index].m10= Con::getFloatVariable(varW);
        if (varH) object->mElement[index].m11= Con::getFloatVariable(varH);

    }
}

DefineEngineMethod(BatchRender, getVector4_3GlobalV, void,
                   (S32 index, String varX, String varY, String varW, String varH),
                   , "Fetches X, Y, W, H to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) Con::setFloatVariable(varX, object->mElement[index].m12);
        if (varY) Con::setFloatVariable(varY, object->mElement[index].m13);
        if (varW) Con::setFloatVariable(varW, object->mElement[index].m14);
        if (varH) Con::setFloatVariable(varH, object->mElement[index].m15);
    }
}

DefineEngineMethod(BatchRender, setVector4_3GlobalV, void,
                   (S32 index, String varX, String varY, String varW, String varH),
                   , "Fetches X, Y, W, H to global variables named by parameters") {
    if (index >= 0 && index < object->mElement.size()) {
        if (varX) object->mElement[index].m12= Con::getFloatVariable(varX);
        if (varY) object->mElement[index].m13= Con::getFloatVariable(varY);
        if (varW) object->mElement[index].m14= Con::getFloatVariable(varW);
        if (varH) object->mElement[index].m15= Con::getFloatVariable(varH);

    }
}
// ================================================================================================
// prior version using rect

// class BatchRender : public SimObject {
//     typedef SimObject Parent;
//
// public:
//     // Flat memory layout holding Raylib Rectangle structures
//     Vector<Rectangle> mElement;
//
//     DECLARE_CONOBJECT(BatchRender);
//
//     // Safely resize the internal Torque vector allocation
//     void setBufferSize(S32 size) {
//         // NOTE: Torque uses setSize() instead of resize() for its Vector
//         mElement.setSize(size);
//     }
//
//     // Data streaming into the continuous array layout
//     void setElement(S32 index, F32 x, F32 y, F32 w, F32 h) {
//         if (index >= 0 && index < mElement.size()) {
//             mElement[index] = { x, y, w, h };
//         }
//     }
//
//     // BATCH DRAW 1: Render circles using rectangle coordinates
//     void drawCircles(S32 count, Color color) {
//         S32 safeCount = getMin(count, mElement.size());
//         for (S32 i = 0; i < safeCount; ++i) {
//             // Using x/y for screen coordinates, width component is used as radius
//             // Vector2 position = { mElement[i].x, mElement[i].y };
//             DrawCircle(mElement[i].x, mElement[i].y, mElement[i].width, color);
//         }
//     }
//
//     // BATCH DRAW 2: Render solid rectangles directly
//     void drawRects(S32 count, Color color) {
//         S32 safeCount = getMin(count, mElement.size());
//         for (S32 i = 0; i < safeCount; ++i) {
//             // Passing the clean Rectangle structure directly to native Raylib
//             DrawRectangleRec(mElement[i], color);
//         }
//     }
//
//     // BATCH DRAW 3: Render lines interpreting components as start/end vectors
//     void drawLines(S32 count, Color color) {
//         S32 safeCount = getMin(count, mElement.size());
//         for (S32 i = 0; i < safeCount; ++i) {
//             DrawLine(mElement[i].x, mElement[i].y, mElement[i].width, mElement[i].height, color);
//
//         }
//     }
// };
//
// IMPLEMENT_CONOBJECT(BatchRender);
//
// // --- Console Method Bindings ---
//
// DefineEngineMethod(BatchRender, setBufferSize, void, (S32 size),, "Resizes the internal buffers safely") {
//     object->setBufferSize(size);
// }
//
// DefineEngineMethod(BatchRender, setElement, void, (S32 index, F32 x, F32 y, F32 w, F32 h), (0.f, 0.f), "Sets data at a specific index") {
//     object->setElement(index, x, y, w, h);
// }
//
// DefineEngineMethod(BatchRender, getX, F32, (S32 index),, "Get x position by index") {
//     return object->mElement[index].x;
// }
//
// DefineEngineMethod(BatchRender, getY, F32, (S32 index),, "Get y position by index") {
//     return object->mElement[index].y;
// }
//
// // Purposefully mapping width to Z-depth for script-side math optimization
// DefineEngineMethod(BatchRender, getZ, F32, (S32 index),, "Get z (width) by index") {
//     return object->mElement[index].width;
// }
//
// DefineEngineMethod(BatchRender, getW, F32, (S32 index),, "Get width by index") {
//     return object->mElement[index].width;
// }
//
// DefineEngineMethod(BatchRender, getH, F32, (S32 index),, "Get height by index") {
//     return object->mElement[index].height;
// }
//
// DefineEngineMethod(BatchRender, getVector2, Vector3, (S32 index),, "Get full Vector2 structure by index") {
//     return { object->mElement[index].x, object->mElement[index].y };
// }
//
// DefineEngineMethod(BatchRender, getVector3, Vector3, (S32 index),, "Get full Vector3 structure by index") {
//     return { object->mElement[index].x, object->mElement[index].y, object->mElement[index].width };
// }
//
// DefineEngineMethod(BatchRender, getVector4, Rectangle, (S32 index),, "Get full Vector4 structure by index") {
//     return object->mElement[index];
// }
//
//
// DefineEngineMethod(BatchRender, drawCircles, void, (S32 count, Color color),, "Batch draw circles") {
//     object->drawCircles(count, color);
// }
//
// DefineEngineMethod(BatchRender, drawRects, void, (S32 count, Color color),, "Batch draw rectangles") {
//     object->drawRects(count, color);
// }
//
// DefineEngineMethod(BatchRender, drawLines, void, (S32 count, Color color),, "Batch draw lines") {
//     object->drawLines(count, color);
// }
//
// // -------------------------------------------------------------------------------------
// // set named global variables for x, y, z
// DefineEngineMethod(BatchRender, setVector2GlobalV, void,
//                    (S32 index, String varX, String varY),
//                    , "Fetches X, Yto global variables named by parameters") {
//     if (index >= 0 && index < object->mElement.size()) {
//         if (varX) Con::setFloatVariable(varX, object->mElement[index].x);
//         if (varY) Con::setFloatVariable(varY, object->mElement[index].y);
//     }
// }
// DefineEngineMethod(BatchRender, setVector3GlobalV, void,
//                    (S32 index, String varX, String varY, String varW),
//                    , "Fetches X, Y, Z to global variables named by parameters") {
//     if (index >= 0 && index < object->mElement.size()) {
//         if (varX) Con::setFloatVariable(varX, object->mElement[index].x);
//         if (varY) Con::setFloatVariable(varY, object->mElement[index].y);
//         if (varW) Con::setFloatVariable(varW, object->mElement[index].width);
//     }
// }
// DefineEngineMethod(BatchRender, setVector4GlobalV, void,
//         (S32 index, String varX, String varY, String varW, String varH),
//             , "Fetches X, Y, W, H to global variables named by parameters") {
//     if (index >= 0 && index < object->mElement.size()) {
//         if (varX) Con::setFloatVariable(varX, object->mElement[index].x);
//         if (varY) Con::setFloatVariable(varY, object->mElement[index].y);
//         if (varW) Con::setFloatVariable(varW, object->mElement[index].width);
//         if (varH) Con::setFloatVariable(varH, object->mElement[index].height);
//     }
// }
