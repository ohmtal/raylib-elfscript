#include "raylib.h"
#include "console/console.h"
#include "console/script.h"
#include "console/engineAPI.h"
#include "ConsoleTypes.h"

// register enum >>>>
// #include "console/consoleExtras.h"
// <<<<
// -----------------------------------------------------------------------------
// Window-related functions
// -----------------------------------------------------------------------------
DefineEngineFunction(InitWindow, void, (S32 width, S32 height, String title),,"Initialize window and OpenGL context"){
    InitWindow(width, height, title);
}
DefineEngineFunction(CloseWindow, void, (),,"Close window and unload OpenGL context"){
    CloseWindow();
}
// -----------------------------------------------------------------------------
// Timing-related functions
// -----------------------------------------------------------------------------

// RLAPI void SetTargetFPS(int fps);                       // Set target FPS (maximum)
DefineEngineFunction(SetTargetFPS, void, (S32 fps),,"Set target FPS (maximum)"){
    SetTargetFPS(fps);
}
// RLAPI float GetFrameTime(void);                         // Get time in seconds for last frame drawn (delta time)
// RLAPI double GetTime(void);                             // Get elapsed time in seconds since InitWindow()
// RLAPI int GetFPS(void);                                 // Get current FPS
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
// RLAPI void BeginMode2D(Camera2D camera);                          // Begin 2D mode with custom camera (2D)
// RLAPI void EndMode2D(void);                                       // End 2D mode with custom camera
// RLAPI void BeginMode3D(Camera3D camera);                          // Begin 3D mode with custom camera (3D)
// RLAPI void EndMode3D(void);                                       // End 3D mode and returns to default 2D orthographic mode
// RLAPI void BeginTextureMode(RenderTexture2D target);              // Begin drawing to render texture
// RLAPI void EndTextureMode(void);                                  // End drawing to render texture
// RLAPI void BeginShaderMode(Shader shader);                        // Begin custom shader drawing
// RLAPI void EndShaderMode(void);                                   // End custom shader drawing (use default shader)
// RLAPI void BeginBlendMode(int mode);                              // Begin blending mode (alpha, additive, multiplied, subtract, custom)
// RLAPI void EndBlendMode(void);                                    // End blending mode (reset to default: alpha blending)
// RLAPI void BeginScissorMode(int x, int y, int width, int height); // Begin scissor mode (define screen area for following drawing)
// RLAPI void EndScissorMode(void);                                  // End scissor mode
// RLAPI void BeginVrStereoMode(VrStereoConfig config);              // Begin stereo rendering (requires VR simulator)
// RLAPI void EndVrStereoMode(void);                                 // End stereo rendering (requires VR simulator)

// -----------------------------------------------------------------------------
// Text drawing functions
// -----------------------------------------------------------------------------
// RLAPI void DrawFPS(int posX, int posY);                                                     // Draw current FPS
DefineEngineFunction( DrawText, void, (const char *text, int posX, int posY
    , int fontSize, Color color), (12 , RAYWHITE), "Draw text (using default font") {
        DrawText(text,posX, posY, fontSize, color);
    }
// RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
// RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
// RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
// RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple characters (codepoint)
