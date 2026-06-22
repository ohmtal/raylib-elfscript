//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#include "raylib.h"
#include "console/engineAPI.h"
#include "ConsoleTypes.h"
#include "console/scriptPreprocessor.h"
#include "ConsoleTypes.h"



//the lazy (long build time) way or define KeyboardKey (348)
// #define MAGIC_ENUM_RANGE_MIN 0
// #define MAGIC_ENUM_RANGE_MAX 348
// compile takes ages! #define MAGIC_ENUM_RANGE_MAX 65536
#include "console/consoleExtras.h" // registerEnum
#include <format>

// -----------------------------------------------------------------------------
// CONST
// -----------------------------------------------------------------------------
void registerRaylibColors() {
    const String prefix = "";

    const std::vector<std::pair<String, Color>> colors = {
        {"LIGHTGRAY", LIGHTGRAY},
        {"GRAY", GRAY},
        {"DARKGRAY", DARKGRAY},
        {"YELLOW", YELLOW},
        {"GOLD", GOLD},
        {"ORANGE", ORANGE},
        {"PINK", PINK},
        {"RED", RED},
        {"MAROON", MAROON},
        {"GREEN", GREEN},
        {"LIME", LIME},
        {"DARKGREEN", DARKGREEN},
        {"SKYBLUE", SKYBLUE},
        {"BLUE", BLUE},
        {"DARKBLUE", DARKBLUE},
        {"PURPLE", PURPLE},
        {"VIOLET", VIOLET},
        {"DARKPURPLE", DARKPURPLE},
        {"BEIGE", BEIGE},
        {"BROWN", BROWN},
        {"DARKBROWN", DARKBROWN},
        {"WHITE", WHITE},
        {"BLACK", BLACK},
        {"BLANK", BLANK},
        {"MAGENTA", MAGENTA},
        {"RAYWHITE", RAYWHITE}
    };


    for (std::size_t i = 0; i < colors.size(); ++i) {
        // 1. Namen zusammenbauen
        String fullName = prefix + colors[i].first;
        Color value = static_cast<Color>(colors[i].second);
        ConsoleBaseType* type = ConsoleBaseType::getType(TypeColor);

        if (type) {
            const char* colorStrP = type->getData(&value, nullptr, 0);
            std::string colorString = std::format("\"{}\"", colorStrP);
            Con::setScriptConstant(fullName.c_str(), colorString );
            // Con::printf("DEBUG key value: %s => %s", fullName.c_str(), colorString.c_str());
        }
    }


    // static std::vector<Color> storedColors;
    // storedColors.resize(colors.size());

    // for (std::size_t i = 0; i < colors.size(); ++i) {
    //     // storedColors[i] = colors[i].second;
    //     String fullName = prefix + colors[i].first;
    //
    //     Color value = static_cast<Color>(colors[i].second);
    //     Con::setScriptConstant(fullName.c_str(), ConsoleTypeTypeColor::getData(....)); ///opt/raylib-elfscript/src/interface/elfEnum.cpp:63:50: error: ‘ConsoleTypeTypeColor’ has not been declared
    //     // Con::addConstant(
    //     //     fullName.c_str(),
    //     //                  TypeColor,
    //     //                  &storedColors[i],
    //     //                  ""
    //     // );
    // }
}



