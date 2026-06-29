//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Storage Template for Resources and Resource Tools
// usage: ElfStorage<Image, UnloadImage> ImageMap;
//-----------------------------------------------------------------------------
#pragma once
#include <raylib.h>
#include <platform/types.h>
#include <unordered_map>
#include "core/util/tVector.h"
#include <vector>
#include <console/console.h>
// #include "elfObjects.h"

namespace ElfResource {

// -------------------------------------------------------------------------
// Template for Resource Handling
// - add() add a item (copy)
// - get() get the pointer of the item
// - getList() get a list of the objects as copy
//          use result.data() to get the pointer.
// - remove() remove a item from the Storage
// - clear() unload all resouces and reset storage
// -------------------------------------------------------------------------
template <typename T, void (*UnloadFunc)(T)>
struct ElfStorage {
    S32 mId = 0;
    std::unordered_map<S32, T> mMap;

    // -------------------------------------------------------------------------
    S32 add(T item) {
        mMap[++mId] = item;
        return mId;
    }
    // -------------------------------------------------------------------------
    T* get(S32 id) {
        auto it = mMap.find(id);
        if (it != mMap.end()) {
            return &it->second;
        }
        return nullptr;
    }
    // -------------------------------------------------------------------------
    std::vector<T> getList(Vector<S32> ids) {
        std::vector<T> objects;
        for (S32 i =0; i < ids.size(); i++) {
            auto obj  = get(ids[i]);
            if (obj) objects.push_back(*obj);
        }
        return objects;
    }
    // -------------------------------------------------------------------------
    bool remove(S32 id) {
        auto it = mMap.find(id);
        if (it == mMap.end()) return false;

        UnloadFunc(it->second);

        mMap.erase(it);
        return true;
    }
    // -------------------------------------------------------------------------
    bool removeId(S32 id) {
        auto it = mMap.find(id);
        if (it == mMap.end()) return false;
        mMap.erase(it);
        return true;
    }
    // -------------------------------------------------------------------------
    void clear() {
        for (auto& [key, val] : mMap) {
            UnloadFunc(val);
        }
        mMap.clear();
        mId = 0;
    }

};
// -------------------------------------------------------------------------
// Special for default font when id <=0 !
// -------------------------------------------------------------------------
template<>
inline Font* ElfStorage<Font, UnloadFont>::get(S32 id) {
    if (id <= 0) {
        static Font defaultFont = GetFontDefault();
        return &defaultFont;
    }

    // Das ist der originale Code aus Ihrem Template für alle anderen IDs
    auto it = mMap.find(id);
    if (it != mMap.end()) {
        return &it->second;
    }
    return nullptr;
}
// -------------------------------------------------------------------------
// Special for Typ Material
// -------------------------------------------------------------------------
template<>
inline Material* ElfStorage<Material, UnloadMaterial>::get(S32 id) {
    if (id <= 0) {
        static Material defaultMaterial = LoadMaterialDefault();
        return &defaultMaterial;
    }

    auto it = mMap.find(id);
    if (it != mMap.end()) {
        return &it->second;
    }
    return nullptr;
}

// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// Helper func to get Vector2  from: Vector<F32> pointValues, S32 pointCount
inline std::vector<Vector2> getVector2List(Vector<F32> pointValues, S32 pointCount) {
    std::vector<Vector2> points;
    if ( pointCount <= 0) return points;

    if (pointValues.size() != (pointCount * 2)) {
        Con::errorf("PointValues size (%d) does not match pointCount * 2 (%d)!", (int)pointValues.size(), pointCount * 2);
        return points;
    }

    points.reserve(pointCount);

    for (S32 i = 0; i < pointCount; ++i) {
        points.push_back( { pointValues[i*2], pointValues[i*2+1] });
    }
    return points;
}
// -----------------------------------------------------------------------------------

inline std::vector<Vector3> getVector3List(Vector<F32> pointValues, S32 pointCount) {
    std::vector<Vector3> points;
    if (pointCount <= 0) return points;

    if (pointValues.size() != (size_t)(pointCount * 3)) {
        Con::errorf("getVector3List: pointValues size (%d) does not match pointCount * 3 (%d)!", (int)pointValues.size(), pointCount * 3);
        return points;
    }

    points.reserve(pointCount);

    for (S32 i = 0; i < pointCount; ++i) {
        S32 idx = i * 3;
        points.push_back({ pointValues[idx], pointValues[idx + 1], pointValues[idx + 2] });
    }
    return points;
}
// -----------------------------------------------------------------------------------

inline std::vector<Vector4> getVector4List(Vector<F32> pointValues, S32 pointCount) {
    std::vector<Vector4> points;
    if (pointCount <= 0) return points;

    if (pointValues.size() != (size_t)(pointCount * 4)) {
        Con::errorf("getVector4List: pointValues size (%d) does not match pointCount * 4 (%d)!", (int)pointValues.size(), pointCount * 4);
        return points;
    }

    points.reserve(pointCount);

    for (S32 i = 0; i < pointCount; ++i) {
        S32 idx = i * 4;
        points.push_back({ pointValues[idx], pointValues[idx + 1], pointValues[idx + 2], pointValues[idx + 3] });
    }
    return points;
}

// -----------------------------------------------------------------------------------
// Special for animations
struct ElfAnimationBlock {
    ModelAnimation* anims = nullptr;
    unsigned int count = 0;
};


inline void UnloadElfAnimationBlock(ElfAnimationBlock block) {
    if (block.anims != nullptr && block.count > 0) {
        UnloadModelAnimations(block.anims, block.count);
    }
}
// -----------------------------------------------------------------------------------

inline ElfStorage<Image, UnloadImage> ImageMap;
inline ElfStorage<Texture, UnloadTexture> TextureMap;
inline ElfStorage<Font, UnloadFont> FontMap;
inline ElfStorage<Model, UnloadModel> ModelMap;
inline ElfStorage<Mesh, UnloadMesh> MeshMap;
inline ElfStorage<Material, UnloadMaterial> MaterialsMap;
inline ElfStorage<ElfAnimationBlock, UnloadElfAnimationBlock> ModelAnimationMap; //special
inline ElfStorage<Shader, UnloadShader> ShadersMap;
inline ElfStorage<Wave, UnloadWave> WaveMap;
inline ElfStorage<Sound, UnloadSound> SoundMap;
inline ElfStorage<Music, UnloadMusicStream> MusicMap;




// -----------------------------------------------------------------------------------
} //ElfResource
