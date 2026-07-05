//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfResource.h"

namespace ElfResource {

    void shutDown() {
        Con::printf("ElfResource shutdown....");
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

} // ElfResource
