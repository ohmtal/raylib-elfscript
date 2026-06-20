//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#include "raylib.h"
#include "console/console.h"
#include "console/script.h"
#include "console/engineAPI.h"
#include "ConsoleTypes.h"
#include "elfStorage.h"

//the lazy (long build time) way or define KeyboardKey (348)
// #define MAGIC_ENUM_RANGE_MIN 0
// #define MAGIC_ENUM_RANGE_MAX 348
// compile takes ages! #define MAGIC_ENUM_RANGE_MAX 65536
#include "console/consoleExtras.h" // registerEnum

// -----------------------------------------------------------------------------
// TraceLog raylib log to Con::.. log.
// -----------------------------------------------------------------------------
//FIXME what it that ? =>
//  TEXTURE: [ID 125595416] Texture loaded successfully (125595416x-2118071736 | UH��H�� �}�H�u�H�U��}�tn�}��� | -2118068406 mipmaps)
// void CustomTraceLog(int msgType, const char *text, va_list args)
// {
//     switch (msgType)
//     {
//         case LOG_INFO: Con::infof(text,args); break;
//         case LOG_ERROR: Con::errorf(text,args); break;
//         case LOG_FATAL: Con::errorf(text,args); break;
//         case LOG_WARNING: Con::warnf(text,args); break;
//         case LOG_DEBUG: ; break;
//         default: break;
//     }
// }

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
// -----------------------------------------------------------------------------
// Logging system
// -----------------------------------------------------------------------------
// RLAPI void SetTraceLogLevel(int logLevel);                      // Set the current threshold (minimum) log level
DefineEngineFunction( SetTraceLogLevel, void, (int logLevel), , "Set the current threshold (minimum) raylib log level (e.g. 2 = LOG_TRACE, 3 = LOG_DEBUG, 4 = LOG_INFO...)") {
    SetTraceLogLevel(logLevel);
}

//RLAPI void SetTraceLogLevel(int logLevel);                      // Set the current threshold (minimum) log level
// RLAPI void TraceLog(int logLevel, const char *text, ...);       // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
// RLAPI void SetTraceLogCallback(TraceLogCallback callback);      // Set custom trace log

// -----------------------------------------------------------------------------
// Window-related functions
// -----------------------------------------------------------------------------
DefineEngineFunction(InitWindow, void, (S32 width, S32 height, String title),,"Initialize window and OpenGL context"){
    InitWindow(width, height, title);
}
// RLAPI void CloseWindow(void);                                     // Close window and unload OpenGL context
DefineEngineFunction(CloseWindow, void, (),,"Close window and unload OpenGL context"){
    CloseWindow();
}
// RLAPI bool WindowShouldClose(void);                               // Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
DefineEngineFunction(WindowShouldClose, bool, (), , "Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)"){
    return WindowShouldClose();
}

// RLAPI bool IsWindowReady(void);                                   // Check if window has been initialized successfully
DefineEngineFunction(IsWindowReady, bool, (), , "Check if window has been initialized successfully"){
    return IsWindowReady();
}

// RLAPI bool IsWindowFullscreen(void);                              // Check if window is currently fullscreen
DefineEngineFunction(IsWindowFullscreen, bool, (), , "Check if window is currently fullscreen"){
    return IsWindowFullscreen();
}

// RLAPI bool IsWindowHidden(void);                                  // Check if window is currently hidden
DefineEngineFunction(IsWindowHidden, bool, (), , "Check if window is currently hidden"){
    return IsWindowHidden();
}

// RLAPI bool IsWindowMinimized(void);                               // Check if window is currently minimized
DefineEngineFunction(IsWindowMinimized, bool, (), , "Check if window is currently minimized"){
    return IsWindowMinimized();
}

// RLAPI bool IsWindowMaximized(void);                               // Check if window is currently maximized
DefineEngineFunction(IsWindowMaximized, bool, (), , "Check if window is currently maximized"){
    return IsWindowMaximized();
}

// RLAPI bool IsWindowFocused(void);                                 // Check if window is currently focused
DefineEngineFunction(IsWindowFocused, bool, (), , "Check if window is currently focused"){
    return IsWindowFocused();
}

// RLAPI bool IsWindowResized(void);                                 // Check if window has been resized last frame
DefineEngineFunction(IsWindowResized, bool, (), , "Check if window has been resized last frame"){
    return IsWindowResized();
}

// RLAPI bool IsWindowState(unsigned int flag);                      // Check if one specific window flag is enabled
DefineEngineFunction(IsWindowState, bool, (unsigned int flag), , "Check if one specific window flag is enabled"){
    return IsWindowState(flag);
}

