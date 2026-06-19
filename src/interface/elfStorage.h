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
#include "core/util/tVector.h"
#include <vector>

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