// -----------------------------------------------------------------------------
// ENUM
// -----------------------------------------------------------------------------
void registerRaylibConfigFlags() {
    const String prefix = "";

    const std::vector<std::pair<String, S32>> flags = {
        {"FLAG_VSYNC_HINT", FLAG_VSYNC_HINT},
        {"FLAG_FULLSCREEN_MODE", FLAG_FULLSCREEN_MODE},
        {"FLAG_WINDOW_RESIZABLE", FLAG_WINDOW_RESIZABLE},
        {"FLAG_WINDOW_UNDECORATED", FLAG_WINDOW_UNDECORATED},
        {"FLAG_WINDOW_HIDDEN", FLAG_WINDOW_HIDDEN},
        {"FLAG_WINDOW_MINIMIZED", FLAG_WINDOW_MINIMIZED},
        {"FLAG_WINDOW_MAXIMIZED", FLAG_WINDOW_MAXIMIZED},
        {"FLAG_WINDOW_UNFOCUSED", FLAG_WINDOW_UNFOCUSED},
        {"FLAG_WINDOW_TOPMOST", FLAG_WINDOW_TOPMOST},
        {"FLAG_WINDOW_ALWAYS_RUN", FLAG_WINDOW_ALWAYS_RUN},
        {"FLAG_WINDOW_TRANSPARENT", FLAG_WINDOW_TRANSPARENT},
        {"FLAG_WINDOW_HIGHDPI", FLAG_WINDOW_HIGHDPI},
        {"FLAG_WINDOW_MOUSE_PASSTHROUGH", FLAG_WINDOW_MOUSE_PASSTHROUGH},
        {"FLAG_BORDERLESS_WINDOWED_MODE", FLAG_BORDERLESS_WINDOWED_MODE},
        {"FLAG_MSAA_4X_HINT", FLAG_MSAA_4X_HINT},
        {"FLAG_INTERLACED_HINT", FLAG_INTERLACED_HINT}
    };


    // static std::vector<S32> storedValues;
    // storedValues.resize(flags.size());

    for (std::size_t i = 0; i < flags.size(); ++i) {
        // storedValues[i] = flags[i].second;
        String fullName = prefix + flags[i].first;
        S32 value = static_cast<S32>(flags[i].second);
        Con::setScriptConstant(fullName.c_str(), value);

        // Con::addConstant(
        //     fullName.c_str(),
        //                  TypeS32,
        //                  &storedValues[i],
        //                  ""
        // );
    }
}

