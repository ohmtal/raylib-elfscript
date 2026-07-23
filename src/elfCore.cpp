//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#include "raylib.h"
#include "console/engineAPI.h"
#include "ConsoleTypes.h"
#include "elfResource.h"

//====================================================================================
// Window and Graphics Device Functions (Module: core)
//====================================================================================

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

// elfScript
DefineEngineFunction(GetScreenSize, Vector2, (), , "Get current screen size"){
    return {(F32)GetScreenWidth(), (F32)GetScreenHeight()};
}

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
// Cursor-related functions
// -----------------------------------------------------------------------------
// RLAPI void ShowCursor(void);                                      // Show cursor
DefineEngineFunction(ShowCursor, void, (), , "Show cursor"){
    ShowCursor();
}
// RLAPI void HideCursor(void);                                      // Hide cursor
DefineEngineFunction(HideCursor, void, (), , "Hide cursor"){
    HideCursor();
}

// RLAPI bool IsCursorHidden(void);                                  // Check if cursor is not visible
DefineEngineFunction(IsCursorHidden, bool, (), , "Check if cursor is not visible"){
    return IsCursorHidden();
}

// RLAPI void EnableCursor(void);                                    // Enable cursor (unlock cursor)
DefineEngineFunction(EnableCursor, void, (), , "Enable cursor (unlock cursor)"){
    EnableCursor();
}

// RLAPI void DisableCursor(void);                                   // Disable cursor (lock cursor)
DefineEngineFunction(DisableCursor, void, (), , "Disable cursor (lock cursor)"){
    DisableCursor();
}