// RLAPI void SetWindowState(unsigned int flags);                    // Set window configuration state using flags
DefineEngineFunction(SetWindowState, void, (unsigned int flags), , "Set window configuration state using flags"){
    SetWindowState(flags);
}

// RLAPI void ClearWindowState(unsigned int flags);                  // Clear window configuration state flags
DefineEngineFunction(ClearWindowState, void, (unsigned int flags), , "Clear window configuration state flags"){
    ClearWindowState(flags);
}

// RLAPI void ToggleFullscreen(void);                                // Toggle window state: fullscreen/windowed, resizes monitor to match window resolution
DefineEngineFunction(ToggleFullscreen, void, (), , "Toggle window state: fullscreen/windowed, resizes monitor to match window resolution"){
    ToggleFullscreen();
}

// RLAPI void ToggleBorderlessWindowed(void);                        // Toggle window state: borderless windowed, resizes window to match monitor resolution
DefineEngineFunction(ToggleBorderlessWindowed, void, (), , "Toggle window state: borderless windowed, resizes window to match monitor resolution"){
    ToggleBorderlessWindowed();
}

// RLAPI void MaximizeWindow(void);                                  // Set window state: maximized, if resizable
DefineEngineFunction(MaximizeWindow, void, (), , "Set window state: maximized, if resizable"){
    MaximizeWindow();
}

// RLAPI void MinimizeWindow(void);                                  // Set window state: minimized, if resizable
DefineEngineFunction(MinimizeWindow, void, (), , "Set window state: minimized, if resizable"){
    MinimizeWindow();
}

// RLAPI void RestoreWindow(void);                                   // Restore window from being minimized/maximized
DefineEngineFunction(RestoreWindow, void, (), , "Restore window from being minimized/maximized"){
    RestoreWindow();
}

// RLAPI void SetWindowIcon(Image image);                            // Set icon for window (single image, RGBA 32bit)
DefineEngineFunction(SetWindowIcon, void, (S32 imageId), , "Set icon for window (single image, RGBA 32bit)"){

    Image* img = ElfResource::ImageMap.get(imageId);
    if (img) SetWindowIcon(*img);
    else Con::errorf("Image with id %d not found.", imageId);
}

// RLAPI void SetWindowIcons(Image *images, int count);              // Set icon for window (multiple images, RGBA 32bit)
DefineEngineFunction(SetWindowIcons, void, (Vector<S32> imageIds, int count), , "Set icon for window (multiple images, RGBA 32bit)"){
    auto images = ElfResource::ImageMap.getList(imageIds);
    if (images.size() > 0) SetWindowIcons(images.data(), (int) images.size());
    if ((int) images.size() != count) {
        Con::warnf("ImagesIds size missmatch. got:%d, count is: %d", (int) images.size(),count);
    }
}

// RLAPI void SetWindowTitle(const char *title);                     // Set title for window
DefineEngineFunction(SetWindowTitle, void, (const char *title), , "Set title for window"){
    SetWindowTitle(title);
}

// RLAPI void SetWindowPosition(int x, int y);                       // Set window position on screen
DefineEngineFunction(SetWindowPosition, void, (int x, int y), , "Set window position on screen"){
    SetWindowPosition(x, y);
}

// RLAPI void SetWindowMonitor(int monitor);                         // Set monitor for the current window
DefineEngineFunction(SetWindowMonitor, void, (int monitor), , "Set monitor for the current window"){
    SetWindowMonitor(monitor);
}

// RLAPI void SetWindowMinSize(int width, int height);               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
DefineEngineFunction(SetWindowMinSize, void, (int width, int height), , "Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)"){
    SetWindowMinSize(width, height);
}

// RLAPI void SetWindowMaxSize(int width, int height);               // Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
DefineEngineFunction(SetWindowMaxSize, void, (int width, int height), , "Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)"){
    SetWindowMaxSize(width, height);
}

// RLAPI void SetWindowSize(int width, int height);                  // Set window dimensions
DefineEngineFunction(SetWindowSize, void, (int width, int height), , "Set window dimensions"){
    SetWindowSize(width, height);
}

// RLAPI void SetWindowOpacity(float opacity);                       // Set window opacity [0.0f..1.0f]
DefineEngineFunction(SetWindowOpacity, void, (float opacity), , "Set window opacity [0.0f..1.0f]"){
    SetWindowOpacity(opacity);
}

// RLAPI void SetWindowFocused(void);                                // Set window focused
DefineEngineFunction(SetWindowFocused, void, (), , "Set window focused"){
    SetWindowFocused();
}

// RLAPI void *GetWindowHandle(void);                                // Get native window handle
// FIXME
// DefineEngineFunction(GetWindowHandle, void *, (), , "Get native window handle"){
//     return GetWindowHandle();
// }


