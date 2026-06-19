//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Storage Template for Resources
// usage: ElfStorage<Image, UnloadImage> ImageMap;
//-----------------------------------------------------------------------------
#pragma once
#include <raylib.h>
#include <platform/types.h>
#include <unordered_map>

namespace ElfResource {



template <typename T, void (*UnloadFunc)(T)>
struct ElfStorage {
    S32 mId = 0;
    std::unordered_map<S32, T> mMap;

    S32 add(T item) {
        mMap[++mId] = item;
        return mId;
    }

    T* get(S32 id) {
        auto it = mMap.find(id);
        if (it != mMap.end()) {
            return &it->second;
        }
        return nullptr;
    }

    bool remove(S32 id) {
        auto it = mMap.find(id);
        if (it == mMap.end()) return false;

        UnloadFunc(it->second);

        mMap.erase(it);
        return true;
    }

    void clear() {
        for (auto& [key, val] : mMap) {
            UnloadFunc(val);
        }
        mMap.clear();
        mId = 0;
    }
};
// -----------------------------------------------------------------------------------

inline ElfStorage<Image, UnloadImage> ImageMap;
inline ElfStorage<Texture2D, UnloadTexture> TextureMap;
inline ElfStorage<Font, UnloadFont> FontMap;


// -----------------------------------------------------------------------------------
} //ElfResource