// RLAPI bool IsCursorOnScreen(void);                                // Check if cursor is on the screen
DefineEngineFunction(IsCursorOnScreen, bool, (), , "Check if cursor is on the screen"){
    return IsCursorOnScreen();
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

// RLAPI void BeginTextureMode(RenderTexture2D target);
// Begins drawing to render texture
// NOTE moved to RenderTextureObject!
DefineEngineFunction( BeginTextureMode, void, (S32 renderTextureId), , "Begins drawing to render texture") {
    // RenderTexture2D* target = ElfResource::RenderTextureMap.get(renderTextureId);
    // if (!target) return;
    // BeginTextureMode(*target);
    Con::errorf("BeginTextureMode is not available. Create an RenderTextureObject and use it's method BeginTextureMode");
}
DefineEngineFunction(EndTextureMode, void, (),, " End drawing to render texture") {
    // Con::warnf("EndTextureMode can be used but better  create an RenderTextureObject and use it's method EndTextureMode");
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
// Shader management functions
// -----------------------------------------------------------------------------
// NOTE located in elfShader.cpp

// -----------------------------------------------------------------------------
// Screen-space-related functions
// -----------------------------------------------------------------------------
// NOTE located in elfCamera.cpp

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
DefineEngineFunction(GetRandomValues, Vector<S32>, (U32 count, S32 min, S32 max), ,
            "Generate a list of random values. Unline LoadRandomSequence they are NOT uniqe "
            "#elfScript custom function."
)
{
    Vector<S32> result;
    for (S32 i = 0; i < count; i++) result.push_back(GetRandomValue(min,max));
    return result;
}


// RLAPI int *LoadRandomSequence(unsigned int count, int min, int max); // Load random values sequence, no values repeated
DefineEngineFunction(LoadRandomSequence, Vector<S32>, (U32 count, S32 min, S32 max), ,
                     "Load random values sequence, no values repeated, unload automaticly done. "){
   int* sequence = LoadRandomSequence(count, min, max);
   Vector<S32> result;
   if (!sequence) return result;
   for (S32 i = 0; i < count; i++) result.push_back(sequence[i]);
   UnloadRandomSequence(sequence);
   return result;
}

// NOTE: not implemented because it's done in LoadRandomSequence
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
// Logging system
// -----------------------------------------------------------------------------
// RLAPI void SetTraceLogLevel(int logLevel);                      // Set the current threshold (minimum) log level
DefineEngineFunction( SetTraceLogLevel, void, (int logLevel), , "Set the current threshold (minimum) raylib log level (e.g. 2 = LOG_TRACE, 3 = LOG_DEBUG, 4 = LOG_INFO...)") {
    SetTraceLogLevel(logLevel);
}

// NOTE: not implemented .. not possible with script interface
// RLAPI void TraceLog(int logLevel, const char *text, ...);       // Show trace log messages (LOG_DEBUG, LOG_INFO, LOG_WARNING, LOG_ERROR...)
// RLAPI void SetTraceLogCallback(TraceLogCallback callback);      // Set custom trace log

// -----------------------------------------------------------------------------
// Memory management, using internal allocators
// -----------------------------------------------------------------------------
// NOTE: not implemented .. not possible with script interface
// RLAPI void *MemAlloc(unsigned int size);                        // Internal memory allocator
// RLAPI void *MemRealloc(void *ptr, unsigned int size);           // Internal memory reallocator
// RLAPI void MemFree(void *ptr);                                  // Internal memory free

// -----------------------------------------------------------------------------
// File system management functions
// File access custom callbacks
// Compression/Encoding functionality
// -----------------------------------------------------------------------------
// NOTE parts implemented in elfFilecpp .....

//====================================================================================
// Input Handling Functions (Module: core)
//====================================================================================

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
// Input-related functions: gamepads
// -----------------------------------------------------------------------------

// RLAPI bool IsGamepadAvailable(int gamepad);                   // Check if a gamepad is available
DefineEngineFunction(IsGamepadAvailable, bool, (S32 gamepad), , "Check if a gamepad is available"){
    return IsGamepadAvailable(gamepad);
}

// RLAPI const char *GetGamepadName(int gamepad);                // Get gamepad internal name id
DefineEngineFunction(GetGamepadName, String, (S32 gamepad), , "Get gamepad internal name id"){
    return GetGamepadName(gamepad);
}

// RLAPI bool IsGamepadButtonPressed(int gamepad, int button);   // Check if a gamepad button has been pressed once
DefineEngineFunction(IsGamepadButtonPressed, bool, (S32 gamepad, S32 button), , "Check if a gamepad button has been pressed once"){
    return IsGamepadButtonPressed(gamepad, button);
}

// RLAPI bool IsGamepadButtonDown(int gamepad, int button);      // Check if a gamepad button is being pressed
DefineEngineFunction(IsGamepadButtonDown, bool, (S32 gamepad, S32 button), , "Check if a gamepad button is being pressed"){
    return IsGamepadButtonDown(gamepad, button);
}

// RLAPI bool IsGamepadButtonReleased(int gamepad, int button);  // Check if a gamepad button has been released once
DefineEngineFunction(IsGamepadButtonReleased, bool, (S32 gamepad, S32 button), , "Check if a gamepad button has been released once"){
    return IsGamepadButtonReleased(gamepad, button);
}

// RLAPI bool IsGamepadButtonUp(int gamepad, int button);        // Check if a gamepad button is NOT being pressed
DefineEngineFunction(IsGamepadButtonUp, bool, (S32 gamepad, S32 button), , "Check if a gamepad button is NOT being pressed"){
    return IsGamepadButtonUp(gamepad, button);
}

// RLAPI int GetGamepadButtonPressed(void);                      // Get the last gamepad button pressed
DefineEngineFunction(GetGamepadButtonPressed, S32, (), , "Get the last gamepad button pressed"){
    return GetGamepadButtonPressed();
}

// RLAPI int GetGamepadAxisCount(int gamepad);                   // Get axis count for a gamepad
DefineEngineFunction(GetGamepadAxisCount, S32, (S32 gamepad), , "Get axis count for a gamepad"){
    return GetGamepadAxisCount(gamepad);
}

// RLAPI F32 GetGamepadAxisMovement(int gamepad, int axis);    // Get movement value for a gamepad axis
DefineEngineFunction(GetGamepadAxisMovement, F32, (S32 gamepad, S32 axis), , "Get movement value for a gamepad axis"){
    return GetGamepadAxisMovement(gamepad, axis);
}

// RLAPI int SetGamepadMappings(const char *mappings);           // Set internal gamepad mappings (SDL_GameControllerDB)
DefineEngineFunction(SetGamepadMappings, S32, (const char *mappings), , "Set internal gamepad mappings (SDL_GameControllerDB)"){
    return SetGamepadMappings(mappings);
}

// RLAPI void SetGamepadVibration(int gamepad, F32 leftMotor, F32 rightMotor, F32 duration); // Set gamepad vibration for both motors (duration in seconds)
DefineEngineFunction(SetGamepadVibration, void, (S32 gamepad, F32 leftMotor, F32 rightMotor, F32 duration), , "Set gamepad vibration for both motors (duration in seconds)"){
    SetGamepadVibration(gamepad, leftMotor, rightMotor, duration);
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
// Gestures and Touch Handling Functions (NOTE: Module: rgestures)
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
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
