//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfResource.h"

namespace ElfResource {

    void shutDown() {
        Con::printf("Unloading resources...");
        ImageMap.clear();
        TextureMap.clear();
        FontMap.clear();
    }

} // ElfResource
