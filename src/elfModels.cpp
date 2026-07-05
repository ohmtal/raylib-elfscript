//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfResource.h"
#include "ConsoleTypes.h"
#include "elfCamera.h"
#include "elfTools.h"

#include "console/console.h"
#include "console/engineAPI.h"

#include "raymath.h"

using namespace ElfResource;
using namespace ElfTools;
//------------------------------------------------------------------------------------
// Basic 3d Shapes Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// Basic geometric 3D shapes drawing functions
// RLAPI void DrawLine3D(Vector3 startPos, Vector3 endPos, Color color); // Draw a line in 3D world space
DefineEngineFunction( DrawLine3D, void, (Vector3 startPos, Vector3 endPos, Color color), , "Draw a line in 3D world space") {
    DrawLine3D(startPos, endPos, color);
}

// RLAPI void DrawPoint3D(Vector3 position, Color color); // Draw a point in 3D space, actually a small line
DefineEngineFunction( DrawPoint3D, void, (Vector3 position, Color color), , "Draw a point in 3D space, actually a small line") {
    DrawPoint3D(position, color);
}

// RLAPI void DrawCircle3D(Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color); // Draw a circle in 3D world space
DefineEngineFunction( DrawCircle3D, void, (Vector3 center, float radius, Vector3 rotationAxis, float rotationAngle, Color color), , "Draw a circle in 3D world space") {
    DrawCircle3D(center, radius, rotationAxis, rotationAngle, color);
}

// RLAPI void DrawTriangle3D(Vector3 v1, Vector3 v2, Vector3 v3, Color color); // Draw a color-filled triangle (vertex in counter-clockwise order!)
DefineEngineFunction( DrawTriangle3D, void, (Vector3 v1, Vector3 v2, Vector3 v3, Color color), , "Draw a color-filled triangle (vertex in counter-clockwise order!)") {
    DrawTriangle3D(v1, v2, v3, color);
}

// RLAPI void DrawTriangleStrip3D(const Vector3 *points, int pointCount, Color color); // Draw a triangle strip defined by points
DefineEngineFunction( DrawTriangleStrip3D, void, (Vector<F32> pointValues, int pointCount, Color color), , "Draw a triangle strip defined by points") {
    auto points = getVector3List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;
    DrawTriangleStrip3D(points.data(), pointCount, color);
}

// RLAPI void DrawCube(Vector3 position, float width, float height, float length, Color color); // Draw cube
DefineEngineFunction( DrawCube, void, (Vector3 position, float width, float height, float length, Color color), , "Draw cube") {
    DrawCube(position, width, height, length, color);
}

// RLAPI void DrawCubeV(Vector3 position, Vector3 size, Color color); // Draw cube (Vector version)
DefineEngineFunction( DrawCubeV, void, (Vector3 position, Vector3 size, Color color), , "Draw cube (Vector version)") {
    DrawCubeV(position, size, color);
}

// RLAPI void DrawCubeWires(Vector3 position, float width, float height, float length, Color color); // Draw cube wires
DefineEngineFunction( DrawCubeWires, void, (Vector3 position, float width, float height, float length, Color color), , "Draw cube wires") {
    DrawCubeWires(position, width, height, length, color);
}

// RLAPI void DrawCubeWiresV(Vector3 position, Vector3 size, Color color); // Draw cube wires (Vector version)
DefineEngineFunction( DrawCubeWiresV, void, (Vector3 position, Vector3 size, Color color), , "Draw cube wires (Vector version)") {
    DrawCubeWiresV(position, size, color);
}

// RLAPI void DrawSphere(Vector3 centerPos, float radius, Color color); // Draw sphere
DefineEngineFunction( DrawSphere, void, (Vector3 centerPos, float radius, Color color), , "Draw sphere") {
    DrawSphere(centerPos, radius, color);
}

// RLAPI void DrawSphereEx(Vector3 centerPos, float radius, int rings, int slices, Color color); // Draw sphere with extended parameters
DefineEngineFunction( DrawSphereEx, void, (Vector3 centerPos, float radius, int rings, int slices, Color color), , "Draw sphere with extended parameters") {
    DrawSphereEx(centerPos, radius, rings, slices, color);
}

// RLAPI void DrawSphereWires(Vector3 centerPos, float radius, int rings, int slices, Color color); // Draw sphere wires
DefineEngineFunction( DrawSphereWires, void, (Vector3 centerPos, float radius, int rings, int slices, Color color), , "Draw sphere wires") {
    DrawSphereWires(centerPos, radius, rings, slices, color);
}

// RLAPI void DrawCylinder(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); // Draw a cylinder/cone
DefineEngineFunction( DrawCylinder, void, (Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color), , "Draw a cylinder/cone") {
    DrawCylinder(position, radiusTop, radiusBottom, height, slices, color);
}

// RLAPI void DrawCylinderEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color); // Draw a cylinder with base at startPos and top at endPos
DefineEngineFunction( DrawCylinderEx, void, (Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int sides, Color color), , "Draw a cylinder with base at startPos and top at endPos") {
    DrawCylinderEx(startPos, endPos, startRadius, endRadius, sides, color);
}

