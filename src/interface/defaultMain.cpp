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


String gScriptFile = "assets/main.cs";
bool gShutDownRequest = false;
bool gNoDefaultCalls  = false;
bool gEnableConsole = false;

extern void initEnum();
extern void CustomTraceLog(int msgType, const char *text, va_list args);
namespace ElfResource { extern void shutDown(); }


int argParser(int argc, char* argv[]) {

    String argStr;
    // argv[0] is program name
    for (int i = 1; i < argc; ++i) {
        if (!argv[i]) continue;
        argStr = argv[i];

        if (argStr.equal("--noloop")) {
            gNoDefaultCalls = false;
            continue;
        }
        if (argStr.equal("--console")) {
            gEnableConsole = true;
            continue;
        }
        // filename test
        if (argStr.equal("--script")) {
            if (i + 1 < argc) {
                gScriptFile= argv[++i];
                dPrintf("Custom Script File: %s\n", gScriptFile.c_str());
            } else {
                dPrintf("--script but no file parameter usage: --script myFile.cs\n");
                return 1;
            }
            continue;
        }

    } //for ...
    return 0;
}

int defaultMain(int argc, char* argv[])
{
    argParser(argc, argv);
    engineGlue::init(nullptr, GetApplicationDirectory()); // FIXME command line path => --path
    initEnum();
    SetTraceLogCallback(CustomTraceLog);



    if (!Con::executeFile(gScriptFile.c_str())) { //fixme with command line
        Con::errorf("main script not found.");
        return 1;
    }

    if (!gNoDefaultCalls) {

        #if defined(__unix__)
        // console test:
        if (gEnableConsole) {
            StdConsole::create();
            stdConsole->enable(!gShutDownRequest);
            stdConsole->enableInput(!gShutDownRequest);
        }

        #endif

        if (!Con::isFunction("MainLoop")) {
            Con::errorf("MainLoop function is missing!");
            return 1;
        }

        ConsoleValue initResult = Con::executef("MainInit");
        if (initResult.getBool() == false) {
            Con::errorf("init failed");
            return 1;
        }


        // --------- advance time for scheduler this should be placed in the main loop
        while (!WindowShouldClose())    // Detect window close button or ESC key
        {
            Con::executef("MainLoop");
            #if defined(__unix__)
            if (gEnableConsole && stdConsole) stdConsole->process();
            #endif
            engineGlue::process(GetFrameTime());
            if (gShutDownRequest) break;
        }

        Con::executef("MainShutdown");
    }


    // -------- finallize
    ElfResource::shutDown();
    engineGlue::shutDown();

    return 0;
}
