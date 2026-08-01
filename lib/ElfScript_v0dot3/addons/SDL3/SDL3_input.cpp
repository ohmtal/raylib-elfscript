//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// SDL3 Keyboard (via scancodes) and Mouse event handling
//-----------------------------------------------------------------------------
#include "console/scriptPreprocessor.h"
#include "console/engineAPI.h"

#include <SDL3/SDL.h>
#include <console/script.h>

#ifndef ElfSDL3_DISABLE_POLL
#define ElfSDL3_ENABLE_POLL
#endif


    IMPLEMENT_GLOBAL_CALLBACK(onSDLKeyBoardEvent,void
        , (S32 scancode, S32 modifiers, bool isKeyDown, bool isKeyRepeat)
        , (scancode, modifiers, isKeyDown, isKeyRepeat)
        ,"Event triggered when a key is pressed or released." );

    // to many calles ... disabled
    // IMPLEMENT_GLOBAL_CALLBACK(onSDLMouseMotionEvent,void
    // , (F32 mouseX, F32 mouseY, F32 DeltaX, F32 DeltaY)
    // , ( mouseX, mouseY, DeltaX, DeltaY)
    // ,"Event triggered when mouse is moved" );

    IMPLEMENT_GLOBAL_CALLBACK(onSDLMouseButtonEvent,void
    , (S32 button, bool isDown, F32 mouseX, F32 mouseY)
    , ( button , isDown, mouseX, mouseY)
    ,"Event triggered when mousebutton is pressed" );

    IMPLEMENT_GLOBAL_CALLBACK(onSDLMouseWheelEvent,void
    , (F32 wheelX, F32 wheelY)
    , ( wheelX, wheelY)
    ,"Event triggered when mouse wheel is moved" );

namespace ElfSDL3 {

namespace {

    // --- keyboard ---
    enum KeyFlags : Uint8 {
        KF_None     = 0,
        KF_Down     = 1 << 0,
        KF_Pressed  = 1 << 1,
        KF_Released = 1 << 2,
        KF_Repeat   = 1 << 3
    };

    Uint8 s_KeyState[SDL_SCANCODE_COUNT];

    // --- mouse ---
    #define MAX_MOUSE_BUTTONS 8
    Uint8 s_MouseButtonState[MAX_MOUSE_BUTTONS];

    float s_MouseX = 0.0f;
    float s_MouseY = 0.0f;
    float s_MouseDeltaX = 0.0f;
    float s_MouseDeltaY = 0.0f;
    float s_MouseWheelX = 0.0f;
    float s_MouseWheelY = 0.0f;

