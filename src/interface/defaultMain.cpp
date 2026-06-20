//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// FIXME emscripten loop
// FIXME commandline parameter for path and script
//-----------------------------------------------------------------------------
#include "raylib.h"
#include "main/engineGlue.h"
#include "console/script.h"
#include "console/engineAPI.h"

#if defined(__unix__)
#include <addons/shellConsole/POSIXStdConsole.h>
#endif



bool gShutDownRequest = false;
extern void initEnum();
extern void CustomTraceLog(int msgType, const char *text, va_list args);
namespace ElfResource { extern void shutDown(); }

int defaultMain(void)
{
    engineGlue::init(nullptr, GetApplicationDirectory()); // command line path
    initEnum();


    if (!Con::executeFile("assets/main.cs")) { //fixme with command line
        Con::errorf("main script not found.");
        return 1;
    }

    if (!Con::isFunction("MainLoop")) {
        Con::errorf("MainLoop function is missing!");
        return 1;
    }

    SetTraceLogCallback(CustomTraceLog);
    ConsoleValue initResult = Con::executef("MainInit");
    if (initResult.getBool() == false) {
        Con::errorf("init failed");
        return 1;
    }

    #if defined(__unix__)
    // console test:
    StdConsole::create();
    stdConsole->enable(!gShutDownRequest);
    stdConsole->enableInput(!gShutDownRequest);
    #endif

    // --------- advance time for scheduler this should be placed in the main loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Con::executef("MainLoop");
        #if defined(__unix__)
        stdConsole->process();
        #endif
        engineGlue::process(GetFrameTime());
        if (gShutDownRequest) break;
    }

    Con::executef("MainShutdown");
    // -------- finallize
    ElfResource::shutDown();
    engineGlue::shutDown();

    return 0;
}