// RLAPI int GetScreenWidth(void);                                   // Get current screen width
DefineEngineFunction(GetScreenWidth, int, (), , "Get current screen width"){
    return GetScreenWidth();
}

// RLAPI int GetScreenHeight(void);                                  // Get current screen height
DefineEngineFunction(GetScreenHeight, int, (), , "Get current screen height"){
    return GetScreenHeight();
}

// RLAPI int GetRenderWidth(void);                                   // Get current render width (it considers HiDPI)
DefineEngineFunction(GetRenderWidth, int, (), , "Get current render width (it considers HiDPI)"){
    return GetRenderWidth();
}

// RLAPI int GetRenderHeight(void);                                  // Get current render height (it considers HiDPI)
DefineEngineFunction(GetRenderHeight, int, (), , "Get current render height (it considers HiDPI)"){
    return GetRenderHeight();
}

// RLAPI int GetMonitorCount(void);                                  // Get number of connected monitors
DefineEngineFunction(GetMonitorCount, int, (), , "Get number of connected monitors"){
    return GetMonitorCount();
}

// RLAPI int GetCurrentMonitor(void);                                // Get current monitor where window is placed
DefineEngineFunction(GetCurrentMonitor, int, (), , "Get current monitor where window is placed"){
    return GetCurrentMonitor();
}

// RLAPI Vector2 GetMonitorPosition(int monitor);                    // Get specified monitor position
DefineEngineFunction(GetMonitorPosition, Vector2, (int monitor), , "Get specified monitor position"){
    return GetMonitorPosition(monitor);
}

// RLAPI int GetMonitorWidth(int monitor);                           // Get specified monitor width (current video mode used by monitor)
DefineEngineFunction(GetMonitorWidth, int, (int monitor), , "Get specified monitor width (current video mode used by monitor)"){
    return GetMonitorWidth(monitor);
}

// RLAPI int GetMonitorHeight(int monitor);                          // Get specified monitor height (current video mode used by monitor)
DefineEngineFunction(GetMonitorHeight, int, (int monitor), , "Get specified monitor height (current video mode used by monitor)"){
    return GetMonitorHeight(monitor);
}

// RLAPI int GetMonitorPhysicalWidth(int monitor);                   // Get specified monitor physical width in millimetres
DefineEngineFunction(GetMonitorPhysicalWidth, int, (int monitor), , "Get specified monitor physical width in millimetres"){
    return GetMonitorPhysicalWidth(monitor);
}

// RLAPI int GetMonitorPhysicalHeight(int monitor);                  // Get specified monitor physical height in millimetres
DefineEngineFunction(GetMonitorPhysicalHeight, int, (int monitor), , "Get specified monitor physical height in millimetres"){
    return GetMonitorPhysicalHeight(monitor);
}

// RLAPI int GetMonitorRefreshRate(int monitor);                     // Get specified monitor refresh rate
DefineEngineFunction(GetMonitorRefreshRate, int, (int monitor), , "Get specified monitor refresh rate"){
    return GetMonitorRefreshRate(monitor);
}

// RLAPI Vector2 GetWindowPosition(void);                            // Get window position XY on monitor
DefineEngineFunction(GetWindowPosition, Vector2, (), , "Get window position XY on monitor"){
    return GetWindowPosition();
}

// RLAPI Vector2 GetWindowScaleDPI(void);                            // Get window scale DPI factor
DefineEngineFunction(GetWindowScaleDPI, Vector2, (), , "Get window scale DPI factor"){
    return GetWindowScaleDPI();
}

// RLAPI const char *GetMonitorName(int monitor);                    // Get the human-readable, UTF-8 encoded name of the specified monitor
DefineEngineFunction(GetMonitorName, const char *, (int monitor), , "Get the human-readable, UTF-8 encoded name of the specified monitor"){
    return GetMonitorName(monitor);
}

// RLAPI void SetClipboardText(const char *text);                    // Set clipboard text content
DefineEngineFunction(SetClipboardText, void, (const char *text), , "Set clipboard text content"){
    SetClipboardText(text);
}

// RLAPI const char *GetClipboardText(void);                         // Get clipboard text content
DefineEngineFunction(GetClipboardText, const char *, (), , "Get clipboard text content"){
    return GetClipboardText();
}

// RLAPI Image GetClipboardImage(void);                              // Get clipboard image content
DefineEngineFunction(GetClipboardImage, S32, (), , "Get clipboard image content"){
    Image img = GetClipboardImage();
    if (!IsImageValid(img)) return 0;
    return ElfResource::ImageMap.add(img);
}

