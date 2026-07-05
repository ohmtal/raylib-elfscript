//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#pragma once

#include "platform/types.h"

namespace elfWrapper {

    //NOTE  this is from CMDScan.cpp but used in str.h!
    void expandEscape(char *dest, const char *src);
    bool collapseEscape(char *buf);
}

using namespace elfWrapper;
