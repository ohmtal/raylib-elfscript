//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfStorage.h"
#include <console/console.h>
#include "console/engineAPI.h"
#include "ConsoleTypes.h"
#include "elfStorage.h"

using namespace ElfResource;
//-----------------------------------------------------------------------------
// RLAPI void BeginShaderMode(Shader shader);                        // Begin custom shader drawing
DefineEngineFunction( BeginShaderMode, void, (S32 shaderId), , "Begin custom shader drawing using a ShaderID") {
    Shader* shader = ShadersMap.get(shaderId);
    if (!shader) {
        Con::errorf("BeginShaderMode: Invalid ShaderID: %d", shaderId);
        return;
    }
    BeginShaderMode(*shader);
}

// RLAPI void EndShaderMode(void);                                   // End custom shader drawing (use default shader)
DefineEngineFunction( EndShaderMode, void, (), , "End custom shader drawing and reset to the default Raylib shader") {
    EndShaderMode();
}
//-----------------------------------------------------------------------------
// Shader management functions
//-----------------------------------------------------------------------------
// NOTE: Shader functionality is not available on OpenGL 1.1
//-----------------------------------------------------------------------------
// RLAPI Shader LoadShader(const char *vsFileName, const char *fsFileName);   // Load shader from files
DefineEngineFunction( LoadShader, S32, (String vsFileName, String fsFileName), , "Load shader from files and return ShaderID") {
    // Falls ein Pfad leer ist (nullptr für reines Vertex- oder Fragment-Shading)
    const char* vs = vsFileName.isEmpty() ? nullptr : vsFileName.c_str();
    const char* fs = fsFileName.isEmpty() ? nullptr : fsFileName.c_str();

    Shader shader = LoadShader(vs, fs);
    if (!IsShaderValid(shader)) return 0;
    return ShadersMap.add(shader);
}

// RLAPI Shader LoadShaderFromMemory(const char *vsCode, const char *fsCode); // Load shader from code strings
DefineEngineFunction( LoadShaderFromMemory, S32, (String vsCode, String fsCode), , "Load shader from code strings and return ShaderID") {
    const char* vs = vsCode.isEmpty() ? nullptr : vsCode.c_str();
    const char* fs = fsCode.isEmpty() ? nullptr : fsCode.c_str();

    Shader shader = LoadShaderFromMemory(vs, fs);
    if (!IsShaderValid(shader)) return 0;
    return ShadersMap.add(shader);
}

// RLAPI bool IsShaderValid(Shader shader);                                   // Check if a shader is valid
DefineEngineFunction( IsShaderValid, bool, (S32 shaderId), , "Check if a shader is valid (loaded on GPU)") {
    Shader* shader = ShadersMap.get(shaderId);
    if (!shader) return false;
    return IsShaderValid(*shader);
}

// RLAPI int GetShaderLocation(Shader shader, const char *uniformName);       // Get shader uniform location
DefineEngineFunction( GetShaderLocation, int, (S32 shaderId, String uniformName), , "Get shader uniform location index") {
    Shader* shader = ShadersMap.get(shaderId);
    if (!shader) return -1;
    return GetShaderLocation(*shader, uniformName.c_str());
}

// RLAPI int GetShaderLocationAttrib(Shader shader, const char *attribName);  // Get shader attribute location
DefineEngineFunction( GetShaderLocationAttrib, int, (S32 shaderId, String attribName), , "Get shader attribute location index") {
    Shader* shader = ShadersMap.get(shaderId);
    if (!shader) return -1;
    return GetShaderLocationAttrib(*shader, attribName.c_str());
}

// RLAPI void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);
DefineEngineFunction( SetShaderValue, void, (S32 shaderId, int locIndex, String valueStr, int uniformType), , "Set shader uniform value from a string based on uniformType") {
    Shader* shader = ShadersMap.get(shaderId);
    if (!shader || locIndex < 0) return;

    // Wir konvertieren den TorqueScript-String basierend auf dem Raylib Uniform-Typ
    // (SHADER_UNIFORM_FLOAT = 0, SHADER_UNIFORM_VEC2 = 1, SHADER_UNIFORM_VEC3 = 2, SHADER_UNIFORM_VEC4 = 3, SHADER_UNIFORM_INT = 4 ...)
    float fValues[4] = { 0.0f };
    int iValues[4] = { 0 };

    if (uniformType <= 3) { // Es ist ein Float, Vec2, Vec3 oder Vec4
        dSscanf(valueStr.c_str(), "%g %g %g %g", &fValues[0], &fValues[1], &fValues[2], &fValues[3]);
        SetShaderValue(*shader, locIndex, fValues, uniformType);
    }
    else if (uniformType == 4) { // SHADER_UNIFORM_INT
        dSscanf(valueStr.c_str(), "%d %d %d %d", &iValues[0], &iValues[1], &iValues[2], &iValues[3]);
        SetShaderValue(*shader, locIndex, iValues, uniformType);
    }
}

// RLAPI void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType, int count);
DefineEngineFunction( SetShaderValueV, void, (S32 shaderId, int locIndex, Vector<F32> dataValues, int uniformType, int count), , "Set shader uniform array/vector using a flat float list") {
    Shader* shader = ShadersMap.get(shaderId);
    if (!shader || locIndex < 0 || dataValues.size() == 0) return;

    // Wir reichen den Zeiger auf das flache Float-Array direkt an Raylib durch
    SetShaderValueV(*shader, locIndex, dataValues.address(), uniformType, count);
}

// RLAPI void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);  // Set shader uniform value (matrix 4x4)
DefineEngineFunction( SetShaderValueMatrix, void, (S32 shaderId, int locIndex, Matrix mat), , "Set shader uniform value for a 4x4 matrix") {
    Shader* shader = ShadersMap.get(shaderId);
    if (!shader || locIndex < 0) return;

    SetShaderValueMatrix(*shader, locIndex, mat);
}

// RLAPI void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture); // Set shader uniform value and bind texture
DefineEngineFunction( SetShaderValueTexture, void, (S32 shaderId, int locIndex, S32 textureId), , "Set shader uniform value and bind a Texture2D ID") {
    Shader* shader = ShadersMap.get(shaderId);
    Texture2D* tex = TextureMap.get(textureId);
    if (!shader || !tex || locIndex < 0) return;

    SetShaderValueTexture(*shader, locIndex, *tex);
}

// RLAPI void UnloadShader(Shader shader);                                    // Unload shader from GPU memory (VRAM)
DefineEngineFunction( UnloadShader, void, (S32 shaderId), , "Unload shader from GPU memory (VRAM)") {
    ShadersMap.remove(shaderId);
}