// RLAPI void EnableEventWaiting(void);                              // Enable waiting for events on EndDrawing(), no automatic event polling
DefineEngineFunction(EnableEventWaiting, void, (), , "Enable waiting for events on EndDrawing(), no automatic event polling"){
    EnableEventWaiting();
}

// RLAPI void DisableEventWaiting(void);                             // Disable waiting for events on EndDrawing(), automatic events polling
DefineEngineFunction(DisableEventWaiting, void, (), , "Disable waiting for events on EndDrawing(), automatic events polling"){
    DisableEventWaiting();
}

// -----------------------------------------------------------------------------
// Custom frame control functions
// -----------------------------------------------------------------------------

// RLAPI void SwapScreenBuffer(void);                      // Swap back buffer with front buffer (screen drawing)
DefineEngineFunction(SwapScreenBuffer, void, (), , "Swap back buffer with front buffer (screen drawing)"){
    SwapScreenBuffer();
}

// RLAPI void PollInputEvents(void);                       // Register all input events
DefineEngineFunction(PollInputEvents, void, (), , "Register all input events"){
    PollInputEvents();
}

// RLAPI void WaitTime(double seconds);                    // Wait for some time (halt program execution)
DefineEngineFunction(WaitTime, void, (double seconds), , "Wait for some time (halt program execution)"){
    WaitTime(seconds);
}
// -----------------------------------------------------------------------------
// Random values generation functions
// -----------------------------------------------------------------------------
// RLAPI void SetRandomSeed(unsigned int seed);            // Set the seed for the random number generator
DefineEngineFunction(SetRandomSeed, void, (unsigned int seed), , "Set the seed for the random number generator"){
    SetRandomSeed(seed);
}

// RLAPI int GetRandomValue(int min, int max);             // Get a random value between min and max (both included)
DefineEngineFunction(GetRandomValue, int, (int min, int max), , "Get a random value between min and max (both included)"){
    return GetRandomValue(min, max);
}

// RLAPI int *LoadRandomSequence(unsigned int count, int min, int max); // Load random values sequence, no values repeated
DefineEngineFunction(LoadRandomSequence, Vector<S32>, (U32 count, S32 min, S32 max), ,
                     "Load random values sequence, no values repeated, unload automaticly done. "){
   int* sequence = LoadRandomSequence(count, min, max);
   Vector<S32> result;
   for (S32 i = 0; i < count; i++) result.push_back(sequence[i]);
   UnloadRandomSequence(sequence);
   return result;
}

// RLAPI void UnloadRandomSequence(int *sequence);         // Unload random values sequence
// DefineEngineFunction(UnloadRandomSequence, void, (int *sequence), , "Unload random values sequence"){
//     UnloadRandomSequence(sequence);
// }
// -----------------------------------------------------------------------------
// Misc. functions
// -----------------------------------------------------------------------------
// RLAPI void TakeScreenshot(const char *fileName);                // Takes a screenshot of current screen (filename extension defines format)
DefineEngineFunction(TakeScreenshot, void, (const char *fileName), , "Takes a screenshot of current screen (filename extension defines format)"){
    TakeScreenshot(fileName);
}

// RLAPI void SetConfigFlags(unsigned int flags);                  // Set up init configuration flags (view FLAGS)
DefineEngineFunction(SetConfigFlags, void, (unsigned int flags), , "Set up init configuration flags (view FLAGS)"){
    SetConfigFlags(flags);
}

// RLAPI void OpenURL(const char *url);                            // Open URL with default system browser (if available)
DefineEngineFunction(OpenURL, void, (const char *url), , "Open URL with default system browser (if available)"){
    OpenURL(url);
}

// -----------------------------------------------------------------------------
// Timing-related functions
// -----------------------------------------------------------------------------

DefineEngineFunction(SetTargetFPS, void, (S32 fps),,"Set target FPS (maximum)"){
    SetTargetFPS(fps);
}

DefineEngineFunction(GetFrameTime, F32, (),,"Get time in seconds for last frame drawn (delta time)"){
   return GetFrameTime();
}
DefineEngineFunction(GetTime, F64, (),,"Get elapsed time in seconds since InitWindow()"){
    return GetTime();
}
DefineEngineFunction(GetFPS, S32, (),,"Get current FPS"){
    return GetFPS();
}

// -----------------------------------------------------------------------------
// Drawing-related functions
// -----------------------------------------------------------------------------
DefineEngineFunction(ClearBackground, void, (Color color),(RAYWHITE),"Clear background (framebuffer) to color"){
    ClearBackground(color);
}
DefineEngineFunction(BeginDrawing, void, (),,"Begin canvas (framebuffer) drawing"){
    BeginDrawing();
}
DefineEngineFunction(EndDrawing, void, (),," End canvas (framebuffer) drawing and swap buffers (double buffering)"){
    EndDrawing();
}

