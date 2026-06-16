#include "raylib.h"
#include "main/engineGlue.h"
#include "console/script.h"
#include "console/engineAPI.h"




bool gShutDownRequest = false;
extern void initEnum();
extern void CustomTraceLog(int msgType, const char *text, va_list args);

int main(void)
{
    engineGlue::init(nullptr, ""); //fixme logfunc
    initEnum();


    if (!Con::executeFile("assets/main.cs")) { //fixme with command line
        Con::errorf("main script not found.");
        return 1;
    }

    if (!Con::isFunction("MainUpdate")) {
        Con::errorf("MainUpdate function is missing!");
        return 1;
    }

    SetTraceLogCallback(CustomTraceLog);
    ConsoleValue initResult = Con::executef("MainInit");
    if (initResult.getBool() == false) {
        Con::errorf("init failed");
        return 1;
    }

    // --------- advance time for scheduler this should be placed in the main loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Con::executef("MainUpdate");
        engineGlue::process(GetFrameTime());
        if (gShutDownRequest) break;
    }

    Con::executef("MainShutdown");
    // -------- finallize
    engineGlue::shutDown();

    return 0;
}
