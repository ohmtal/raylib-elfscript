//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#pragma once

#include <iostream>
#include <deque>
#include <string>

#include "ext/magic_enum.hpp"
#include "console.h"
#include "consoleTypes.h"
#include "scriptPreprocessor.h"


namespace Con {

    // -------------------------------------------------------------------------
    /*
     * Register a enum(S32) to global variable with addConstent
     * NOTE only for interger types .. can be enhanced i guess ..
     */


    inline std::deque<S32> dynamicConst32Storage;

    template <typename TEnum>
    void registerEnumS32(const std::string& prefix, bool asConstantVariable = false) {
        constexpr std::size_t count = magic_enum::enum_count<TEnum>();
        constexpr auto enumValues = magic_enum::enum_values<TEnum>();
        constexpr auto enumNames = magic_enum::enum_names<TEnum>();

        S32 value = 0;
        for (std::size_t i = 0; i < count; ++i) {
            value = static_cast<S32>(enumValues[i]);

#ifndef ELFSCRIPT_PREPROCESSOR
    asConstantVariable = true;
#endif
            if (!asConstantVariable) {
                std::string fullName = prefix + std::string(enumNames[i]);
                Con::setScriptConstant(fullName, value);

            } else {
                dynamicConst32Storage.push_back(static_cast<S32>(enumValues[i]));
                S32* permanentPointer = &dynamicConst32Storage.back();
                std::string fullName = prefix + std::string(enumNames[i]);

                Con::addConstant(
                    fullName.c_str(),
                                 TypeS32,
                                 permanentPointer,
                                 ""
                );
            }

        }
    }

    // --------------------------------------------------------------------------------------------

} //namespace Con