// RLAPI void BeginTextureMode(RenderTexture2D target);                                                     // Begins drawing to render texture
DefineEngineFunction( BeginTextureMode, void, (S32 renderTextureId), , "Begins drawing to render texture") {
    RenderTexture2D* target = ElfResource::RenderTextureMap.get(renderTextureId);
    if (!target) return;
    BeginTextureMode(*target);
}
DefineEngineFunction(EndTextureMode, void, (),, " End drawing to render texture") {
    EndTextureMode();
}

// NOTE: in elfShader.cpp
// RLAPI void BeginShaderMode(Shader shader);                        // Begin custom shader drawing
// RLAPI void EndShaderMode(void);                                   // End custom shader drawing (use default shader)


// RLAPI void BeginBlendMode(int mode);                              // Begin blending mode (alpha, additive, multiplied, subtract, custom)
DefineEngineFunction( BeginBlendMode, void, (int mode), , "Begin blending mode (e.g. BLEND_ALPHA, BLEND_ADDITIVE, BLEND_MULTIPLIED)") {
    BeginBlendMode(mode);
}

// RLAPI void EndBlendMode(void);                                    // End blending mode (reset to default: alpha blending)
DefineEngineFunction( EndBlendMode, void, (), , "End blending mode (reset to default: alpha blending)") {
    EndBlendMode();
}

// RLAPI void BeginScissorMode(int x, int y, int width, int height); // Begin scissor mode (define screen area for following drawing)
DefineEngineFunction( BeginScissorMode, void, (int x, int y, int width, int height), , "Begin scissor mode (define screen area for following drawing)") {
    BeginScissorMode(x, y, width, height);
}

// RLAPI void EndScissorMode(void);                                  // End scissor mode
DefineEngineFunction( EndScissorMode, void, (), , "End scissor mode") {
    EndScissorMode();
}



//NOTE not implemented:
// RLAPI void BeginVrStereoMode(VrStereoConfig config);              // Begin stereo rendering (requires VR simulator)
// RLAPI void EndVrStereoMode(void);                                 // End stereo rendering (requires VR simulator)


// -----------------------------------------------------------------------------
// Input-related functions: keyboard
// -----------------------------------------------------------------------------
DefineEngineFunction(IsKeyPressed, bool, (S32 key), , "Check if a key has been pressed once"){
    return IsKeyPressed(key);
}
DefineEngineFunction( IsKeyPressedRepeat, bool, (int key), , "Check if a key has been pressed again") {
    return IsKeyPressedRepeat(key);
}
DefineEngineFunction( IsKeyDown, bool, (int key), , "Check if a key is being pressed") {
    return IsKeyDown(key);
}
DefineEngineFunction( IsKeyReleased, bool, (int key), , "Check if a key has been released once") {
    return IsKeyReleased(key);
}
DefineEngineFunction( IsKeyUp, bool, (int key), , "Check if a key is NOT being pressed") {
    return IsKeyUp(key);
}
// RLAPI int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
DefineEngineFunction( GetKeyPressed, int, (void), , "Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty") {
    return GetKeyPressed();
}

// RLAPI int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
DefineEngineFunction( GetCharPressed, int, (void), , "Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty") {
    return GetCharPressed();
}

// RLAPI const char *GetKeyName(int key);                        // Get name of a QWERTY key on the current keyboard layout (eg returns string 'q' for KEY_A on an AZERTY keyboard)
// TODO: not working ???? GetKeyName return nullptr
// DefineEngineFunction( GetKeyName, String, (int key), , " Get name of a QWERTY key on the current keyboard layout (eg returns string 'q' for KEY_A on an AZERTY keyboard)") {
//
//     String result = GetKeyName(key);
//     return result;
//     // S32 bufSize = 32;
//     // char* returnBuffer = Con::getReturnBuffer(bufSize);
//     // dSprintf(returnBuffer, bufSize, "%s", GetKeyName(key));
//     // return(returnBuffer);
// }

// RLAPI void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)
DefineEngineFunction( SetExitKey, void, (int key), , "Set a custom key to exit program (default is ESC)") {
    SetExitKey(key);
}
// -----------------------------------------------------------------------------
// Input-related functions: mouse
// -----------------------------------------------------------------------------
DefineEngineFunction( IsMouseButtonPressed, bool, (int button), , "Check if a mouse button has been pressed once") {
    return IsMouseButtonPressed(button);
}
DefineEngineFunction( IsMouseButtonDown, bool, (int button), , "Check if a mouse button is being pressed") {
    return IsMouseButtonDown(button);
}
DefineEngineFunction( IsMouseButtonReleased, bool, (int button), , "Check if a mouse button has been released once") {
    return IsMouseButtonReleased(button);
}
DefineEngineFunction( IsMouseButtonUp, bool, (S32 button), , " Check if a mouse button is NOT being pressed") {
    return IsMouseButtonUp(button);
}

