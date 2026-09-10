//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfResource.h"
#include "console/engineAPI.h"

namespace ElfResource {

    void clearAll() {
        ImageMap.clear();
        TextureMap.clear();
        FontMap.clear();
        ModelMap.clear();
        //double free MeshMap.clear();
        MaterialsMap.clear();
        ModelAnimationMap.clear();
        ShadersMap.clear();
        WaveMap.clear();
        SoundMap.clear();
        MusicMap.clear();
        ColorsMap.clear();
    }
    //--------------------------------------------------------------------------
    void shutDown() {
        Con::printf("ElfResource shutdown....");
        clearAll();
    }
    //--------------------------------------------------------------------------
    DefineEngineFunction(ClearAllResources, void, (), , "Resource Manager: Unload all resources and clear resource maps.") {
        ElfResource::clearAll();
    }
} // ElfResource