// RLAPI void DrawCylinderWires(Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color); // Draw a cylinder/cone wires
DefineEngineFunction( DrawCylinderWires, void, (Vector3 position, float radiusTop, float radiusBottom, float height, int slices, Color color), , "Draw a cylinder/cone wires") {
    DrawCylinderWires(position, radiusTop, radiusBottom, height, slices, color);
}

// RLAPI void DrawCylinderWiresEx(Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int slices, Color color); // Draw a cylinder wires with base at startPos and top at endPos
DefineEngineFunction( DrawCylinderWiresEx, void, (Vector3 startPos, Vector3 endPos, float startRadius, float endRadius, int slices, Color color), , "Draw a cylinder wires with base at startPos and top at endPos") {
    DrawCylinderWiresEx(startPos, endPos, startRadius, endRadius, slices, color);
}

// RLAPI void DrawCapsule(Vector3 startPos, Vector3 endPos, float radius, int rings, int slices, Color color); // Draw a capsule
DefineEngineFunction( DrawCapsule, void, (Vector3 startPos, Vector3 endPos, float radius, int rings, int slices, Color color), , "Draw a capsule with the center of its sphere caps at startPos and endPos") {
    DrawCapsule(startPos, endPos, radius, rings, slices, color);
}

// RLAPI void DrawCapsuleWires(Vector3 startPos, Vector3 endPos, float radius, int rings, int slices, Color color); // Draw capsule wireframe
DefineEngineFunction( DrawCapsuleWires, void, (Vector3 startPos, Vector3 endPos, float radius, int rings, int slices, Color color), , "Draw capsule wireframe with the center of its sphere caps at startPos and endPos") {
    DrawCapsuleWires(startPos, endPos, radius, rings, slices, color);
}

// RLAPI void DrawPlane(Vector3 centerPos, Vector2 size, Color color); // Draw a plane XZ
DefineEngineFunction( DrawPlane, void, (Vector3 centerPos, Vector2 size, Color color), , "Draw a plane XZ") {
    DrawPlane(centerPos, size, color);
}

// RLAPI void DrawRay(Ray ray, Color color); // Draw a ray line
// NUTZT JETZT NATIV IHR NEUES TYPE_RAY BINDING!
DefineEngineFunction( DrawRay, void, (Ray ray, Color color), , "Draw a ray line using the TypeRay format") {
    DrawRay(ray, color);
}

// RLAPI void DrawGrid(int slices, float spacing); // Draw a grid (centered at (0, 0, 0))
DefineEngineFunction( DrawGrid, void, (int slices, float spacing), , "Draw a grid (centered at (0, 0, 0))") {
    DrawGrid(slices, spacing);
}

//------------------------------------------------------------------------------------
// Model 3d Loading and Drawing Functions (Module: models)
//------------------------------------------------------------------------------------

// // Model management functions
// RLAPI Model LoadModel(const char *fileName);                                                // Load model from files (meshes and materials)
DefineEngineFunction( LoadModel, S32, (String fileName), , "Load model from files (meshes and materials) and return ModelID") {
    Model model = LoadModel(fileName.c_str());
    if (!IsModelValid(model)) return 0;
    return ModelMap.add(model);
}

