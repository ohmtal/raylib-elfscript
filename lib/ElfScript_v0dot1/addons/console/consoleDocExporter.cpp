//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// ConsoleDocExporter for:
//      Namespace::dumpClasses( dumpScript, dumpEngine );
//       Namespace::dumpFunctions( dumpScript, dumpEngine );
//-----------------------------------------------------------------------------
#include "platform/platform.h"
#include "console/console.h"

#include "core/tAlgorithm.h"

#include "core/strings/findMatch.h"
#include "console/consoleInternal.h"
#include "console/consoleObject.h"
#include "core/frameAllocator.h"
#include "console/engineAPI.h"
#include "core/stream/fileStream.h"

namespace ConsoleExporter {

Vector<String> gConsoleLines;
// Buffer for expanding script filenames.
static char buffer[1024];

//-----------------------------------------------------------------------------
void ConsoleExportLogger(U32 level, const char *consoleLine) {
    if (!consoleLine || consoleLine[0] == '\0') return;
    gConsoleLines.push_back(consoleLine);
}

//-----------------------------------------------------------------------------
void BeginConsoleLines() {

    gConsoleLines.setSize(4000); // enough ?
    gConsoleLines.clear();
    Con::addConsumer(ConsoleExportLogger);
}

//-----------------------------------------------------------------------------
void EndConsoleLines() {
    Con::removeConsumer(ConsoleExportLogger);
    gConsoleLines.clear();
    // remove the memory from begin ....
    gConsoleLines.setSize(0);
}

//-----------------------------------------------------------------------------
bool ExportConsoleLines(const char* fileName, bool forDoxyGen = false, bool append = false) {
    if (gConsoleLines.size() == 0) return false;
    if(Con::expandScriptFilename(buffer, sizeof(buffer), fileName))
        fileName = buffer;

    FileStream *strm = NULL;

    if (fileName)
    {
        if ((strm = FileStream::createAndOpen(fileName, append ? Torque::FS::File::ReadWrite : Torque::FS::File::Write)) == NULL)
        {
            Con::errorf(ConsoleLogEntry::General, "Unable to open file '%s for writing.", fileName);
            return false;
        }
        if (append)
            strm->setPosition(strm->getStreamSize());
    }
    // sanity ...
    if (!strm) return false;

    for (S32 i = 0; i < gConsoleLines.size(); i++) {
        if (!forDoxyGen) {
             gConsoleLines[i].replace("((", "(");
             gConsoleLines[i].replace("))", ")");
             gConsoleLines[i].replace("virtual ", "");
        }
        gConsoleLines[i] += "\n";
        strm->writeText(gConsoleLines[i].c_str());
    }
    strm->close();
    delete strm;

    return true;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
DefineEngineFunction( exportConsoleDocu, bool, ( String fileName, bool forDoxyGen, bool append, bool dumpScript, bool dumpEngine), ( false,false, true, true ),
                      "@brief Export all declared console classes to the console.\n\n"
                      "@param dumpScript Optional parameter specifying whether or not classes defined in script should be dumped.\n"
                      "@param dumpEngine Optional parameter specifying whether or not classes defined in the engine should be dumped.\n"
                      "@ingroup Docu")
{
    BeginConsoleLines();
    Namespace::dumpClasses( dumpScript, dumpEngine );
    Namespace::dumpFunctions( dumpScript, dumpEngine );
    bool ok = ExportConsoleLines(fileName, forDoxyGen, append);
    EndConsoleLines();
    return ok;
}



} //namespace


