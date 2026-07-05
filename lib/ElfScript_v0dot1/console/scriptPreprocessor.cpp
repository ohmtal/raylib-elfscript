//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Script preprocessor using regex.
// Torquescript have no concept to use "fast" constants bevor i start
// changing bison/ast with adding this i try this first.
// NOTE: used in: Con::EvalResult CodeBlock::compileExec(StringTableEntry fileName, const char *inString, bool noCalls, S32 setFrame)
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// #define _LOOP_COUNT_ 5000
// for (%i = 0; %i < _LOOP_COUNT_; %i++) => for (%i = 0; %i < 500; %i++)
// which use the bytecode than as constant which is much faster than using
// variables.
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <vector>
#include <algorithm>
#include <core/strings/stringFunctions.h>

#include <cctype>

#include "engineAPI.h"

namespace Con {

    //----------------------------------------------------------------------
// Global table that persists across multiple exec() calls
std::unordered_map<std::string, std::string> gScriptConstants;

//----------------------------------------------------------------------
void setScriptConstant(std::string key, S32 value) {
    StringBuilder str;
    str.format("%d", value);
    gScriptConstants[key] = str.end();
}
//----------------------------------------------------------------------
void setScriptConstant(std::string key, std::string value) {
    gScriptConstants[key] = value;
}
//----------------------------------------------------------------------

DefineEngineFunction(dumpScriptConstants, void, (String filter), (""),
                     "(String filter) - Dumps the script constants table to the console. Using filter for keys if not empty.")
{
    if (gScriptConstants.empty())
    {
        Con::printf("Script constants table is empty.");
        return;
    }

    bool useFilter = !filter.isEmpty();
    U32 matchCount = 0;

    Con::printf("--- Script Constants Dump ---");

    for (const auto& pair : gScriptConstants)
    {
        if (useFilter)
        {
            if (!dStristr(pair.first.c_str(), filter))
                continue;
        }

        Con::printf("  %s = %s", pair.first.c_str(), pair.second.c_str());
        matchCount++;
    }

    if (useFilter)
    {
        Con::printf("--- End of Dump (%u of %zu items matched) ---", matchCount, gScriptConstants.size());
    }
    else
    {
        Con::printf("--- End of Dump (%zu items) ---", gScriptConstants.size());
    }
}
//----------------------------------------------------------------------

/**
 * replace constant in code
 * checks word boundary (\b).
 *
 * @param sourceCode the code
 * @param constants the map
 * @return modified code
 */
std::string replaceConstantsSinglePass(const std::string& sourceCode,
                                       const std::unordered_map<std::string, std::string>& constants)
{
    std::string result;
    result.reserve(sourceCode.size());

    std::string currentWord;

    for (size_t i = 0; i <= sourceCode.size(); ++i) {
        char c = (i < sourceCode.size()) ? sourceCode[i] : '\0';

        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
            currentWord += c;
        } else {
            if (!currentWord.empty()) {
                auto it = constants.find(currentWord);
                if (it != constants.end()) {
                    result += it->second;
                } else {
                    result += currentWord;
                }
                currentWord.clear();
            }

            if (c != '\0') {
                result += c;
            }
        }
    }

    return result;
}

//----------------------------------------------------------------------
std::string preprocessTorqueScript(const char* inString) {
    if (inString == nullptr) return "";
    bool foundHash = dStrchr(inString, '#') != nullptr;

    std::string outputCode;

    if (foundHash) {
        std::istringstream stream(inString);
        std::string line;

        // RegEx to find: #define NAME VALUE
        std::regex defineRegex(R"(^\s*#define\s+([A-Za-z_][A-Za-z0-9_]*)\s+(.+?)\s*$)");

        while (std::getline(stream, line)) {

            std::smatch match;

            if (dStrchr(inString, '#') != nullptr && std::regex_match(line, match, defineRegex)) {
                std::string name = match[1].str();
                std::string value = match[2].str();
                gScriptConstants[name] = value;
                // add an empty lime
                outputCode += "\n";
            } else {
                // Keep normal code line
                outputCode += line + "\n";
            }
        }

    } //if found hash
    else {
        outputCode = inString;
    }

    outputCode = replaceConstantsSinglePass(outputCode, gScriptConstants);

    return outputCode;
}
//----------------------------------------------------------------------


} //Con