// RLAPI Model LoadModelFromMesh(Mesh mesh);                                                   // Load model from generated mesh (default material)
DefineEngineFunction( LoadModelFromMesh, S32, (S32 meshId), , "Load model from generated mesh (default material) and return ModelID") {
    Mesh* mesh = MeshMap.get(meshId);
    if (!mesh) {
        Con::errorf("LoadModelFromMesh: Invalid MeshID: %d", meshId);
        return 0;
    }

    Model model = LoadModelFromMesh(*mesh);
    if (!IsModelValid(model)) return 0;

    return ModelMap.add(model);
}
//------------------------------------------------------------------------------------
// ElfScript ==> textureId = ModelGetTexture($model [, matIndex=0, mapMap=MATERIAL_MAP_DIFFUSE]);
DefineEngineFunction( GetModelMatrialCount, S32, (S32 modelId, S32 mapMap), ((S32)MATERIAL_MAP_DIFFUSE),
                      "Gets the material count from a model by \n"
                      "GetModelMapTexture(modelId, [mapMap=MATERIAL_MAP_DIFFUSE])")
{
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("GetModelMapTexture: Invalid modelID: %d", modelId);
        return 0;
    }
    return model->materialCount;
}
//------------------------------------------------------------------------------------
// ElfScript ==> textureId = ModelGetTexture($model [, matIndex=0, mapMap=MATERIAL_MAP_DIFFUSE]);
DefineEngineFunction( GetModelMapTexture, S32, (S32 modelId, S32 matIndex, S32 mapMap), (0, (S32)MATERIAL_MAP_DIFFUSE),
                      "Gets the texture ID from a model material map.\n"
                      "GetModelMapTexture(modelId, [matIndex=0], [mapMap=MATERIAL_MAP_DIFFUSE])"
) {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("GetModelMapTexture: Invalid modelID: %d", modelId);
        return 0;
    }

    if (matIndex < 0 || matIndex >= model->materialCount) {
        Con::errorf("GetModelMapTexture: matIndex %d out of bounds (model has %d materials)", matIndex, model->materialCount);
        return 0;
    }
    if (mapMap < 0 || mapMap > (S32)MATERIAL_MAP_BRDF) {
        Con::errorf("GetModelMapTexture: mapMap %d out of bounds (allowed: 0-%d)", mapMap, (S32)MATERIAL_MAP_BRDF);
        return 0;
    }

    Texture raylibTex = model->materials[matIndex].maps[mapMap].texture;

    if (raylibTex.id == 0) {
        return 0;
    }

    S32 textureId = TextureMap.add(raylibTex);

    return textureId;
}
//------------------------------------------------------------------------------------
// ElfScript ==> model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
DefineEngineFunction( SetModelMapTexture, bool, (S32 modelId,S32 textureId, S32 matIndex, S32 mapMap),(0,(S32)MATERIAL_MAP_DIFFUSE) ,
             "set a texture for a model material map like model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;"
             "SetModelMapTexture($model, $texture) << matIndex default 0,  matMap default MATERIAL_MAP_DIFFUSE "
 ) {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("SetModelMapTexture: Invalid modelID: %d", modelId);
        return false;
    }
    Texture* tex = TextureMap.get(textureId);
    if (!tex) {
        Con::errorf("SetModelMapTexture: Invalid textureID: %d", textureId);
        return false;
    }
    if (matIndex < 0 || matIndex >= model->materialCount) {
        Con::errorf("SetModelMapTexture: matIndex %d out of bounds (model has %d materials)", matIndex, model->materialCount);
        return false;
    }

    if (mapMap < 0 || mapMap > (S32)MATERIAL_MAP_BRDF) {
        Con::errorf("SetModelMapTexture: mapMap %d out of bounds (allowed: 0-11)", mapMap);
        return false;
    }

    model->materials[matIndex].maps[mapMap].texture = *tex;
    return true;
}
//------------------------------------------------------------------------------------
// ElfScript ==> color = ModelGetColor($model [, matIndex=0, mapMap=MATERIAL_MAP_DIFFUSE]);
DefineEngineFunction( GetModelMapColor, Color, (S32 modelId, S32 matIndex, S32 mapMap), (0, (S32)MATERIAL_MAP_DIFFUSE),
                      "Gets the color from a model material map.\n"
                      "GetModelMapColor(modelId, [matIndex=0], [mapMap=MATERIAL_MAP_DIFFUSE])"
) {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("GetModelMapColor: Invalid modelID: %d", modelId);
        return RAYWHITE;
    }

    if (matIndex < 0 || matIndex >= model->materialCount) {
        Con::errorf("GetModelMapColor: matIndex %d out of bounds (model has %d materials)", matIndex, model->materialCount);
        return RAYWHITE;
    }

    if (mapMap < 0 || mapMap > (S32)MATERIAL_MAP_BRDF) {
        Con::errorf("GetModelMapColor: mapMap %d out of bounds (allowed: 0-%d)", mapMap, (S32)MATERIAL_MAP_BRDF);
        return RAYWHITE;
    }

    return model->materials[matIndex].maps[mapMap].color;
}
//------------------------------------------------------------------------------------
// ElfScript ==> model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color
DefineEngineFunction( SetModelMapColor, bool, (S32 modelId, Color color, S32 matIndex, S32 mapMap),(0,(S32)MATERIAL_MAP_DIFFUSE) ,
                      "set a color for a modal material map like model.materials[0].maps[MATERIAL_MAP_DIFFUSE].color = BLUE;"
                      "SetModelMapColor($model, BLUE) << matIndex default 0,  matMap default MATERIAL_MAP_DIFFUSE "
) {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("SetModelMapColor: Invalid modelID: %d", modelId);
        return false;
    }
    if (matIndex < 0 || matIndex >= model->materialCount) {
        Con::errorf("SetModelMapColor: matIndex %d out of bounds (model has %d materials)", matIndex, model->materialCount);
        return false;
    }

    if (mapMap < 0 || mapMap > (S32)MATERIAL_MAP_BRDF) {
        Con::errorf("SetModelMapColor: mapMap %d out of bounds (allowed: 0-11)", mapMap);
        return false;
    }

    model->materials[matIndex].maps[mapMap].color = color;
    return true;
}
//------------------------------------------------------------------------------------
// ElfScript ==> value = GetModelMapValue($model [, matIndex=0, mapMap=MATERIAL_MAP_DIFFUSE]);
DefineEngineFunction( GetModelMapValue, F32, (S32 modelId, S32 matIndex, S32 mapMap), (0, (S32)MATERIAL_MAP_DIFFUSE),
                      "Gets the float value from a model material map.\n"
                      "GetModelMapValue(modelId, [matIndex=0], [mapMap=MATERIAL_MAP_DIFFUSE])"
) {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("GetModelMapValue: Invalid modelID: %d", modelId);
        return 0.0f;
    }

    if (matIndex < 0 || matIndex >= model->materialCount) {
        Con::errorf("GetModelMapValue: matIndex %d out of bounds (model has %d materials)", matIndex, model->materialCount);
        return 0.0f;
    }

    if (mapMap < 0 || mapMap > (S32)MATERIAL_MAP_BRDF) {
        Con::errorf("GetModelMapValue: mapMap %d out of bounds (allowed: 0-%d)", mapMap, (S32)MATERIAL_MAP_BRDF);
        return 0.0f;
    }

    return model->materials[matIndex].maps[mapMap].value;
}
//------------------------------------------------------------------------------------
// ElfScript ==> SetModelMapValue($model, 0.5 [, matIndex=0, mapMap=MATERIAL_MAP_DIFFUSE])
DefineEngineFunction( SetModelMapValue, bool, (S32 modelId, F32 value, S32 matIndex, S32 mapMap), (0, (S32)MATERIAL_MAP_DIFFUSE),
                      "Sets the float value for a model material map (e.g., roughness or metalness factor).\n"
                      "SetModelMapValue(modelId, value [, matIndex=0, mapMap=MATERIAL_MAP_DIFFUSE])"
) {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("SetModelMapValue: Invalid modelID: %d", modelId);
        return false;
    }

    if (matIndex < 0 || matIndex >= model->materialCount) {
        Con::errorf("SetModelMapValue: matIndex %d out of bounds (model has %d materials)", matIndex, model->materialCount);
        return false;
    }

    if (mapMap < 0 || mapMap > (S32)MATERIAL_MAP_BRDF) {
        Con::errorf("SetModelMapValue: mapMap %d out of bounds (allowed: 0-%d)", mapMap, (S32)MATERIAL_MAP_BRDF);
        return false;
    }

    model->materials[matIndex].maps[mapMap].value = value;
    return true;
}
//------------------------------------------------------------------------------------
// ElfScript ==> shaderId = ModelGetShader($model [, matIndex=0])
DefineEngineFunction( GetModelShader, S32, (S32 modelId, S32 matIndex), (0),
                      "Gets the shader ID from a model material.\n"
                      "GetModelShader(modelId [, matIndex=0])"
) {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("GetModelShader: Invalid modelID: %d", modelId);
        return 0;
    }

    if (matIndex < 0 || matIndex >= model->materialCount) {
        Con::errorf("GetModelShader: matIndex %d out of bounds (model has %d materials)", matIndex, model->materialCount);
        return 0;
    }

    Shader raylibShader = model->materials[matIndex].shader;

    return ShadersMap.add(raylibShader);
}