DefineEngineFunction( GetMouseX, S32, (), , " Get mouse position X") {
    return GetMouseX();
}
DefineEngineFunction( GetMouseY, S32, (), , " Get mouse position Y") {
    return GetMouseY();
}
DefineEngineFunction( GetMousePosition, Vector2, (), , " Get mouse position XY") {
    return GetMousePosition();
}
DefineEngineFunction( GetMouseDelta, Vector2, (), , " Get mouse delta XY") {
    return GetMouseDelta();
}

// RLAPI void SetMousePosition(int x, int y);                    // Set mouse position XY
DefineEngineFunction( SetMousePosition, void, (int x, int y), , "Set mouse position XY on the screen") {
    SetMousePosition(x, y);
}

// RLAPI void SetMouseOffset(int offsetX, int offsetY);          // Set mouse offset
DefineEngineFunction( SetMouseOffset, void, (int offsetX, int offsetY), , "Set mouse offset (useful for custom rendering resolution scaling)") {
    SetMouseOffset(offsetX, offsetY);
}

// RLAPI void SetMouseScale(float scaleX, float scaleY);         // Set mouse scaling
DefineEngineFunction( SetMouseScale, void, (float scaleX, float scaleY), , "Set mouse scaling for its coordinates (useful for custom rendering resolution scaling)") {
    SetMouseScale(scaleX, scaleY);
}

DefineEngineFunction( GetMouseWheelMove, F32, (), , " Get mouse wheel movement for X or Y, whichever is larger") {
    return GetMouseWheelMove();
}
// RLAPI Vector2 GetMouseWheelMoveV(void);                       // Get mouse wheel movement for both X and Y
DefineEngineFunction( GetMouseWheelMoveV, Vector2, (), , "Get mouse wheel movement for both X and Y as a Vector2") {
    return GetMouseWheelMoveV();
}

// RLAPI void SetMouseCursor(int cursor);                        // Set mouse cursor
DefineEngineFunction( SetMouseCursor, void, (int cursor), , "Set mouse cursor icon type (e.g. MOUSE_CURSOR_IBEAM, MOUSE_CURSOR_POINT)") {
    SetMouseCursor(cursor);
}
// -----------------------------------------------------------------------------
// Input-related functions: touch
// -----------------------------------------------------------------------------
// RLAPI int GetTouchX(void);                                    // Get touch position X for touch point 0
DefineEngineFunction( GetTouchX, int, (), , "Get touch position X for touch point 0 (relative to screen size)") {
    return GetTouchX();
}

// RLAPI int GetTouchY(void);                                    // Get touch position Y for touch point 0
DefineEngineFunction( GetTouchY, int, (), , "Get touch position Y for touch point 0 (relative to screen size)") {
    return GetTouchY();
}

// RLAPI Vector2 GetTouchPosition(int index);                    // Get touch position XY for a touch point index
DefineEngineFunction( GetTouchPosition, Vector2, (int index), , "Get touch position XY for a touch point index (relative to screen size)") {
    return GetTouchPosition(index);
}

// RLAPI int GetTouchPointId(int index);                         // Get touch point identifier for given index
DefineEngineFunction( GetTouchPointId, int, (int index), , "Get touch point identifier for given index") {
    return GetTouchPointId(index);
}

// RLAPI int GetTouchPointCount(void);                           // Get number of touch points
DefineEngineFunction( GetTouchPointCount, int, (), , "Get number of active touch points") {
    return GetTouchPointCount();
}

//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: rgestures)
//------------------------------------------------------------------------------------
// RLAPI void SetGesturesEnabled(unsigned int flags);            // Enable a set of gestures using flags
DefineEngineFunction( SetGesturesEnabled, void, (int flags), , "Enable a set of gestures using flags (bitmask)") {
    SetGesturesEnabled((unsigned int)flags);
}

// RLAPI bool IsGestureDetected(unsigned int gesture);           // Check if a gesture has been detected
DefineEngineFunction( IsGestureDetected, bool, (int gesture), , "Check if a specific gesture has been detected") {
    return IsGestureDetected((unsigned int)gesture);
}

// RLAPI int GetGestureDetected(void);                           // Get latest detected gesture
DefineEngineFunction( GetGestureDetected, int, (), , "Get latest detected gesture type") {
    return GetGestureDetected();
}

