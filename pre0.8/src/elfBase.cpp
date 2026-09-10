//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// NOTE: i started porting here and broke in parts like the modules are named
//       thats why here is not much left.
//-----------------------------------------------------------------------------
#include "raylib.h"
#include "console/console.h"

// -----------------------------------------------------------------------------
// TraceLog raylib log to Con::.. log.
// -----------------------------------------------------------------------------
void CustomTraceLog(int msgType, const char *text, va_list args)
{

    ConsoleLogEntry::Level level = ConsoleLogEntry::Normal;

    switch (msgType)
    {
        case LOG_INFO:    level = ConsoleLogEntry::Normal; break;
        case LOG_WARNING: level = ConsoleLogEntry::Warning; break;
        case LOG_ERROR:   level = ConsoleLogEntry::Error; break;
        case LOG_FATAL:   level = ConsoleLogEntry::Error; break;
        case LOG_DEBUG:   level = ConsoleLogEntry::Normal; break; // Oder ein eigener Debug-Typ
        default: return;
    }


    Con::LogEntry(level, ConsoleLogEntry::General, text, args);
}