void registerRaylibKeyboardKeys() {
    const String prefix = "";

    const std::vector<std::pair<String, S32>> keys = {
        // Alphanumeric keys
        {"KEY_APOSTROPHE", KEY_APOSTROPHE},
        {"KEY_COMMA", KEY_COMMA},
        {"KEY_MINUS", KEY_MINUS},
        {"KEY_PERIOD", KEY_PERIOD},
        {"KEY_SLASH", KEY_SLASH},
        {"KEY_ZERO", KEY_ZERO},
        {"KEY_ONE", KEY_ONE},
        {"KEY_TWO", KEY_TWO},
        {"KEY_THREE", KEY_THREE},
        {"KEY_FOUR", KEY_FOUR},
        {"KEY_FIVE", KEY_FIVE},
        {"KEY_SIX", KEY_SIX},
        {"KEY_SEVEN", KEY_SEVEN},
        {"KEY_EIGHT", KEY_EIGHT},
        {"KEY_NINE", KEY_NINE},
        {"KEY_SEMICOLON", KEY_SEMICOLON},
        {"KEY_EQUAL", KEY_EQUAL},
        {"KEY_A", KEY_A},
        {"KEY_B", KEY_B},
        {"KEY_C", KEY_C},
        {"KEY_D", KEY_D},
        {"KEY_E", KEY_E},
        {"KEY_F", KEY_F},
        {"KEY_G", KEY_G},
        {"KEY_H", KEY_H},
        {"KEY_I", KEY_I},
        {"KEY_J", KEY_J},
        {"KEY_K", KEY_K},
        {"KEY_L", KEY_L},
        {"KEY_M", KEY_M},
        {"KEY_N", KEY_N},
        {"KEY_O", KEY_O},
        {"KEY_P", KEY_P},
        {"KEY_Q", KEY_Q},
        {"KEY_R", KEY_R},
        {"KEY_S", KEY_S},
        {"KEY_T", KEY_T},
        {"KEY_U", KEY_U},
        {"KEY_V", KEY_V},
        {"KEY_W", KEY_W},
        {"KEY_X", KEY_X},
        {"KEY_Y", KEY_Y},
        {"KEY_Z", KEY_Z},
        {"KEY_LEFT_BRACKET", KEY_LEFT_BRACKET},
        {"KEY_BACKSLASH", KEY_BACKSLASH},
        {"KEY_RIGHT_BRACKET", KEY_RIGHT_BRACKET},
        {"KEY_GRAVE", KEY_GRAVE},
        // Function keys
        {"KEY_SPACE", KEY_SPACE},
        {"KEY_ESCAPE", KEY_ESCAPE},
        {"KEY_ENTER", KEY_ENTER},
        {"KEY_TAB", KEY_TAB},
        {"KEY_BACKSPACE", KEY_BACKSPACE},
        {"KEY_INSERT", KEY_INSERT},
        {"KEY_DELETE", KEY_DELETE},
        {"KEY_RIGHT", KEY_RIGHT},
        {"KEY_LEFT", KEY_LEFT},
        {"KEY_DOWN", KEY_DOWN},
        {"KEY_UP", KEY_UP},
        {"KEY_PAGE_UP", KEY_PAGE_UP},
        {"KEY_PAGE_DOWN", KEY_PAGE_DOWN},
        {"KEY_HOME", KEY_HOME},
        {"KEY_END", KEY_END},
        {"KEY_CAPS_LOCK", KEY_CAPS_LOCK},
        {"KEY_SCROLL_LOCK", KEY_SCROLL_LOCK},
        {"KEY_NUM_LOCK", KEY_NUM_LOCK},
        {"KEY_PRINT_SCREEN", KEY_PRINT_SCREEN},
        {"KEY_PAUSE", KEY_PAUSE},
        {"KEY_F1", KEY_F1},
        {"KEY_F2", KEY_F2},
        {"KEY_F3", KEY_F3},
        {"KEY_F4", KEY_F4},
        {"KEY_F5", KEY_F5},
        {"KEY_F6", KEY_F6},
        {"KEY_F7", KEY_F7},
        {"KEY_F8", KEY_F8},
        {"KEY_F9", KEY_F9},
        {"KEY_F10", KEY_F10},
        {"KEY_F11", KEY_F11},
        {"KEY_F12", KEY_F12},
        {"KEY_LEFT_SHIFT", KEY_LEFT_SHIFT},
        {"KEY_LEFT_CONTROL", KEY_LEFT_CONTROL},
        {"KEY_LEFT_ALT", KEY_LEFT_ALT},
        {"KEY_LEFT_SUPER", KEY_LEFT_SUPER},
        {"KEY_RIGHT_SHIFT", KEY_RIGHT_SHIFT},
        {"KEY_RIGHT_CONTROL", KEY_RIGHT_CONTROL},
        {"KEY_RIGHT_ALT", KEY_RIGHT_ALT},
        {"KEY_RIGHT_SUPER", KEY_RIGHT_SUPER},
        {"KEY_KB_MENU", KEY_KB_MENU},
        // Keypad keys
        {"KEY_KP_0", KEY_KP_0},
        {"KEY_KP_1", KEY_KP_1},
        {"KEY_KP_2", KEY_KP_2},
        {"KEY_KP_3", KEY_KP_3},
        {"KEY_KP_4", KEY_KP_4},
        {"KEY_KP_5", KEY_KP_5},
        {"KEY_KP_6", KEY_KP_6},
        {"KEY_KP_7", KEY_KP_7},
        {"KEY_KP_8", KEY_KP_8},
        {"KEY_KP_9", KEY_KP_9},
        {"KEY_KP_DECIMAL", KEY_KP_DECIMAL},
        {"KEY_KP_DIVIDE", KEY_KP_DIVIDE},
        {"KEY_KP_MULTIPLY", KEY_KP_MULTIPLY},
        {"KEY_KP_SUBTRACT", KEY_KP_SUBTRACT},
        {"KEY_KP_ADD", KEY_KP_ADD},
        {"KEY_KP_ENTER", KEY_KP_ENTER},
        {"KEY_KP_EQUAL", KEY_KP_EQUAL},
        // Android keycodes
        {"KEY_BACK", KEY_BACK},
        {"KEY_MENU", KEY_MENU},
        {"KEY_VOLUME_UP", KEY_VOLUME_UP},
        {"KEY_VOLUME_DOWN", KEY_VOLUME_DOWN}
    };

    // static std::vector<S32> storedValues;
    // storedValues.resize(keys.size());

    for (std::size_t i = 0; i < keys.size(); ++i) {
        // storedValues[i] = keys[i].second;
        String fullName = prefix + keys[i].first;

        S32 value = static_cast<S32>(keys[i].second);
        Con::setScriptConstant(fullName.c_str(), value);

        // Con::addConstant(
        //     fullName.c_str(),
        //                  TypeS32,
        //                  &storedValues[i],
        //                  ""
        // );
    }
}