    // --- init ----
    bool s_initialized = false; //NOTE not used at the moment
}
// -----------------------------------------------------------------------------
void ClearInputFrameTicks() {
    // --- keyboard ---
    for (int i = 0; i < SDL_SCANCODE_COUNT; ++i) {
        s_KeyState[i] &= ~(KF_Pressed | KF_Released | KF_Repeat);
    }
    // --- mouse ---
    for (int i = 0; i < MAX_MOUSE_BUTTONS; ++i) {
        s_MouseButtonState[i] &= ~(KF_Pressed | KF_Released);
    }
    s_MouseDeltaX = 0.0f;
    s_MouseDeltaY = 0.0f;
    s_MouseWheelX = 0.0f;
    s_MouseWheelY = 0.0f;
}
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// Mouse && Keyboard Events (on call)
// -----------------------------------------------------------------------------
void _onKeyEvent(const SDL_Event& event) {
    SDL_Scancode code = event.key.scancode;
    if (code >= SDL_SCANCODE_COUNT || code == SDL_SCANCODE_UNKNOWN) {
        return;
    }

    if (event.type == SDL_EVENT_KEY_DOWN) {
        if (event.key.repeat) {
            s_KeyState[code] |= KF_Repeat;
        } else {
            s_KeyState[code] |= KF_Down;
            s_KeyState[code] |= KF_Pressed;
        }
    }
    else if (event.type == SDL_EVENT_KEY_UP) {
        s_KeyState[code] &= ~KF_Down;
        s_KeyState[code] |= KF_Released;
    }

    onSDLKeyBoardEvent_callback(code, event.key.mod, event.type == SDL_EVENT_KEY_DOWN, event.key.repeat);

}
// -----------------------------------------------------------------------------
void onEvent(const SDL_Event& event) {
    switch (event.type) {
        case SDL_EVENT_MOUSE_MOTION:
            s_MouseX = event.motion.x;
            s_MouseY = event.motion.y;
            s_MouseDeltaX += event.motion.xrel;
            s_MouseDeltaY += event.motion.yrel;

            // onSDLMouseMotionEvent_callback(event.motion.x, event.motion.y, event.motion.xrel, event.motion.yrel);
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN: {
            Uint8 btn = event.button.button;
            if (btn < MAX_MOUSE_BUTTONS) {
                s_MouseButtonState[btn] |= KF_Down;
                s_MouseButtonState[btn] |= KF_Pressed;
                onSDLMouseButtonEvent_callback((S32)btn, true, s_MouseX, s_MouseY);
            }
            break;
        }


        case SDL_EVENT_MOUSE_BUTTON_UP: {
            Uint8 btn = event.button.button;
            if (btn < MAX_MOUSE_BUTTONS) {
                s_MouseButtonState[btn] &= ~KF_Down;
                s_MouseButtonState[btn] |= KF_Released;
                onSDLMouseButtonEvent_callback((S32)btn, false, s_MouseX, s_MouseY);
            }
            break;
        }


        case SDL_EVENT_MOUSE_WHEEL:
            s_MouseWheelX += event.wheel.x;
            s_MouseWheelY += event.wheel.y;
            onSDLMouseWheelEvent_callback(event.wheel.x, event.wheel.y);
            break;

        case SDL_EVENT_KEY_UP:
        case SDL_EVENT_KEY_DOWN:
        {
            _onKeyEvent(event);
        }
        break;
    }

}



// -----------------------------------------------------------------------------

bool IsKeyPressed(SDL_Scancode key) {
    return (s_KeyState[key] & KF_Pressed) != 0;
}

bool IsKeyDown(SDL_Scancode key) {
    return (s_KeyState[key] & KF_Down) != 0;
}

bool IsKeyReleased(SDL_Scancode key) {
    return (s_KeyState[key] & KF_Released) != 0;
}

bool IsKeyUp(SDL_Scancode key) {
    return (s_KeyState[key] & KF_Down) == 0;
}

bool IsKeyRepeat(SDL_Scancode key) {
    return (s_KeyState[key] & KF_Repeat) != 0;
}

bool IsShortcutPressed(Uint16 modifiers, SDL_Scancode key) {
    if (!IsKeyPressed(key)) {
        return false;
    }
    if ((modifiers & SDL_KMOD_CTRL) && !IsKeyDown(SDL_SCANCODE_LCTRL) && !IsKeyDown(SDL_SCANCODE_RCTRL)) {
        return false;
    }
    if ((modifiers & SDL_KMOD_SHIFT) && !IsKeyDown(SDL_SCANCODE_LSHIFT) && !IsKeyDown(SDL_SCANCODE_RSHIFT)) {
        return false;
    }
    if ((modifiers & SDL_KMOD_ALT) && !IsKeyDown(SDL_SCANCODE_LALT) && !IsKeyDown(SDL_SCANCODE_RALT)) {
        return false;
    }
    if ((modifiers & SDL_KMOD_GUI) && !IsKeyDown(SDL_SCANCODE_LGUI) && !IsKeyDown(SDL_SCANCODE_RGUI)) {
        return false;
    }
    return true;
}


// -----------------------------------------------------------------------------
#ifdef ElfSDL3_ENABLE_POLL
DefineEngineFunction(SDL_IsKeyPressed, bool, (S32 scancode),, "return if the key with value scancode is pressed."){
    return IsKeyPressed((SDL_Scancode)scancode);
}
DefineEngineFunction(SDL_IsKeyDown, bool, (S32 scancode),, "return if the key with value scancode is just pressed."){
    return IsKeyDown((SDL_Scancode)scancode);
}
DefineEngineFunction(SDL_IsKeyUp, bool, (S32 scancode),, "return if the key with value scancode is just released."){
    return IsKeyUp((SDL_Scancode)scancode);
}
DefineEngineFunction(SDL_IsKeyRepeat, bool, (S32 scancode),, "return if the key with value scancode is repeated."){
    return IsKeyRepeat((SDL_Scancode)scancode);
}

DefineEngineFunction(SDL_IsShortcutPressed, bool, (S32 modifiers, S32 scancode),, "Returns true if the shortcut (modifier combo + key press) was triggered.") {
    return IsShortcutPressed((Uint16)modifiers, (SDL_Scancode)scancode);
}
#endif //#ifdef ElfSDL3_ENABLE_POLL

bool IsMouseButtonPressed(U32 button)  { return button < MAX_MOUSE_BUTTONS && (s_MouseButtonState[button] & KF_Pressed) != 0; }
bool IsMouseButtonDown(U32 button)     { return button < MAX_MOUSE_BUTTONS && (s_MouseButtonState[button] & KF_Down) != 0; }
bool IsMouseButtonReleased(U32 button) { return button < MAX_MOUSE_BUTTONS && (s_MouseButtonState[button] & KF_Released) != 0; }
bool IsMouseButtonUp(U32 button)       { return button >= MAX_MOUSE_BUTTONS || (s_MouseButtonState[button] & KF_Down) == 0; }

float GetMouseX()      { return s_MouseX; }
float GetMouseY()      { return s_MouseY; }
float GetMouseDeltaX() { return s_MouseDeltaX; }
float GetMouseDeltaY() { return s_MouseDeltaY; }
float GetMouseWheelX() { return s_MouseWheelX; }
float GetMouseWheelY() { return s_MouseWheelY; }

// -----------------------------------------------------------------------------
// Mouse script bindings:
// -----------------------------------------------------------------------------
#ifdef ElfSDL3_ENABLE_POLL
DefineEngineFunction(SDL_IsMouseButtonPressed, bool, (S32 button),, "Return true if the mouse button was pressed this frame.") {
    return ElfSDL3::IsMouseButtonPressed((U32)button);
}

DefineEngineFunction(SDL_IsMouseButtonDown, bool, (S32 button),, "Return true if the mouse button is being held down.") {
    return ElfSDL3::IsMouseButtonDown((U32)button);
}

DefineEngineFunction(SDL_IsMouseButtonReleased, bool, (S32 button),, "Return true if the mouse button was released this frame.") {
    return ElfSDL3::IsMouseButtonReleased((U32)button);
}

DefineEngineFunction(SDL_IsMouseButtonUp, bool, (S32 button),, "Return true if the mouse button is up.") {
    return ElfSDL3::IsMouseButtonUp((U32)button);
}


DefineEngineFunction(SDL_GetMouseDeltaX, F32, (),, "Get mouse movement delta X for this frame.") { return ElfSDL3::GetMouseDeltaX(); }
DefineEngineFunction(SDL_GetMouseDeltaY, F32, (),, "Get mouse movement delta Y for this frame.") { return ElfSDL3::GetMouseDeltaY(); }
DefineEngineFunction(SDL_GetMouseWheelY, F32, (),, "Get vertical mouse wheel scroll amount for this frame.") { return ElfSDL3::GetMouseWheelY(); }
#endif //#ifdef ElfSDL3_ENABLE_POLL
// this can be used also when polling is disabled
DefineEngineFunction(SDL_GetMouseX, F32, (),, "Get absolute mouse X position.") { return ElfSDL3::GetMouseX(); }
DefineEngineFunction(SDL_GetMouseY, F32, (),, "Get absolute mouse Y position.") { return ElfSDL3::GetMouseY(); }
// -----------------------------------------------------------------------------
// Keyboard Constants ...
// -----------------------------------------------------------------------------
void RegisterInputConstants() {

    Con::REGISTER_CONST_S32(SDL_SCANCODE_UNKNOWN);

    // Alphabet keys
    Con::REGISTER_CONST_S32(SDL_SCANCODE_A);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_B);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_C);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_D);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_E);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_G);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_H);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_I);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_J);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_K);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_L);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_M);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_N);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_O);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_P);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_Q);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_R);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_S);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_T);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_U);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_V);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_W);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_X);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_Y);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_Z);

    // Number row
    Con::REGISTER_CONST_S32(SDL_SCANCODE_1);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_2);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_3);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_4);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_5);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_6);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_7);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_8);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_9);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_0);

    // Standard control keys
    Con::REGISTER_CONST_S32(SDL_SCANCODE_RETURN);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_ESCAPE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_BACKSPACE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_TAB);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_SPACE);

    // Punctuation and symbols
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MINUS);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_EQUALS);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LEFTBRACKET);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_RIGHTBRACKET);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_BACKSLASH);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_NONUSHASH);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_SEMICOLON);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_APOSTROPHE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_GRAVE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_COMMA);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_PERIOD);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_SLASH);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_CAPSLOCK);

    // Function keys (F1 to F12)
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F1);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F2);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F3);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F4);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F5);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F6);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F7);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F8);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F9);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F10);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F11);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F12);

    // Navigation cluster
    Con::REGISTER_CONST_S32(SDL_SCANCODE_PRINTSCREEN);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_SCROLLLOCK);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_PAUSE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INSERT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_HOME);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_PAGEUP);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_DELETE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_END);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_PAGEDOWN);

    // Arrow keys
    Con::REGISTER_CONST_S32(SDL_SCANCODE_RIGHT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LEFT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_DOWN);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_UP);

    // Keypad / Numpad
    Con::REGISTER_CONST_S32(SDL_SCANCODE_NUMLOCKCLEAR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_DIVIDE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MULTIPLY);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MINUS);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_PLUS);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_ENTER);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_1);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_2);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_3);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_4);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_5);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_6);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_7);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_8);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_9);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_0);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_PERIOD);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_NONUSBACKSLASH);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_APPLICATION);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_POWER);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_EQUALS);

    // Extended Function keys
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F13);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F14);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F15);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F16);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F17);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F18);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F19);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F20);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F21);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F22);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F23);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_F24);

    // UI / Action keys
    Con::REGISTER_CONST_S32(SDL_SCANCODE_EXECUTE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_HELP);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MENU);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_SELECT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_STOP);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AGAIN);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_UNDO);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_CUT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_COPY);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_PASTE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_FIND);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MUTE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_VOLUMEUP);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_VOLUMEDOWN);

    // Keypad comma & special separators
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_COMMA);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_EQUALSAS400);

    // International keys
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL1);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL2);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL3);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL4);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL5);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL6);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL7);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL8);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_INTERNATIONAL9);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG1);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG2);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG3);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG4);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG5);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG6);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG7);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG8);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LANG9);

    // Erase & operating system operations
    Con::REGISTER_CONST_S32(SDL_SCANCODE_ALTERASE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_SYSREQ);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_CANCEL);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_CLEAR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_PRIOR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_RETURN2);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_SEPARATOR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_OUT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_OPER);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_CLEARAGAIN);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_CRSEL);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_EXSEL);

    // Keypad basic math & syntax variants
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_00);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_000);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_THOUSANDSSEPARATOR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_DECIMALSEPARATOR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_CURRENCYUNIT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_CURRENCYSUBUNIT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_LEFTPAREN);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_RIGHTPAREN);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_LEFTBRACE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_RIGHTBRACE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_TAB);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_BACKSPACE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_A);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_B);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_C);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_D);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_E);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_F);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_XOR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_POWER);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_PERCENT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_LESS);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_GREATER);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_AMPERSAND);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_DBLAMPERSAND);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_VERTICALBAR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_DBLVERTICALBAR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_COLON);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_HASH);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_SPACE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_AT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_EXCLAM);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MEMSTORE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MEMRECALL);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MEMCLEAR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MEMADD);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MEMSUBTRACT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MEMMULTIPLY);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_MEMDIVIDE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_PLUSMINUS);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_CLEAR);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_CLEARENTRY);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_BINARY);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_OCTAL);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_DECIMAL);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_KP_HEXADECIMAL);

    // Modifiers
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LCTRL);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LSHIFT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LALT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_LGUI);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_RCTRL);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_RSHIFT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_RALT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_RGUI);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MODE);

    // Media and Browser commands

    Con::REGISTER_CONST_S32(SDL_SCANCODE_MEDIA_NEXT_TRACK);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MEDIA_PREVIOUS_TRACK);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MEDIA_STOP);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MEDIA_PLAY);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MUTE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MEDIA_SELECT);

    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_NEW);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_OPEN);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_CLOSE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_EXIT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_SAVE);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_PRINT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_PROPERTIES);

    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_SEARCH);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_HOME);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_BACK);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_FORWARD);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_STOP);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_REFRESH);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_AC_BOOKMARKS);

    Con::REGISTER_CONST_S32(SDL_SCANCODE_MEDIA_REWIND);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MEDIA_FAST_FORWARD);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_MEDIA_EJECT);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_VOLUMEUP);
    Con::REGISTER_CONST_S32(SDL_SCANCODE_VOLUMEDOWN);


    // --- SDL3 Keyboard Modifier Constants ---
    Con::REGISTER_CONST_S32(SDL_KMOD_NONE);
    Con::REGISTER_CONST_S32(SDL_KMOD_LSHIFT);
    Con::REGISTER_CONST_S32(SDL_KMOD_RSHIFT);
    Con::REGISTER_CONST_S32(SDL_KMOD_LCTRL);
    Con::REGISTER_CONST_S32(SDL_KMOD_RCTRL);
    Con::REGISTER_CONST_S32(SDL_KMOD_LALT);
    Con::REGISTER_CONST_S32(SDL_KMOD_RALT);
    Con::REGISTER_CONST_S32(SDL_KMOD_LGUI);
    Con::REGISTER_CONST_S32(SDL_KMOD_RGUI);
    Con::REGISTER_CONST_S32(SDL_KMOD_NUM);
    Con::REGISTER_CONST_S32(SDL_KMOD_CAPS);
    Con::REGISTER_CONST_S32(SDL_KMOD_MODE);
    Con::REGISTER_CONST_S32(SDL_KMOD_SCROLL);

    Con::REGISTER_CONST_S32(SDL_KMOD_CTRL);  // (SDL_KMOD_LCTRL | SDL_KMOD_RCTRL)
    Con::REGISTER_CONST_S32(SDL_KMOD_SHIFT); // (SDL_KMOD_LSHIFT | SDL_KMOD_RSHIFT)
    Con::REGISTER_CONST_S32(SDL_KMOD_ALT);   // (SDL_KMOD_LALT | SDL_KMOD_RALT)
    Con::REGISTER_CONST_S32(SDL_KMOD_GUI);   // (SDL_KMOD_LGUI | SDL_KMOD_RGUI)


    // --- MouseButton Constants ... ---
    Con::REGISTER_CONST_S32(SDL_BUTTON_LEFT);
    Con::REGISTER_CONST_S32(SDL_BUTTON_MIDDLE);
    Con::REGISTER_CONST_S32(SDL_BUTTON_RIGHT);
    Con::REGISTER_CONST_S32(SDL_BUTTON_X1);
    Con::REGISTER_CONST_S32(SDL_BUTTON_X2);

}
// -----------------------------------------------------------------------------
void InitKeyCodes() {
    RegisterInputConstants();
    dMemset(s_KeyState, KF_None, sizeof(s_KeyState));

    // implement script stubs
    Con::evaluate( R"(
     function onSDLKeyBoardEvent(%scancode, %modifiers, %isDown, %isRepeat){}
     function onSDLMouseButtonEvent(%button, %isDown, %x, %y){}
     function onSDLMouseWheelEvent(%wheelX, %wheelY){}
    )"
    );

    s_initialized = true;

}
// -----------------------------------------------------------------------------



} //namespace
