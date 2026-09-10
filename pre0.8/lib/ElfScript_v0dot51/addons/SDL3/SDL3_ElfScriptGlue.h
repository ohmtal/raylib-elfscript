//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Glue them together .. you can also use them separatly
//-----------------------------------------------------------------------------
#pragma once

#include "addons/SDL3/SDL3_core.h"
#include "addons/SDL3/SDL3_render.h"
#include "addons/SDL3/SDL3_audio.h"
#include "addons/SDL3/SDL3_input.h"
#include "addons/SDL3/SDL3_Filesystem.h"

#include <functional> //<< bad boy ;)

namespace ElfSDL3 {
    void Init() ;
    void Shutdown();


    // FrameTime
    inline F64 FrameTime = 0.f;

    // using functional for simple lambda call -
    // i would have used Signal but functional is much easier to use
    inline std::function<void(const SDL_Event&)> OnLoop = nullptr;

}


