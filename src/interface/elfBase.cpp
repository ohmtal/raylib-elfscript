#include "raylib.h"
#include "console/console.h"
#include "console/script.h"
#include "console/engineAPI.h"
#include "ConsoleTypes.h"
#include "console/consoleExtras.h" // registerEnum

// -----------------------------------------------------------------------------
// TraceLog raylib log to Con::.. log.
// -----------------------------------------------------------------------------
//FIXME what it that ? =>
//  TEXTURE: [ID 125595416] Texture loaded successfully (125595416x-2118071736 | UH��H�� �}�H�u�H�U��}�tn�}��� | -2118068406 mipmaps)
void CustomTraceLog(int msgType, const char *text, va_list args)
{
    switch (msgType)
    {
        case LOG_INFO: Con::infof(text,args); break;
        case LOG_ERROR: Con::errorf(text,args); break;
        case LOG_FATAL: Con::errorf(text,args); break;
        case LOG_WARNING: Con::warnf(text,args); break;
        case LOG_DEBUG: Con::debugf(text,args); break;
        default: break;
    }
}
// -----------------------------------------------------------------------------
// ENUM
// -----------------------------------------------------------------------------
void initEnum() {
   Con::registerEnumS32<KeyboardKey>("");
   Con::registerEnumS32<ConfigFlags>("");
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
   Con::registerEnumS32<Gesture>("");
   Con::registerEnumS32<CameraMode>("");
   Con::registerEnumS32<CameraProjection>("");
   Con::registerEnumS32<NPatchLayout>("");
}
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

    //FIXME FONT !!
    // // RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
    // DefineEngineFunction( DrawTextEx, void, (Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint), (RAYWHITE), "Draw text using font and additional parameters") {
    //     DrawTextEx(font, text, position, fontSize, spacing, tint);
    // }
    //
    // // RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
    // DefineEngineFunction( DrawTextPro, void, (Font font, const char *text, Vector2 position,
    //                 Vector2 origin, float rotation, float fontSize, float spacing, Color tint), (RAYWHITE),
    //                 "Draw text using Font and pro parameters (rotation)") {
    //     DrawTextPro(font, text, position, origin, rotation, fontSize, spacing, tint);
    // }
// RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
// RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple characters (codepoint)

// -----------------------------------------------------------------------------
// Input-related functions: keyboard
// -----------------------------------------------------------------------------
                         //
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
// FIXME: not working ???? GetKeyName return nullptr
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
// RLAPI void SetMouseOffset(int offsetX, int offsetY);          // Set mouse offset
// RLAPI void SetMouseScale(float scaleX, float scaleY);         // Set mouse scaling
DefineEngineFunction( GetMouseWheelMove, F32, (), , " Get mouse wheel movement for X or Y, whichever is larger") {
    return GetMouseWheelMove();
}
// RLAPI Vector2 GetMouseWheelMoveV(void);                       // Get mouse wheel movement for both X and Y
// RLAPI void SetMouseCursor(int cursor);                        // Set mouse cursor
// -----------------------------------------------------------------------------
// Basic shapes drawing functions
// -----------------------------------------------------------------------------
// RLAPI void DrawPixel(int posX, int posY, Color color);                                                   // Draw a pixel using geometry [Can be slow, use with care]
DefineEngineFunction( DrawPixel, void, (int posX, int posY, Color color), (RAYWHITE), "Draw a pixel using geometry [Can be slow, use with care]") {
    DrawPixel(posX, posY, color);
}

// RLAPI void DrawPixelV(Vector2 position, Color color);                                                    // Draw a pixel using geometry (Vector version) [Can be slow, use with care]
DefineEngineFunction( DrawPixelV, void, (Vector2 position, Color color), (RAYWHITE), "Draw a pixel using geometry (Vector version) [Can be slow, use with care]") {
    DrawPixelV(position, color);
}

// RLAPI void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);                // Draw a line
DefineEngineFunction( DrawLine, void, (int startPosX, int startPosY, int endPosX, int endPosY, Color color), (RAYWHITE), "Draw a line") {
    DrawLine(startPosX, startPosY, endPosX, endPosY, color);
}

// RLAPI void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);                                     // Draw a line (using gl lines)
DefineEngineFunction( DrawLineV, void, (Vector2 startPos, Vector2 endPos, Color color), (RAYWHITE), "Draw a line (using gl lines)") {
    DrawLineV(startPos, endPos, color);
}