// RLAPI float GetGestureHoldDuration(void);                     // Get gesture hold time in seconds
DefineEngineFunction( GetGestureHoldDuration, float, (), , "Get gesture hold time in seconds") {
    return GetGestureHoldDuration();
}

// RLAPI Vector2 GetGestureDragVector(void);                     // Get gesture drag vector
DefineEngineFunction( GetGestureDragVector, Vector2, (), , "Get gesture drag vector as Vector2") {
    return GetGestureDragVector();
}

// RLAPI float GetGestureDragAngle(void);                        // Get gesture drag angle
DefineEngineFunction( GetGestureDragAngle, float, (), , "Get gesture drag angle in degrees") {
    return GetGestureDragAngle();
}

// RLAPI Vector2 GetGesturePinchVector(void);                    // Get gesture pinch delta
DefineEngineFunction( GetGesturePinchVector, Vector2, (), , "Get gesture pinch delta vector as Vector2") {
    return GetGesturePinchVector();
}

// RLAPI float GetGesturePinchAngle(void);                       // Get gesture pinch angle
DefineEngineFunction( GetGesturePinchAngle, float, (), , "Get gesture pinch angle in degrees") {
    return GetGesturePinchAngle();
}
//------------------------------------------------------------------------------------
// Camera System Functions (Module: rcamera)
//------------------------------------------------------------------------------------
// NOTE: implemented in Camera3DObject!
// RLAPI void UpdateCamera(Camera *camera, int mode);            // Update camera position for selected mode
// RLAPI void UpdateCameraPro(Camera *camera, Vector3 movement, Vector3 rotation, float zoom); // Update camera movement/rotation


// -----------------------------------------------------------------------------
// Basic shapes collision detection functions
// -----------------------------------------------------------------------------
// RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);                                           // Check collision between two rectangles
DefineEngineFunction( CheckCollisionRecs, bool, (Rectangle rec1, Rectangle rec2), , "Check collision between two rectangles") {
    return CheckCollisionRecs(rec1, rec2);
}

// RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);        // Check collision between two circles
DefineEngineFunction( CheckCollisionCircles, bool, (Vector2 center1, float radius1, Vector2 center2, float radius2), , "Check collision between two circles") {
    return CheckCollisionCircles(center1, radius1, center2, radius2);
}

// RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);                         // Check collision between circle and rectangle
DefineEngineFunction( CheckCollisionCircleRec, bool, (Vector2 center, float radius, Rectangle rec), , "Check collision between circle and rectangle") {
    return CheckCollisionCircleRec(center, radius, rec);
}

// RLAPI bool CheckCollisionCircleLine(Vector2 center, float radius, Vector2 p1, Vector2 p2);               // Check if circle collides with a line created between two points [p1] and [p2]
DefineEngineFunction( CheckCollisionCircleLine, bool, (Vector2 center, float radius, Vector2 p1, Vector2 p2), , "Check if circle collides with a line created between two points [p1] and [p2]") {
    return CheckCollisionCircleLine(center, radius, p1, p2);
}

// RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec);                                         // Check if point is inside rectangle
DefineEngineFunction( CheckCollisionPointRec, bool, (Vector2 point, Rectangle rec), , "Check if point is inside rectangle") {
    return CheckCollisionPointRec(point, rec);
}

// RLAPI bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);                       // Check if point is inside circle
DefineEngineFunction( CheckCollisionPointCircle, bool, (Vector2 point, Vector2 center, float radius), , "Check if point is inside circle") {
    return CheckCollisionPointCircle(point, center, radius);
}

// RLAPI bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);               // Check if point is inside a triangle
DefineEngineFunction( CheckCollisionPointTriangle, bool, (Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3), , "Check if point is inside a triangle") {
    return CheckCollisionPointTriangle(point, p1, p2, p3);
}

// RLAPI bool CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold);                // Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
DefineEngineFunction( CheckCollisionPointLine, bool, (Vector2 point, Vector2 p1, Vector2 p2, int threshold), , "Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]") {
    return CheckCollisionPointLine(point, p1, p2, threshold);
}

// RLAPI bool CheckCollisionPointPoly(Vector2 point, const Vector2 *points, int pointCount);                // Check if point is within a polygon described by array of vertices
DefineEngineFunction( CheckCollisionPointPoly, bool, (Vector2 point, Vector<F32> pointValues, int pointCount), , "Check if point is within a polygon described by array of vertices") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return false;

    return CheckCollisionPointPoly(point, points.data(), pointCount);
}