//------------------------------------------------------------------------------------
// ElfScript ==> ModelSetShader($model, $shader [, matIndex=0])
DefineEngineFunction( SetModelShader, bool, (S32 modelId, S32 shaderId, S32 matIndex), (0),
                      "Sets a shader for a model material like model.materials[matIndex].shader = shader;\n"
                      "SetModelShader(modelId, shaderId [, matIndex=0])"
) {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        Con::errorf("SetModelShader: Invalid modelID: %d", modelId);
        return false;
    }

    Shader* shd = ShadersMap.get(shaderId);
    if (!shd) {
        Con::errorf("SetModelShader: Invalid shaderID: %d", shaderId);
        return false;
    }

    if (matIndex < 0 || matIndex >= model->materialCount) {
        Con::errorf("SetModelShader: matIndex %d out of bounds (model has %d materials)", matIndex, model->materialCount);
        return false;
    }

    model->materials[matIndex].shader = *shd;
    return true;
}

//------------------------------------------------------------------------------------

// RLAPI bool IsModelValid(Model model);                                                       // Check if a model is valid (loaded in GPU, VAO/VBOs)
DefineEngineFunction( IsModelValid, bool, (S32 modelId), , "Check if a model is valid (loaded in GPU, VAO/VBOs)") {
    Model* model = ModelMap.get(modelId);
    if (!model) return false;
    return IsModelValid(*model);
}

// RLAPI void UnloadModel(Model model);                                                        // Unload model (including meshes) from memory (RAM and/or VRAM)
DefineEngineFunction( UnloadModel, void, (S32 modelId), , "Unload model (including meshes) from memory (RAM and/or VRAM)") {
    ModelMap.remove(modelId);
}

// RLAPI BoundingBox GetModelBoundingBox(Model model);                                         // Compute model bounding box limits (considers all meshes)
DefineEngineFunction( GetModelBoundingBox, BoundingBox, (S32 modelId), , "Compute model bounding box limits (considers all meshes)") {
    Model* model = ModelMap.get(modelId);
    if (!model) {
        BoundingBox empty = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
        return empty;
    }
    return GetModelBoundingBox(*model);
}
// -----------------------------------------------------------------------------
// Model drawing functions
// -----------------------------------------------------------------------------
// RLAPI void DrawModel(Model model, Vector3 position, float scale, Color tint);               // Draw a model (with texture if set)
DefineEngineFunction( DrawModel, void, (S32 modelId, Vector3 position, float scale, Color tint), (WHITE), "Draw a 3D model with position, scale and tint color") {
    Model* model = ModelMap.get(modelId);
    if (!model) return;

    DrawModel(*model, position, scale, tint);
}

// RLAPI void DrawModelEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint); // Draw a model with extended parameters
DefineEngineFunction( DrawModelEx, void, (S32 modelId, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint), (WHITE), "Draw a 3D model with extended transform parameters") {
    Model* model = ModelMap.get(modelId);
    if (!model) return;

    DrawModelEx(*model, position, rotationAxis, rotationAngle, scale, tint);
}

// RLAPI void DrawModelWires(Model model, Vector3 position, float scale, Color tint);          // Draw a model wires (with texture if set)
DefineEngineFunction( DrawModelWires, void, (S32 modelId, Vector3 position, float scale, Color tint), (WHITE), "Draw a 3D model wireframe") {
    Model* model = ModelMap.get(modelId);
    if (!model) return;

    DrawModelWires(*model, position, scale, tint);
}

