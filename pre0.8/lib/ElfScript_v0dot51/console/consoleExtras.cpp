//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "console.h"
#include "consoleTypes.h"
#include "engineAPI.h"
#include "consoleExtras.h"

namespace Con { }

// was a test if i can speed up lookups .. - not
// DefineEngineFunction(defS32, void, (String varName, S32 value),(0),"Add as integer Constant") {
//     Con::dynamicConst32Storage.push_back(value);
//     S32* permanentPointer = &Con::dynamicConst32Storage.back();
//     Con::addVariable(
//         varName.c_str(),
//                         TypeS32,
//                         permanentPointer,
//                         ""
//     );
// }
//
// DefineEngineFunction(removeVariable, bool, (String varName),,"Remove a variable") {
//     return Con::removeVariable(varName);
// }


