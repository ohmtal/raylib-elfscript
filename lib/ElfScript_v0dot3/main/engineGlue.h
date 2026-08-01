#pragma once
#include "console/console.h"
#include "console/sim.h"

namespace engineGlue
{

    void DefaultLogger(U32 level, const char *consoleLine);
    static ConsumerCallback mLogger = DefaultLogger;

    void init( ConsumerCallback LogFunc = nullptr, String workingDirectory = "");

    // SimTime U32 ms since last Loop
    void process(SimTime delta);

    void shutDown();
} //engineGlue
