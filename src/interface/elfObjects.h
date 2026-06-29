//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#pragma once
#include "raylib.h"
#include "ConsoleTypes.h"
#include "console/engineAPI.h"

//-----------------------------------------------------------------------------
// Camera2DObject
//-----------------------------------------------------------------------------
class Camera2DObject : public SimObject
{
    typedef SimObject Parent;

public:
    // Wir halten die echte Raylib-Struktur direkt im Objekt
    Camera2D mCamera;
    Camera2DObject()
    {
        mCamera.offset = Vector2{ 0.0f, 0.0f };
        mCamera.target = Vector2{ 0.0f, 0.0f };
        mCamera.rotation = 0.0f;
        mCamera.zoom = 1.0f;
    }
    DECLARE_CONOBJECT(Camera2DObject);
    static void initPersistFields()
    {
        Parent::initPersistFields();
        addField("offset",   TypeVector2, Offset(mCamera.offset, Camera2DObject), "Camera screen offset");
        addField("target",   TypeVector2, Offset(mCamera.target, Camera2DObject), "Camera world target");
        addField("rotation", TypeF32,     Offset(mCamera.rotation, Camera2DObject), "Camera rotation in degrees");
        addField("zoom",     TypeF32,     Offset(mCamera.zoom, Camera2DObject), "Camera zoom level");
    }
};
//-----------------------------------------------------------------------------
// Camera3DObject
//-----------------------------------------------------------------------------
class Camera3DObject : public SimObject
{
    typedef SimObject Parent;

public:

    Camera3D mCamera;

    Camera3DObject()
    {
        mCamera.position   = Vector3{ 0.0f, 10.0f, 10.0f };
        mCamera.target     = Vector3{ 0.0f, 0.0f, 0.0f };
        mCamera.up         = Vector3{ 0.0f, 1.0f, 0.0f }; // Y-Up is default
        mCamera.fovy       = 45.0f;
        mCamera.projection = CAMERA_PERSPECTIVE;
    }

    DECLARE_CONOBJECT(Camera3DObject);

    static void initPersistFields()
    {
        Parent::initPersistFields();
        addField("position",   TypeVector3, Offset(mCamera.position, Camera3DObject), "Camera position in world space");
        addField("target",     TypeVector3, Offset(mCamera.target, Camera3DObject), "Camera target point in world space");
        addField("up",         TypeVector3, Offset(mCamera.up, Camera3DObject), "Camera up vector (defines the orientation)");
        addField("fovy",       TypeF32,     Offset(mCamera.fovy, Camera3DObject), "Camera field-of-view aperture in Y (degrees) in perspective, or width in orthographic");
        addField("projection", TypeS32,     Offset(mCamera.projection, Camera3DObject), "Camera projection type (CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC)");
    }

};

//-----------------------------------------------------------------------------
// RenderTextureObject
//-----------------------------------------------------------------------------
class RenderTextureObject : public SimObject
{
    typedef SimObject Parent;

public:

    RenderTexture mRenderTexture;
    S32 mTextureId = 0;
    S32 mWidth = 0; //no default the script must set it!
    S32 mHeight = 0;

    // RenderTextureObject();
    // ~RenderTextureObject();

    DECLARE_CONOBJECT(RenderTextureObject);

    bool onAdd() override ;
    void onRemove() override;

    bool resize(S32 width, S32 height, bool copyContent = true, Color copyColor = WHITE); //resize ==> recreate!

    static void initPersistFields()
    {
        Parent::initPersistFields();
        addField("width", TypeS32, Offset(mWidth, RenderTextureObject), "Set the width of the RenderTexture");
        addField("height", TypeS32, Offset(mHeight, RenderTextureObject), "Set the width of the RenderTexture");
        addProtectedField("Texture", TypeS32, Offset(mTextureId, RenderTextureObject),
                          defaultProtectedNotSetFn,&defaultProtectedGetFn,
                          "get the Id of the Texture (readonly )");
    }

};
//-----------------------------------------------------------------------------
// TextureObject
//-----------------------------------------------------------------------------
// class TextureObject : public SimObject
// {
//     typedef SimObject Parent;
//
// public:
//     DECLARE_CONOBJECT(TextureObject);
// };

