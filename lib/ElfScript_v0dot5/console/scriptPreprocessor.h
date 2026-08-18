//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------#pragma once
#include <string>
#include "console/console.h"
namespace Con {


    /// XXTH ElfScript preprocessor:
    void setScriptConstant(std::string key, S32 value);
    void setScriptConstant(std::string key, U32 value);
    void setScriptConstant(std::string key, U64 value);
    void setScriptConstant(std::string key, F64 value);
    void setScriptConstant(std::string key, std::string value);
    std::string preprocessTorqueScript(const char* inString);

    #define REGISTER_CONST(constName) setScriptConstant(#constName, constName)
    #define REGISTER_CONST_S32(constName) setScriptConstant(#constName, (S32)constName)
    #define REGISTER_CONST_U32(constName) setScriptConstant(#constName, (U32)constName)
    #define REGISTER_CONST_U64(constName) setScriptConstant(#constName, (U64)constName)
    #define REGISTER_CONST_F64(constName) setScriptConstant(#constName, (F64)constName)
}