// RLAPI void DrawModelWiresEx(Model model, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint); // Draw a model wires (with texture if set) with extended parameters
DefineEngineFunction( DrawModelWiresEx, void, (S32 modelId, Vector3 position, Vector3 rotationAxis, float rotationAngle, Vector3 scale, Color tint), (WHITE), "Draw a 3D model wireframe with extended transform parameters") {
    Model* model = ModelMap.get(modelId);
    if (!model) return;

    DrawModelWiresEx(*model, position, rotationAxis, rotationAngle, scale, tint);
}

// RLAPI void DrawBoundingBox(BoundingBox box, Color color);                                   // Draw bounding box (wires)
// HINWEIS: Hatten wir zwar schon vorbereitet, fügt sich hier aber nahtlos über TypeBoundingBox ein
DefineEngineFunction( DrawBoundingBox, void, (BoundingBox box, Color color), , "Draw a 3D bounding box wireframe") {
    DrawBoundingBox(box, color);
}

// RLAPI void DrawBillboard(Camera camera, Texture2D texture, Vector3 position, float scale, Color tint); // Draw a billboard texture
DefineEngineFunction( DrawBillboard, void, (S32 cameraId, S32 textureId, Vector3 position, float scale, Color tint), (WHITE), "Draw a 2D billboard texture in 3D space facing the camera") {
    Camera3DObject* camObj = dynamic_cast<Camera3DObject*>(Sim::findObject(cameraId));
    Texture2D* tex = TextureMap.get(textureId);

    if (!camObj || !tex) return;

    DrawBillboard(camObj->mCamera, *tex, position, scale, tint);
}

// RLAPI void DrawBillboardRec(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector2 size, Color tint); // Draw a billboard texture defined by source
DefineEngineFunction( DrawBillboardRec, void, (S32 cameraId, S32 textureId, Rectangle source, Vector3 position, Vector2 size, Color tint), (WHITE), "Draw a part of a 2D billboard texture defined by a source rectangle") {
    Camera3DObject* camObj = dynamic_cast<Camera3DObject*>(Sim::findObject(cameraId));
    Texture2D* tex = TextureMap.get(textureId);

    if (!camObj || !tex) return;

    DrawBillboardRec(camObj->mCamera, *tex, source, position, size, tint);
}

// RLAPI void DrawBillboardPro(Camera camera, Texture2D texture, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint); // Draw a billboard texture defined by source and rotation
DefineEngineFunction( DrawBillboardPro, void, (S32 cameraId, S32 textureId, Rectangle source, Vector3 position, Vector3 up, Vector2 size, Vector2 origin, float rotation, Color tint), (WHITE), "Draw a billboard texture with pro transform parameters") {
    Camera3DObject* camObj = dynamic_cast<Camera3DObject*>(Sim::findObject(cameraId));
    Texture2D* tex = TextureMap.get(textureId);

    if (!camObj || !tex) return;

    DrawBillboardPro(camObj->mCamera, *tex, source, position, up, size, origin, rotation, tint);
}
//------------------------------------------------------------------------------
// Mesh management functions
//------------------------------------------------------------------------------
// RLAPI void UploadMesh(Mesh *mesh, bool dynamic);                                            // Upload mesh vertex data in GPU and provide VAO/VBO ids
DefineEngineFunction( UploadMesh, void, (S32 meshId, bool dynamic), , "Upload mesh vertex data to GPU (VRAM)") {
    Mesh* mesh = MeshMap.get(meshId);
    if (!mesh) return;
    UploadMesh(mesh, dynamic);
}

// RLAPI void UpdateMeshBuffer(Mesh mesh, int index, const void *data, int dataSize, int offset); // Update mesh vertex data in GPU for a specific buffer index
DefineEngineFunction( UpdateMeshBuffer, void, (S32 meshId, int index, Vector<F32> dataValues, int dataSize, int offset), ,
                      "Update mesh vertex data in GPU for a specific buffer index using a float list") {
    Mesh* mesh = MeshMap.get(meshId);
    if (!mesh || dataValues.size() == 0) return;

    UpdateMeshBuffer(*mesh, index, dataValues.address(), dataSize, offset);
}

// RLAPI void UnloadMesh(Mesh mesh);                                                           // Unload mesh data from CPU and GPU
DefineEngineFunction( UnloadMesh, void, (S32 meshId), , "Unload mesh data from CPU and GPU memory") {
    MeshMap.remove(meshId);
}

// RLAPI Matrix MatrixIdentity(void);                                                         // Returns identity matrix
DefineEngineFunction( MatrixIdentity, Matrix, (), , "Returns a 3D identity matrix") {
    return MatrixIdentity();
}

// RLAPI Matrix MatrixTranslate(float x, float y, float z);                                    // Translate matrix
DefineEngineFunction( MatrixTranslate, Matrix, (float x, float y, float z), , "Returns a translation matrix") {
    return MatrixTranslate(x, y, z);
}

// RLAPI Matrix MatrixRotateXYZ(Vector3 angle);                                               // Rotate matrix by XYZ angles (radians)
DefineEngineFunction( MatrixRotateXYZ, Matrix, (Vector3 angleRadians), , "Returns a rotation matrix from XYZ angles (in radians)") {
    return MatrixRotateXYZ(angleRadians);
}

