//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// SDL_render / some SDL_video / some SDL_Rect ElfScript bindings
//-----------------------------------------------------------------------------
#pragma once

#include <SDL3/SDL_render.h>
#include "resourceManager/ElfResource.h"

namespace ElfSDL3 {

    //Note dont forget to add them to ShutDownRenderer!!
    inline ElfResource::ElfStorage<SDL_Window*  , SDL_DestroyWindow>   WindowMap;
    inline ElfResource::ElfStorage<SDL_Renderer*, SDL_DestroyRenderer> RendererMap;
    inline ElfResource::ElfStorage<SDL_Surface* , SDL_DestroySurface>  SurfaceMap;
    inline ElfResource::ElfStorage<SDL_Texture* , SDL_DestroyTexture>  TextureMap;


    inline bool IsRenderInitialized = false;
    void InitRenderer(); // calling=> void RegisterRenderConstants();
    void ShutDownRenderer();

} //namespace
