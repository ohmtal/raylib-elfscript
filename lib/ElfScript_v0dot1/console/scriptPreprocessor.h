#pragma once
#include <string>
namespace Con {
    /// XXTH ElfScript preprocessor:
    void setScriptConstant(std::string key, S32 value);
    void setScriptConstant(std::string key, std::string value);
    std::string preprocessTorqueScript(const char* inString);

}