void registerRaylibGestures() {
    const String prefix = "";

    const std::vector<std::pair<String, S32>> gestures = {
        {"GESTURE_NONE", GESTURE_NONE},
        {"GESTURE_TAP", GESTURE_TAP},
        {"GESTURE_DOUBLETAP", GESTURE_DOUBLETAP},
        {"GESTURE_HOLD", GESTURE_HOLD},
        {"GESTURE_DRAG", GESTURE_DRAG},
        {"GESTURE_SWIPE_RIGHT", GESTURE_SWIPE_RIGHT},
        {"GESTURE_SWIPE_LEFT", GESTURE_SWIPE_LEFT},
        {"GESTURE_SWIPE_UP", GESTURE_SWIPE_UP},
        {"GESTURE_SWIPE_DOWN", GESTURE_SWIPE_DOWN},
        {"GESTURE_PINCH_IN", GESTURE_PINCH_IN},
        {"GESTURE_PINCH_OUT", GESTURE_PINCH_OUT}
    };

    // static std::vector<S32> storedValues;
    // storedValues.resize(gestures.size());

    for (std::size_t i = 0; i < gestures.size(); ++i) {
        // storedValues[i] = gestures[i].second;
        String fullName = prefix + gestures[i].first;

        S32 value = static_cast<S32>(gestures[i].second);
        Con::setScriptConstant(fullName.c_str(), value);

        // Con::addConstant(
        //     fullName.c_str(),
        //                  TypeS32,
        //                  &storedValues[i],
        //                  ""
        // );
    }
}


void initEnum() {
    registerRaylibColors();
    // -----
    registerRaylibKeyboardKeys();
    // Con::registerEnumS32<KeyboardKey>("");
    registerRaylibConfigFlags();
    // Con::registerEnumS32<ConfigFlags>(""); //values to high!! max -128 / 128 with magic enum
    Con::registerEnumS32<TraceLogLevel>("");
    Con::registerEnumS32<MouseButton>("");
    Con::registerEnumS32<MouseCursor>("");
    Con::registerEnumS32<GamepadButton>("");
    Con::registerEnumS32<GamepadAxis>("");
    Con::registerEnumS32<MaterialMapIndex>("");
    Con::registerEnumS32<ShaderLocationIndex>("");
    Con::registerEnumS32<ShaderUniformDataType>("");
    Con::registerEnumS32<ShaderAttributeDataType>("");
    Con::registerEnumS32<PixelFormat>("");
    Con::registerEnumS32<TextureFilter>("");
    Con::registerEnumS32<TextureWrap>("");
    Con::registerEnumS32<CubemapLayout>("");
    Con::registerEnumS32<FontType>("");
    Con::registerEnumS32<BlendMode>("");
    // values to high !!! Con::registerEnumS32<Gesture>("");
    registerRaylibGestures();
    Con::registerEnumS32<CameraMode>("");
    Con::registerEnumS32<CameraProjection>("");
    Con::registerEnumS32<NPatchLayout>("");
}