// RLAPI bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint); // Check the collision between two lines defined by two points each, returns collision point by reference
DefineEngineFunction( CheckCollisionLines, Vector2, (Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2), , "Check the collision between two lines. Returns 'x y' string if colliding, or empty string if not.") {
    Vector2 collisionPoint = { 0.0f, 0.0f };

    CheckCollisionLines(startPos1, endPos1, startPos2, endPos2, &collisionPoint);
     return collisionPoint;

}


// RLAPI Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);                                         // Get collision rectangle for two rectangles collision
DefineEngineFunction( GetCollisionRec, Rectangle, (Rectangle rec1, Rectangle rec2), , "Get collision rectangle for two rectangles collision") {
    return GetCollisionRec(rec1, rec2);
}



//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------
// FIXME ?
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------

// // Text codepoints management functions (unicode characters)
// RLAPI char *LoadUTF8(const int *codepoints, int length);                                    // Load UTF-8 text encoded from codepoints array
// RLAPI void UnloadUTF8(char *text);                                                          // Unload UTF-8 text encoded from codepoints array
// RLAPI int *LoadCodepoints(const char *text, int *count);                                    // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
// RLAPI void UnloadCodepoints(int *codepoints);                                               // Unload codepoints data from memory
// RLAPI int GetCodepointCount(const char *text);                                              // Get total number of codepoints in a UTF-8 encoded string
// RLAPI int GetCodepoint(const char *text, int *codepointSize);                               // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepointNext(const char *text, int *codepointSize);                           // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepointPrevious(const char *text, int *codepointSize);                       // Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI const char *CodepointToUTF8(int codepoint, int *utf8Size);                            // Encode one codepoint into UTF-8 byte array (array length returned as parameter)

// Text strings management functions (no UTF-8 strings, only byte chars)
// WARNING 1: Most of these functions use internal static buffers[], it's recommended to store returned data on user-side for re-use
// WARNING 2: Some functions allocate memory internally for the returned strings, those strings must be freed by user using MemFree()
// RLAPI char **LoadTextLines(const char *text, int *count);                                   // Load text as separate lines ('\n')
// RLAPI void UnloadTextLines(char **text, int lineCount);                                     // Unload text lines
// RLAPI int TextCopy(char *dst, const char *src);                                             // Copy one string to another, returns bytes copied
// RLAPI bool TextIsEqual(const char *text1, const char *text2);                               // Check if two text strings are equal
// RLAPI unsigned int TextLength(const char *text);                                            // Get text length, checks for '\0' ending
// RLAPI const char *TextFormat(const char *text, ...);                                        // Text formatting with variables (sprintf() style)
// RLAPI const char *TextSubtext(const char *text, int position, int length);                  // Get a piece of a text string
// RLAPI const char *TextRemoveSpaces(const char *text);                                       // Remove text spaces, concat words
// RLAPI char *GetTextBetween(const char *text, const char *begin, const char *end);           // Get text between two strings
// RLAPI char *TextReplace(const char *text, const char *search, const char *replacement);     // Replace text string with new string
// RLAPI char *TextReplaceAlloc(const char *text, const char *search, const char *replacement); // Replace text string with new string, memory must be MemFree()
// RLAPI char *TextReplaceBetween(const char *text, const char *begin, const char *end, const char *replacement); // Replace text between two specific strings
// RLAPI char *TextReplaceBetweenAlloc(const char *text, const char *begin, const char *end, const char *replacement); // Replace text between two specific strings, memory must be MemFree()
// RLAPI char *TextInsert(const char *text, const char *insert, int position);                 // Insert text in a defined byte position
// RLAPI char *TextInsertAlloc(const char *text, const char *insert, int position);            // Insert text in a defined byte position, memory must be MemFree()
// RLAPI char *TextJoin(char **textList, int count, const char *delimiter);                    // Join text strings with delimiter
// RLAPI char **TextSplit(const char *text, char delimiter, int *count);                       // Split text into multiple strings, using MAX_TEXTSPLIT_COUNT static strings
// RLAPI void TextAppend(char *text, const char *append, int *position);                       // Append text at specific position and move cursor
// RLAPI int TextFindIndex(const char *text, const char *search);                              // Find first text occurrence within a string, -1 if not found
// RLAPI char *TextToUpper(const char *text);                                                  // Get upper case version of provided string
// RLAPI char *TextToLower(const char *text);                                                  // Get lower case version of provided string
// RLAPI char *TextToPascal(const char *text);                                                 // Get Pascal case notation version of provided string
// RLAPI char *TextToSnake(const char *text);                                                  // Get Snake case notation version of provided string
// RLAPI char *TextToCamel(const char *text);                                                  // Get Camel case notation version of provided string
// RLAPI int TextToInteger(const char *text);                                                  // Get integer value from text
// RLAPI float TextToFloat(const char *text);                                                  // Get float value from text
