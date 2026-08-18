//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Core: SDL_init, FIXME **events**
//-----------------------------------------------------------------------------
#include <SDL3/SDL.h>

#include "console/scriptPreprocessor.h"
#include "console/engineAPI.h"
#include "console/consoleExtras.h" // for PoD types - dont forget to add the .cpp to your build

namespace ElfSDL3 {

void RegisterCoreConstants() {
    using namespace Con;

    REGISTER_CONST_S32(SDL_INIT_AUDIO      ); // 0x00000010u /**< `SDL_INIT_AUDIO` implies `SDL_INIT_EVENTS` */
    REGISTER_CONST_S32(SDL_INIT_VIDEO      ); // 0x00000020u /**< `SDL_INIT_VIDEO` implies `SDL_INIT_EVENTS`, should be initialized on the main thread */
    REGISTER_CONST_S32(SDL_INIT_JOYSTICK   ); // 0x00000200u /**< `SDL_INIT_JOYSTICK` implies `SDL_INIT_EVENTS` */
    REGISTER_CONST_S32(SDL_INIT_HAPTIC     ); // 0x00001000u
    REGISTER_CONST_S32(SDL_INIT_GAMEPAD    ); // 0x00002000u /**< `SDL_INIT_GAMEPAD` implies `SDL_INIT_JOYSTICK` */
    REGISTER_CONST_S32(SDL_INIT_EVENTS     ); // 0x00004000u
    REGISTER_CONST_S32(SDL_INIT_SENSOR     ); // 0x00008000u /**< `SDL_INIT_SENSOR` implies `SDL_INIT_EVENTS` */
    REGISTER_CONST_S32(SDL_INIT_CAMERA     ); // 0x00010000u /**< `SDL_INIT_CAMERA` implies `SDL_INIT_EVENTS` */

}

// extern SDL_DECLSPEC bool SDLCALL SDL_Init(SDL_InitFlags flags);
DefineEngineFunction(SDL_Init, bool, (S32 InitFlags), (SDL_INIT_VIDEO | SDL_INIT_AUDIO), "Init SDL default Video and Audio") {
    return SDL_Init(InitFlags);
}

// extern SDL_DECLSPEC void SDLCALL SDL_Quit(void);
DefineEngineFunction(SDL_Quit, void, (), , "Quit SDL") {
    SDL_Quit();
}


// -------- Timer -------------
// extern SDL_DECLSPEC Uint64 SDLCALL SDL_GetTicks(void);
DefineEngineFunction(SDL_GetTicks, U64, (),,"Get the number of milliseconds that have elapsed since the SDL library") {
    return SDL_GetTicks();
}


// extern SDL_DECLSPEC Uint64 SDLCALL SDL_GetTicksNS(void);
DefineEngineFunction(SDL_GetTicksNS, U64, (),,"Get the number of nanoseconds that have elapsed since the SDL library") {
    return SDL_GetTicksNS();
}

// extern SDL_DECLSPEC Uint64 SDLCALL SDL_GetPerformanceCounter(void);
DefineEngineFunction(SDL_GetPerformanceCounter, U64, (),,"Get the current value of the high resolution counter.") {
    return SDL_GetPerformanceCounter();
}

// extern SDL_DECLSPEC Uint64 SDLCALL SDL_GetPerformanceFrequency(void);
DefineEngineFunction(SDL_GetPerformanceFrequency, U64, (),,"Get the count per second of the high resolution counter.") {
    return SDL_GetPerformanceFrequency();
}


// extern SDL_DECLSPEC void SDLCALL SDL_Delay(Uint32 ms);
DefineEngineFunction(SDL_Delay, void, (U32 ms),,"Wait a specified number of milliseconds before returning.") {
    SDL_Delay(ms);
}

// extern SDL_DECLSPEC void SDLCALL SDL_DelayNS(Uint64 ns);
DefineEngineFunction(SDL_DelayNS, void, (U64 ns),,"Wait a specified number of nanoseconds before returning.") {
    SDL_Delay(ns);
}

// extern SDL_DECLSPEC void SDLCALL SDL_DelayPrecise(Uint64 ns);
DefineEngineFunction(SDL_DelayPrecise, void, (U64 ns),,"Wait a specified number of nanoseconds before returning.") {
    SDL_DelayPrecise(ns);
}



} // namespace