// RLAPI void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);                       // Draw a line (using triangles/quads)
DefineEngineFunction( DrawLineEx, void, (Vector2 startPos, Vector2 endPos, float thick, Color color), (RAYWHITE), "Draw a line (using triangles/quads)") {
    DrawLineEx(startPos, endPos, thick, color);
}

//FIXME pointer ^^
// RLAPI void DrawLineStrip(const Vector2 *points, int pointCount, Color color);                            // Draw lines sequence (using gl lines)
// DefineEngineFunction( DrawLineStrip, void, (const Vector2 points, int pointCount, Color color), (RAYWHITE), "Draw lines sequence (using gl lines)") {
//     DrawLineStrip(points, pointCount, color);
// }

// RLAPI void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);                   // Draw line segment cubic-bezier in-out interpolation
DefineEngineFunction( DrawLineBezier, void, (Vector2 startPos, Vector2 endPos, float thick, Color color), (RAYWHITE), "Draw line segment cubic-bezier in-out interpolation") {
    DrawLineBezier(startPos, endPos, thick, color);
}

// RLAPI void DrawLineDashed(Vector2 startPos, Vector2 endPos, int dashSize, int spaceSize, Color color);   // Draw a dashed line
DefineEngineFunction( DrawLineDashed, void, (Vector2 startPos, Vector2 endPos, int dashSize, int spaceSize, Color color), (RAYWHITE), "Draw a dashed line") {
    DrawLineDashed(startPos, endPos, dashSize, spaceSize, color);
}

// RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color);                              // Draw a color-filled circle
DefineEngineFunction( DrawCircle, void, (int centerX, int centerY, float radius, Color color), (RAYWHITE), "Draw a color-filled circle") {
    DrawCircle(centerX, centerY, radius, color);
}

// RLAPI void DrawCircleV(Vector2 center, float radius, Color color); // Draw a filled circle within an image (Vector version)
DefineEngineFunction( DrawCircleV, void, (Vector2 center, float radius, Color color), (RAYWHITE), "Draw a filled circle within an image (Vector version)") {
    DrawCircleV(center, radius, color);
}

// RLAPI void DrawCircleGradient(Vector2 center, float radius, Color inner, Color outer);                   // Draw a gradient-filled circle
DefineEngineFunction( DrawCircleGradient, void, (Vector2 center, float radius, Color inner,
            Color outer), , "Draw a gradient-filled circle") {
    DrawCircleGradient(center, radius, inner, outer);
}

// RLAPI void DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color); // Draw a piece of a circle
DefineEngineFunction( DrawCircleSector, void, (Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color), (RAYWHITE), "Draw a piece of a circle") {
    DrawCircleSector(center, radius, startAngle, endAngle, segments, color);
}

// RLAPI void DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color); // Draw circle sector outline
DefineEngineFunction( DrawCircleSectorLines, void, (Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color), (RAYWHITE), "Draw circle sector outline") {
    DrawCircleSectorLines(center, radius, startAngle, endAngle, segments, color);
}

// RLAPI void DrawCircleLines(int centerX, int centerY, float radius, Color color);                         // Draw circle outline
DefineEngineFunction( DrawCircleLines, void, (int centerX, int centerY, float radius, Color color), (RAYWHITE), "Draw circle outline") {
    DrawCircleLines(centerX, centerY, radius, color);
}

// RLAPI void DrawCircleLinesV(Vector2 center, float radius, Color color);                                  // Draw circle outline (Vector version)
DefineEngineFunction( DrawCircleLinesV, void, (Vector2 center, float radius, Color color), (RAYWHITE), "Draw circle outline (Vector version)") {
    DrawCircleLinesV(center, radius, color);
}

// RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);             // Draw ellipse
DefineEngineFunction( DrawEllipse, void, (int centerX, int centerY, float radiusH, float radiusV, Color color), (RAYWHITE), "Draw ellipse") {
    DrawEllipse(centerX, centerY, radiusH, radiusV, color);
}

// RLAPI void DrawEllipseV(Vector2 center, float radiusH, float radiusV, Color color);                      // Draw ellipse (Vector version)
DefineEngineFunction( DrawEllipseV, void, (Vector2 center, float radiusH, float radiusV, Color color), (RAYWHITE), "Draw ellipse (Vector version)") {
    DrawEllipseV(center, radiusH, radiusV, color);
}

// RLAPI void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);        // Draw ellipse outline
DefineEngineFunction( DrawEllipseLines, void, (int centerX, int centerY, float radiusH, float radiusV, Color color), (RAYWHITE), "Draw ellipse outline") {
    DrawEllipseLines(centerX, centerY, radiusH, radiusV, color);
}