// RLAPI Matrix MatrixMultiply(Matrix left, Matrix right);                                    // Multiply two matrices
DefineEngineFunction( MatrixMultiply, Matrix, (Matrix left, Matrix right), , "Multiplies two matrices together") {
    return MatrixMultiply(left, right);
}

// RLAPI void DrawMesh(Mesh mesh, Material material, Matrix transform);                        // Draw a 3d mesh
DefineEngineFunction( DrawMesh, void, (S32 meshId, S32 materialId, Matrix transform), , "Draw a 3d mesh with material and transform matrix") {
    Mesh* mesh = MeshMap.get(meshId);
    Material* mat = MaterialsMap.get(materialId);

    Material material = (mat != nullptr) ? *mat : LoadMaterialDefault();

    if (!mesh) return;

    DrawMesh(*mesh, material, transform);
}


// RLAPI BoundingBox GetMeshBoundingBox(Mesh mesh);                                            // Compute mesh bounding box limits
DefineEngineFunction( GetMeshBoundingBox, BoundingBox, (S32 meshId), , "Compute mesh bounding box limits") {
    Mesh* mesh = MeshMap.get(meshId);
    if (!mesh) {
        BoundingBox empty = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };
        return empty;
    }
    return GetMeshBoundingBox(*mesh);
}

// RLAPI void GenMeshTangents(Mesh *mesh);                                                     // Compute mesh tangents
DefineEngineFunction( GenMeshTangents, void, (S32 meshId), , "Compute mesh tangents for normal-mapping") {
    Mesh* mesh = MeshMap.get(meshId);
    if (!mesh) return;

    GenMeshTangents(mesh);
}

// RLAPI bool ExportMesh(Mesh mesh, const char *fileName);                                     // Export mesh data to file, returns true on success
DefineEngineFunction( ExportMesh, bool, (S32 meshId, String fileName), , "Export mesh data to file (.obj), returns true on success") {
    Mesh* mesh = MeshMap.get(meshId);
    if (!mesh) return false;

    return ExportMesh(*mesh, fileName.c_str());
}

// RLAPI bool ExportMeshAsCode(Mesh mesh, const char *fileName);                               // Export mesh as code file (.h)
DefineEngineFunction( ExportMeshAsCode, bool, (S32 meshId, String fileName), , "Export mesh as code file (.h) defining vertex attribute arrays") {
    Mesh* mesh = MeshMap.get(meshId);
    if (!mesh) return false;

    return ExportMeshAsCode(*mesh, fileName.c_str());
}

// RLAPI void DrawMeshInstanced(Mesh mesh, Material material, const Matrix *transforms, int instances); // Draw multiple mesh instances with material and different transforms

