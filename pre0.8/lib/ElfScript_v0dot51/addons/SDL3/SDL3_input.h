//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// - Implement polling SDL_IsKeyPressed, SDL_IsMouseButtonPressed ....
// - Implement addional or alternativ events:
//      function onSDLKeyBoardEvent(%scancode, %modifiers, %isDown, %isRepeat)
//      DISABLED: function onSDLMouseMotionEvent(%x, %y, %deltaX, %deltaY)
//      function onSDLMouseButtonEvent(%button, %isDown, %x, %y)
//      function onSDLMouseWheelEvent(%wheelX, %wheelY)
//  NOTE: is you use Events only you do not need to call ClearInputFrameTicks
//  NOTE: you can disable the ElfScript polling bindings with ElfSDL3_DISABLE_POLL
//        this will hide the bindings only if you do not call ClearInputFrameTicks
//        you also can ignore this.
//-----------------------------------------------------------------------------
#pragma once

#include <SDL3/SDL.h>

namespace ElfSDL3 {
    // NOTE IMPLEMENTATION: You need to call this once to register the constants
    void InitKeyCodes();

    // NOTE IMPLEMENTATION:  reset the states very frame
    void ClearInputFrameTicks();

    // --------------- Keyboard via Scancodes: -----------------

    // NOTE IMPLEMENTATION:  onEvent
    void onEvent(const SDL_Event& event);

    bool IsKeyPressed(SDL_Scancode key);
    bool IsKeyDown(SDL_Scancode key);
    bool IsKeyReleased(SDL_Scancode key);
    bool IsKeyUp(SDL_Scancode key) ;
    bool IsKeyRepeat(SDL_Scancode key);

    bool IsShortcutPressed(Uint16 modifiers, SDL_Scancode key);

    // --------------- Mouse ----------------

    // --- mouse buttons  ---
    bool IsMouseButtonPressed(U32 button);
    bool IsMouseButtonDown(U32 button);
    bool IsMouseButtonReleased(U32 button);
    bool IsMouseButtonUp(U32 button);

    // --- mouse movement  ---
    float GetMouseX();
    float GetMouseY();
    float GetMouseDeltaX();
    float GetMouseDeltaY();
    float GetMouseWheelX();
    float GetMouseWheelY();


    // is done by InitKeyCodes but can be called separatyl
    void RegisterInputConstants();
}