// RLAPI void DrawEllipseLinesV(Vector2 center, float radiusH, float radiusV, Color color);                 // Draw ellipse outline (Vector version)
DefineEngineFunction( DrawEllipseLinesV, void, (Vector2 center, float radiusH, float radiusV, Color color), (RAYWHITE), "Draw ellipse outline (Vector version)") {
    DrawEllipseLinesV(center, radiusH, radiusV, color);
}

// RLAPI void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); // Draw ring
DefineEngineFunction( DrawRing, void, (Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color), (RAYWHITE), "Draw ring") {
    DrawRing(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
}

// RLAPI void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); // Draw ring outline
DefineEngineFunction( DrawRingLines, void, (Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color), (RAYWHITE), "Draw ring outline") {
    DrawRingLines(center, innerRadius, outerRadius, startAngle, endAngle, segments, color);
}

// RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);                        // Draw a color-filled rectangle
DefineEngineFunction( DrawRectangle, void, (int posX, int posY, int width, int height, Color color), (RAYWHITE), "Draw a color-filled rectangle") {
    DrawRectangle(posX, posY, width, height, color);
}

// RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  // Draw a color-filled rectangle (Vector version)
DefineEngineFunction( DrawRectangleV, void, (Vector2 position, Vector2 size, Color color), (RAYWHITE), "Draw a color-filled rectangle (Vector version)") {
    DrawRectangleV(position, size, color);
}

// RLAPI void DrawRectangleRec(Rectangle rec, Color color);                                                 // Draw a color-filled rectangle
DefineEngineFunction( DrawRectangleRec, void, (Rectangle rec, Color color), (RAYWHITE), "Draw a color-filled rectangle") {
    DrawRectangleRec(rec, color);
}

// RLAPI void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);                 // Draw a color-filled rectangle with pro parameters
DefineEngineFunction( DrawRectanglePro, void, (Rectangle rec, Vector2 origin, float rotation, Color color), (RAYWHITE), "Draw a color-filled rectangle with pro parameters") {
    DrawRectanglePro(rec, origin, rotation, color);
}

// RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color top, Color bottom);   // Draw a vertical-gradient-filled rectangle
DefineEngineFunction( DrawRectangleGradientV, void, (int posX, int posY, int width, int height,
        Color top, Color bottom), , "Draw a vertical-gradient-filled rectangle") {
    DrawRectangleGradientV(posX, posY, width, height, top, bottom);
}

// RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color left, Color right);   // Draw a horizontal-gradient-filled rectangle
DefineEngineFunction( DrawRectangleGradientH, void, (int posX, int posY, int width, int height,
        Color left, Color right), , "Draw a horizontal-gradient-filled rectangle") {
    DrawRectangleGradientH(posX, posY, width, height, left, right);
}

// RLAPI void DrawRectangleGradientEx(Rectangle rec, Color topLeft, Color bottomLeft, Color bottomRight, Color topRight); // Draw a gradient-filled rectangle with custom vertex colors
DefineEngineFunction( DrawRectangleGradientEx, void,
                (Rectangle rec, Color topLeft, Color bottomLeft, Color bottomRight, Color topRight)
                , , "Draw a gradient-filled rectangle with custom vertex colors") {
    DrawRectangleGradientEx(rec, topLeft, bottomLeft, bottomRight, topRight);
}

// RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
DefineEngineFunction( DrawRectangleLines, void, (int posX, int posY, int width, int height, Color color), (RAYWHITE), "Draw rectangle outline") {
    DrawRectangleLines(posX, posY, width, height, color);
}

// RLAPI void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);                            // Draw rectangle outline with extended parameters
DefineEngineFunction( DrawRectangleLinesEx, void, (Rectangle rec, float lineThick, Color color), (RAYWHITE), "Draw rectangle outline with extended parameters") {
    DrawRectangleLinesEx(rec, lineThick, color);
}

// RLAPI void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);              // Draw rectangle with rounded edges
DefineEngineFunction( DrawRectangleRounded, void, (Rectangle rec, float roundness, int segments, Color color), (RAYWHITE), "Draw rectangle with rounded edges") {
    DrawRectangleRounded(rec, roundness, segments, color);
}

// RLAPI void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, Color color);         // Draw rectangle lines with rounded edges
DefineEngineFunction( DrawRectangleRoundedLines, void, (Rectangle rec, float roundness, int segments, Color color), (RAYWHITE), "Draw rectangle lines with rounded edges") {
    DrawRectangleRoundedLines(rec, roundness, segments, color);
}

// RLAPI void DrawRectangleRoundedLinesEx(Rectangle rec, float roundness, int segments, float lineThick, Color color); // Draw rectangle lines with rounded edges outline
DefineEngineFunction( DrawRectangleRoundedLinesEx, void, (Rectangle rec, float roundness, int segments, float lineThick, Color color), (RAYWHITE), "Draw rectangle lines with rounded edges outline") {
    DrawRectangleRoundedLinesEx(rec, roundness, segments, lineThick, color);
}

// RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                // Draw a color-filled triangle (vertex in counter-clockwise order!)
DefineEngineFunction( DrawTriangle, void, (Vector2 v1, Vector2 v2, Vector2 v3, Color color), (RAYWHITE), "Draw a color-filled triangle (vertex in counter-clockwise order!)") {
    DrawTriangle(v1, v2, v3, color);
}

// RLAPI void DrawTriangleGradient(Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3);       // Draw triangle with interpolated colors (vertex in counter-clockwise order!)
DefineEngineFunction( DrawTriangleGradient, void, (
        Vector2 v1, Vector2 v2, Vector2 v3,
        Color c1, Color c2, Color c3), ,
        "Draw triangle with interpolated colors (vertex in counter-clockwise order!)") {
    DrawTriangleGradient(v1, v2, v3, c1, c2, c3);
}

// RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                           // Draw triangle outline (vertex in counter-clockwise order!)
DefineEngineFunction( DrawTriangleLines, void, (Vector2 v1, Vector2 v2, Vector2 v3, Color color), (RAYWHITE), "Draw triangle outline (vertex in counter-clockwise order!)") {
    DrawTriangleLines(v1, v2, v3, color);
}

//FIXME POINTER
// RLAPI void DrawTriangleFan(const Vector2 *points, int pointCount, Color color);                          // Draw a triangle fan defined by points (first vertex is the center)
// DefineEngineFunction( DrawTriangleFan, void, (const Vector2 *points, int pointCount, Color color), (RAYWHITE), "Draw a triangle fan defined by points (first vertex is the center)") {
//     DrawTriangleFan(points, pointCount, color);
// }

//FIXME POINTER
// RLAPI void DrawTriangleStrip(const Vector2 *points, int pointCount, Color color);                        // Draw a triangle strip defined by points
// DefineEngineFunction( DrawTriangleStrip, void, (const Vector2 *points, int pointCount, Color color), (RAYWHITE), "Draw a triangle strip defined by points") {
//     DrawTriangleStrip(points, pointCount, color);
// }

// RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);               // Draw a polygon of n sides
DefineEngineFunction( DrawPoly, void, (Vector2 center, int sides, float radius, float rotation, Color color), (RAYWHITE), "Draw a polygon of n sides") {
    DrawPoly(center, sides, radius, rotation, color);
}

// RLAPI void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color);          // Draw a polygon outline of n sides
DefineEngineFunction( DrawPolyLines, void, (Vector2 center, int sides, float radius, float rotation, Color color), (RAYWHITE), "Draw a polygon outline of n sides") {
    DrawPolyLines(center, sides, radius, rotation, color);
}

// RLAPI void DrawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color); // Draw a polygon outline of n sides with extended parameters
DefineEngineFunction( DrawPolyLinesEx, void, (Vector2 center, int sides, float radius, float rotation, float lineThick, Color color), (RAYWHITE), "Draw a polygon outline of n sides with extended parameters") {
    DrawPolyLinesEx(center, sides, radius, rotation, lineThick, color);
}
// -----------------------------------------------------------------------------
// Splines drawing functions
// -----------------------------------------------------------------------------
// RLAPI void DrawSplineLinear(const Vector2 *points, int pointCount, float thick, Color color);            // Draw spline: Linear, minimum 2 points
//FIXME POINTER

// RLAPI void DrawSplineBasis(const Vector2 *points, int pointCount, float thick, Color color);             // Draw spline: B-Spline, minimum 4 points
//FIXME POINTER

// RLAPI void DrawSplineCatmullRom(const Vector2 *points, int pointCount, float thick, Color color);        // Draw spline: Catmull-Rom, minimum 4 points
//FIXME POINTER

// RLAPI void DrawSplineBezierQuadratic(const Vector2 *points, int pointCount, float thick, Color color);   // Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
//FIXME POINTER

// RLAPI void DrawSplineBezierCubic(const Vector2 *points, int pointCount, float thick, Color color);       // Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
//FIXME POINTER

// RLAPI void DrawSplineSegmentLinear(Vector2 p1, Vector2 p2, float thick, Color color);                    // Draw spline segment: Linear, 2 points
DefineEngineFunction( DrawSplineSegmentLinear, void, (Vector2 p1, Vector2 p2, float thick, Color color), (RAYWHITE), "Draw spline segment: Linear, 2 points") {
    DrawSplineSegmentLinear(p1, p2, thick, color);
}

// RLAPI void DrawSplineSegmentBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color); // Draw spline segment: B-Spline, 4 points
DefineEngineFunction( DrawSplineSegmentBasis, void, (Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color), (RAYWHITE), "Draw spline segment: B-Spline, 4 points") {
    DrawSplineSegmentBasis(p1, p2, p3, p4, thick, color);
}

// RLAPI void DrawSplineSegmentCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color); // Draw spline segment: Catmull-Rom, 4 points
DefineEngineFunction( DrawSplineSegmentCatmullRom, void, (Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color), (RAYWHITE), "Draw spline segment: Catmull-Rom, 4 points") {
    DrawSplineSegmentCatmullRom(p1, p2, p3, p4, thick, color);
}

// RLAPI void DrawSplineSegmentBezierQuadratic(Vector2 p1, Vector2 c2, Vector2 p3, float thick, Color color); // Draw spline segment: Quadratic Bezier, 2 points, 1 control point
DefineEngineFunction( DrawSplineSegmentBezierQuadratic, void, (Vector2 p1, Vector2 c2, Vector2 p3, float thick, Color color), (RAYWHITE), "Draw spline segment: Quadratic Bezier, 2 points, 1 control point") {
    DrawSplineSegmentBezierQuadratic(p1, c2, p3, thick, color);
}

// RLAPI void DrawSplineSegmentBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float thick, Color color); // Draw spline segment: Cubic Bezier, 2 points, 2 control points
DefineEngineFunction( DrawSplineSegmentBezierCubic, void, (Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float thick, Color color), (RAYWHITE), "Draw spline segment: Cubic Bezier, 2 points, 2 control points") {
    DrawSplineSegmentBezierCubic(p1, c2, c3, p4, thick, color);
}

// RLAPI Vector2 GetSplinePointLinear(Vector2 startPos, Vector2 endPos, float t);                           // Get (evaluate) spline point: Linear
DefineEngineFunction( GetSplinePointLinear, Vector2, (Vector2 startPos, Vector2 endPos, float t), , "Get (evaluate) spline point: Linear") {
    return GetSplinePointLinear(startPos, endPos, t);
}

// RLAPI Vector2 GetSplinePointBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);              // Get (evaluate) spline point: B-Spline
DefineEngineFunction( GetSplinePointBasis, Vector2, (Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t), , "Get (evaluate) spline point: B-Spline") {
    return GetSplinePointBasis(p1, p2, p3, p4, t);
}

// RLAPI Vector2 GetSplinePointCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);         // Get (evaluate) spline point: Catmull-Rom
DefineEngineFunction( GetSplinePointCatmullRom, Vector2, (Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t), , "Get (evaluate) spline point: Catmull-Rom") {
    return GetSplinePointCatmullRom(p1, p2, p3, p4, t);
}

// RLAPI Vector2 GetSplinePointBezierQuadratic(Vector2 p1, Vector2 c2, Vector2 p3, float t);                // Get (evaluate) spline point: Quadratic Bezier
DefineEngineFunction( GetSplinePointBezierQuadratic, Vector2, (Vector2 p1, Vector2 c2, Vector2 p3, float t), , "Get (evaluate) spline point: Quadratic Bezier") {
    return GetSplinePointBezierQuadratic(p1, c2, p3, t);
}

// RLAPI Vector2 GetSplinePointBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t);        // Get (evaluate) spline point: Cubic Bezier
DefineEngineFunction( GetSplinePointBezierCubic, Vector2, (Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t), , "Get (evaluate) spline point: Cubic Bezier") {
    return GetSplinePointBezierCubic(p1, c2, c3, p4, t);
}
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
//FIXME POINTER

// RLAPI bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint); // Check the collision between two lines defined by two points each, returns collision point by reference
//FIXME POINTER

// RLAPI Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);                                         // Get collision rectangle for two rectangles collision
DefineEngineFunction( GetCollisionRec, Rectangle, (Rectangle rec1, Rectangle rec2), , "Get collision rectangle for two rectangles collision") {
    return GetCollisionRec(rec1, rec2);
}