// -----------------------------------------------------------------------------
// Mesh generation functions
// -----------------------------------------------------------------------------
// RLAPI Mesh GenMeshPoly(int sides, float radius);                                            // Generate polygonal mesh
DefineEngineFunction( GenMeshPoly, S32, (int sides, float radius), , "Generate polygonal mesh and return MeshID") {
    Mesh mesh = GenMeshPoly(sides, radius);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshPlane(float width, float length, int resX, int resZ);                     // Generate plane mesh (with subdivisions)
DefineEngineFunction( GenMeshPlane, S32, (float width, float length, int resX, int resZ), , "Generate plane mesh (with subdivisions) and return MeshID") {
    Mesh mesh = GenMeshPlane(width, length, resX, resZ);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshCube(float width, float height, float length);                            // Generate cuboid mesh
DefineEngineFunction( GenMeshCube, S32, (float width, float height, float length), , "Generate cuboid mesh and return MeshID") {
    Mesh mesh = GenMeshCube(width, height, length);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshSphere(float radius, int rings, int slices);                              // Generate sphere mesh (standard sphere)
DefineEngineFunction( GenMeshSphere, S32, (float radius, int rings, int slices), , "Generate sphere mesh (standard sphere) and return MeshID") {
    Mesh mesh = GenMeshSphere(radius, rings, slices);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshHemiSphere(float radius, int rings, int slices);                          // Generate half-sphere mesh (no bottom cap)
DefineEngineFunction( GenMeshHemiSphere, S32, (float radius, int rings, int slices), , "Generate half-sphere mesh (no bottom cap) and return MeshID") {
    Mesh mesh = GenMeshHemiSphere(radius, rings, slices);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshCylinder(float radius, float height, int slices);                         // Generate cylinder mesh
DefineEngineFunction( GenMeshCylinder, S32, (float radius, float height, int slices), , "Generate cylinder mesh and return MeshID") {
    Mesh mesh = GenMeshCylinder(radius, height, slices);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshCone(float radius, float height, int slices);                             // Generate cone/pyramid mesh
DefineEngineFunction( GenMeshCone, S32, (float radius, float height, int slices), , "Generate cone/pyramid mesh and return MeshID") {
    Mesh mesh = GenMeshCone(radius, height, slices);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshTorus(float radius, float size, int radSeg, int sides);                   // Generate torus mesh
DefineEngineFunction( GenMeshTorus, S32, (float radius, float size, int radSeg, int sides), , "Generate torus mesh and return MeshID") {
    Mesh mesh = GenMeshTorus(radius, size, radSeg, sides);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshKnot(float radius, float size, int radSeg, int sides);                    // Generate trefoil knot mesh
DefineEngineFunction( GenMeshKnot, S32, (float radius, float size, int radSeg, int sides), , "Generate trefoil knot mesh and return MeshID") {
    Mesh mesh = GenMeshKnot(radius, size, radSeg, sides);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshHeightmap(Image heightmap, Vector3 size);                                 // Generate heightmap mesh from image data
DefineEngineFunction( GenMeshHeightmap, S32, (S32 imageId, Vector3 size), , "Generate heightmap mesh from image data and return MeshID") {
    Image* img = ImageMap.get(imageId);
    if (!img || img->data == nullptr) {
        Con::errorf("GenMeshHeightmap: Invalid ImageID: %d", imageId);
        return 0;
    }
    Mesh mesh = GenMeshHeightmap(*img, size);
    return MeshMap.add(mesh);
}

// RLAPI Mesh GenMeshCubicmap(Image cubicmap, Vector3 cubeSize);                               // Generate cubes-based map mesh from image data
DefineEngineFunction( GenMeshCubicmap, S32, (S32 imageId, Vector3 cubeSize), , "Generate cubes-based map mesh from image data and return MeshID") {
    Image* img = ImageMap.get(imageId);
    if (!img || img->data == nullptr) {
        Con::errorf("GenMeshCubicmap: Invalid ImageID: %d", imageId);
        return 0;
    }
    Mesh mesh = GenMeshCubicmap(*img, cubeSize);
    return MeshMap.add(mesh);
}


// RLAPI bool IsMaterialValid(Material material);                                              // Check if a material is valid
DefineEngineFunction( IsMaterialValid, bool, (S32 materialId), , "Check if a material is valid") {
    Material* mat = MaterialsMap.get(materialId);
    if (!mat) return false;
    return IsMaterialValid(*mat);
}

// RLAPI void UnloadMaterial(Material material);                                               // Unload material from GPU memory (VRAM)
DefineEngineFunction( UnloadMaterial, void, (S32 materialId), , "Unload material from GPU memory (VRAM)") {
    if (materialId <= 0) return; // Default-Material niemals entladen!
    MaterialsMap.remove(materialId);
}

// RLAPI void SetMaterialTexture(Material *material, int mapType, Texture2D texture);          // Set texture for a material map type
DefineEngineFunction( SetMaterialTexture, void, (S32 materialId, int mapType, S32 textureId), , "Set texture for a material map type (e.g. MATERIAL_MAP_DIFFUSE)") {
    Material* mat = MaterialsMap.get(materialId);
    Texture2D* tex = TextureMap.get(textureId);

    if (!mat || !tex) return;

    // Raylib erwartet hier einen Pointer auf das Material, da es die Textur-ID darin einträgt
    SetMaterialTexture(mat, mapType, *tex);
}

// RLAPI void SetModelMeshMaterial(Model *model, int meshId, int materialId);                  // Set material for a mesh
DefineEngineFunction( SetModelMeshMaterial, void, (S32 modelId, int meshId, S32 materialId), , "Set material for a specific mesh index inside a model") {
    Model* model = ModelMap.get(modelId);
    Material* mat = MaterialsMap.get(materialId);

    if (!model) return;

    if (meshId < 0 || meshId >= model->meshCount) {
        Con::errorf("SetModelMeshMaterial: Mesh index %d out of bounds for Model %d (Count: %d)", meshId, modelId, model->meshCount);
        return;
    }

    model->materials[meshId] = (mat != nullptr) ? *mat : LoadMaterialDefault();
}

// -----------------------------------------------------------------------------
// Collision detection functions
// -----------------------------------------------------------------------------
// RLAPI bool CheckCollisionSpheres(Vector3 center1, float radius1, Vector3 center2, float radius2); // Check collision between two spheres
DefineEngineFunction( CheckCollisionSpheres, bool, (Vector3 center1, float radius1, Vector3 center2, float radius2), , "Check collision between two spheres") {
    return CheckCollisionSpheres(center1, radius1, center2, radius2);
}

// RLAPI bool CheckCollisionBoxes(BoundingBox box1, BoundingBox box2);                         // Check collision between two bounding boxes
DefineEngineFunction( CheckCollisionBoxes, bool, (BoundingBox box1, BoundingBox box2), , "Check collision between two bounding boxes") {
    return CheckCollisionBoxes(box1, box2);
}

// RLAPI bool CheckCollisionBoxSphere(BoundingBox box, Vector3 center, float radius);          // Check collision between box and sphere
DefineEngineFunction( CheckCollisionBoxSphere, bool, (BoundingBox box, Vector3 center, float radius), , "Check collision between box and sphere") {
    return CheckCollisionBoxSphere(box, center, radius);
}


// RLAPI RayCollision GetRayCollisionSphere(Ray ray, Vector3 center, float radius);            // Get collision info between ray and sphere
DefineEngineFunction( GetRayCollisionSphere, const char*, (Ray ray, Vector3 center, float radius), , "Returns hit info string 'px py pz nx ny nz dist' or empty string") {
    return FormatRayCollision(GetRayCollisionSphere(ray, center, radius));
}

// RLAPI RayCollision GetRayCollisionBox(Ray ray, BoundingBox box);                            // Get collision info between ray and box
DefineEngineFunction( GetRayCollisionBox, const char*, (Ray ray, BoundingBox box), , "Returns hit info string 'px py pz nx ny nz dist' or empty string") {
    return FormatRayCollision(GetRayCollisionBox(ray, box));
}

// RLAPI RayCollision GetRayCollisionMesh(Ray ray, Mesh mesh, Matrix transform);               // Get collision info between ray and mesh
DefineEngineFunction( GetRayCollisionMesh, const char*, (Ray ray, S32 meshId, Matrix transform), , "Returns hit info string from 3D mesh collision") {
    Mesh* mesh = MeshMap.get(meshId);
    if (!mesh) return "";
    return FormatRayCollision(GetRayCollisionMesh(ray, *mesh, transform));
}

// RLAPI RayCollision GetRayCollisionTriangle(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3);    // Get collision info between ray and triangle
DefineEngineFunction( GetRayCollisionTriangle, const char*, (Ray ray, Vector3 p1, Vector3 p2, Vector3 p3), , "Returns hit info string from 3D triangle collision") {
    return FormatRayCollision(GetRayCollisionTriangle(ray, p1, p2, p3));
}

// RLAPI RayCollision GetRayCollisionQuad(Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4); // Get collision info between ray and quad
DefineEngineFunction( GetRayCollisionQuad, const char*, (Ray ray, Vector3 p1, Vector3 p2, Vector3 p3, Vector3 p4), , "Returns hit info string from 3D quad collision") {
    return FormatRayCollision(GetRayCollisionQuad(ray, p1, p2, p3, p4));
}



// -----------------------------------------------------------------------------
// NOTE: Elfscript: Model animations loading/unloading functions
// -----------------------------------------------------------------------------
// RLAPI void UpdateModelAnimationEx(Model model, ModelAnimation animA, float frameA, ModelAnimation animB, float frameB, float blend); // Update model animation pose, blending two animations

// RLAPI ModelAnimation *LoadModelAnimations(const char *fileName, int *animCount);
DefineEngineFunction( LoadModelAnimations, S32, (String fileName), , "Load model animations from file and return an AnimationBlockID") {
    int animCount = 0;
    ModelAnimation* anims = LoadModelAnimations(fileName.c_str(), &animCount);

    if (animCount <= 0 || anims == nullptr) {
        return 0;
    }

    ElfAnimationBlock block;
    block.anims = anims;
    block.count = (unsigned int)animCount;

    return ModelAnimationMap.add(block);
}

// RLAPI void UpdateModelAnimation(Model model, ModelAnimation anim, int frame);
DefineEngineFunction( UpdateModelAnimation, void, (S32 modelId, S32 animBlockId, int animIndex, int frame), , "Update model animation pose for a specific frame index") {
    Model* model = ModelMap.get(modelId);
    ElfAnimationBlock* block = ModelAnimationMap.get(animBlockId);

    if (!model || !block || block->anims == nullptr) return;

    if (animIndex < 0 || animIndex >= (int)block->count) {
        Con::errorf("UpdateModelAnimation: Animation index %d out of bounds (Max: %d)", animIndex, block->count - 1);
        return;
    }

    UpdateModelAnimation(*model, block->anims[animIndex], frame);
}

// RLAPI void UnloadModelAnimations(ModelAnimation *animations, int animCount);
DefineEngineFunction( UnloadModelAnimations, void, (S32 animBlockId), , "Unload model animation array data from memory") {
    ModelAnimationMap.remove(animBlockId);
}

// Helper func
DefineEngineFunction( GetModelAnimationCount, int, (S32 animBlockId), , "Get total number of animations inside an AnimationBlock") {
    ElfAnimationBlock* block = ModelAnimationMap.get(animBlockId);
    if (!block) return 0;
    return (int)block->count;
}
// ----------------------
// WRAPPER FIXME MORE ;)
// ElfScript ==> %cubeModelId = GenModelCube(2.0, 2.0, 2.0);
DefineEngineFunction( GenModelCube, S32, (F32 width, F32 height, F32 length), ,
                      "Generates a 3D cube model from dimensions and returns its modelId."
) {
    if (width <= 0.0f || height <= 0.0f || length <= 0.0f) return 0;
    Mesh mesh = ::GenMeshCube(width, height, length);
    Model model = ::LoadModelFromMesh(mesh);
    return ModelMap.add(model);
}
// ElfScript ==> %sphereModelId = GenModelSphere(1.0, 16, 16);
DefineEngineFunction( GenModelSphere, S32, (F32 radius, int rings, int slices), ,
                      "Generates a 3D sphere model and returns its modelId."
) {
    if (radius <= 0.0f || rings < 3 || slices < 3) return 0;
    Mesh mesh = ::GenMeshSphere(radius, rings, slices);
    Model model = ::LoadModelFromMesh(mesh);
    return ModelMap.add(model);
}

// ElfScript ==> %cylinderModelId = GenModelCylinder(0.5, 2.0, 16);
DefineEngineFunction( GenModelCylinder, S32, (F32 radius, F32 height, int slices), ,
                      "Generates a 3D cylinder model and returns its modelId."
) {
    if (radius <= 0.0f || height <= 0.0f || slices < 3) return 0;
    Mesh mesh = ::GenMeshCylinder(radius, height, slices);
    Model model = ::LoadModelFromMesh(mesh);
    return ModelMap.add(model);
}
