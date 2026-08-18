//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Local Variable (%) Power :D ... also added  global ($) but kept the nameing
//-----------------------------------------------------------------------------
#pragma once

class ConsoleValue;
namespace ElfScript {
    const char* getConsoleValueTypeName(S32 type);
    S32 findLocalVarRegisterInCurrentScope(const char* variableName);

    void varDumpGlobals(const char* variableName);
    void varDumpLocals(const char* variableName);
    void varDumpDynamicField(const char* variableName);
    void dumpAllLocalVariables();
    void dumpAllGlobalVariables();


    bool getLocalVariable(const char* variableName, ConsoleValue* stack, S32& reg);
    ConsoleValue* getLocalVariable(const char* variableName );

    bool setLocalFloat(const char* variableName, F64 value);
    bool setLocalInt(const char* variableName, S64 value);
    bool setLocalString(const char* variableName, const char* value);

    F64 getLocalFloat(const char* variableName);
    S64 getLocalInt(const char* variableName);
    const char* getLocalString(const char* variableName);


#ifdef ENABLE_CONSOLE_VECTOR
    ConsoleVector getLocalVector(const char* variableName);
    bool setLocalVector(const char* variableName, ConsoleVector& value);
#endif
}
