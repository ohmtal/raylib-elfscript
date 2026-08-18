#pragma once
#include "console/console.h"
#include "console/sim.h"

namespace engineGlue
{
    inline String ScriptDirectory = "";
    inline String ScriptFile = "assets/main.elf";
    // default argParser used to set --script and --dir combinded with
    int argParser(int argc, char* argv[]);

    void DefaultLogger(U32 level, const char *consoleLine);
    static ConsumerCallback mLogger = DefaultLogger;

    void init( ConsumerCallback LogFunc = nullptr, String workingDirectory = "");

    // SimTime U32 ms since last Loop
    void process(SimTime delta);

    void shutDown();
} //engineGlue
