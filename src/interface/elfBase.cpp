#include "raylib.h"
#include "console/console.h"
#include "console/script.h"
#include "console/engineAPI.h"
#include "ConsoleTypes.h"
#include "console/consoleExtras.h" // registerEnum

// -----------------------------------------------------------------------------
// ENUM
// -----------------------------------------------------------------------------
void initEnum() {
   Con::registerEnumS32<KeyboardKey>("");
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
// RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
// RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
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
// RLAPI int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
// RLAPI const char *GetKeyName(int key);                        // Get name of a QWERTY key on the current keyboard layout (eg returns string 'q' for KEY_A on an AZERTY keyboard)
// RLAPI void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)
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
    F32 tmpFloat = GetMouseWheelMove();
    if (tmpFloat != 0.f) Con::printf("GetMouseWheelMove %f", tmpFloat);
    return tmpFloat;
}
// RLAPI Vector2 GetMouseWheelMoveV(void);                       // Get mouse wheel movement for both X and Y
// RLAPI void SetMouseCursor(int cursor);                        // Set mouse cursor
// -----------------------------------------------------------------------------
// Basic shapes drawing functions
// -----------------------------------------------------------------------------
// RLAPI void DrawPixel(int posX, int posY, Color color);                                                   // Draw a pixel using geometry [Can be slow, use with care]
// RLAPI void DrawPixelV(Vector2 position, Color color);                                                    // Draw a pixel using geometry (Vector version) [Can be slow, use with care]
// RLAPI void DrawLine(int startPosX, int startPosY, int endPosX, int endPosY, Color color);                // Draw a line
// RLAPI void DrawLineV(Vector2 startPos, Vector2 endPos, Color color);                                     // Draw a line (using gl lines)
// RLAPI void DrawLineEx(Vector2 startPos, Vector2 endPos, float thick, Color color);                       // Draw a line (using triangles/quads)
// RLAPI void DrawLineStrip(const Vector2 *points, int pointCount, Color color);                            // Draw lines sequence (using gl lines)
// RLAPI void DrawLineBezier(Vector2 startPos, Vector2 endPos, float thick, Color color);                   // Draw line segment cubic-bezier in-out interpolation
// RLAPI void DrawLineDashed(Vector2 startPos, Vector2 endPos, int dashSize, int spaceSize, Color color);   // Draw a dashed line
// RLAPI void DrawCircle(int centerX, int centerY, float radius, Color color);                              // Draw a color-filled circle
// RLAPI void DrawCircleV(Vector2 center, float radius, Color color);
DefineEngineFunction( DrawCircleV, void, (Vector2 center, float radius, Color color), (RAYWHITE), "  // Draw a filled circle within an image (Vector version)") {
    DrawCircleV(center, radius, color);
}

// RLAPI void DrawCircleGradient(Vector2 center, float radius, Color inner, Color outer);                   // Draw a gradient-filled circle
// RLAPI void DrawCircleSector(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color); // Draw a piece of a circle
// RLAPI void DrawCircleSectorLines(Vector2 center, float radius, float startAngle, float endAngle, int segments, Color color); // Draw circle sector outline
// RLAPI void DrawCircleLines(int centerX, int centerY, float radius, Color color);                         // Draw circle outline
// RLAPI void DrawCircleLinesV(Vector2 center, float radius, Color color);                                  // Draw circle outline (Vector version)
// RLAPI void DrawEllipse(int centerX, int centerY, float radiusH, float radiusV, Color color);             // Draw ellipse
// RLAPI void DrawEllipseV(Vector2 center, float radiusH, float radiusV, Color color);                      // Draw ellipse (Vector version)
// RLAPI void DrawEllipseLines(int centerX, int centerY, float radiusH, float radiusV, Color color);        // Draw ellipse outline
// RLAPI void DrawEllipseLinesV(Vector2 center, float radiusH, float radiusV, Color color);                 // Draw ellipse outline (Vector version)
// RLAPI void DrawRing(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); // Draw ring
// RLAPI void DrawRingLines(Vector2 center, float innerRadius, float outerRadius, float startAngle, float endAngle, int segments, Color color); // Draw ring outline
// RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);                        // Draw a color-filled rectangle
// RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  // Draw a color-filled rectangle (Vector version)
// RLAPI void DrawRectangleRec(Rectangle rec, Color color);                                                 // Draw a color-filled rectangle
// RLAPI void DrawRectanglePro(Rectangle rec, Vector2 origin, float rotation, Color color);                 // Draw a color-filled rectangle with pro parameters
// RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color top, Color bottom);   // Draw a vertical-gradient-filled rectangle
// RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color left, Color right);   // Draw a horizontal-gradient-filled rectangle
// RLAPI void DrawRectangleGradientEx(Rectangle rec, Color topLeft, Color bottomLeft, Color bottomRight, Color topRight); // Draw a gradient-filled rectangle with custom vertex colors
// RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
// RLAPI void DrawRectangleLinesEx(Rectangle rec, float lineThick, Color color);                            // Draw rectangle outline with extended parameters
// RLAPI void DrawRectangleRounded(Rectangle rec, float roundness, int segments, Color color);              // Draw rectangle with rounded edges
// RLAPI void DrawRectangleRoundedLines(Rectangle rec, float roundness, int segments, Color color);         // Draw rectangle lines with rounded edges
// RLAPI void DrawRectangleRoundedLinesEx(Rectangle rec, float roundness, int segments, float lineThick, Color color); // Draw rectangle lines with rounded edges outline
// RLAPI void DrawTriangle(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                                // Draw a color-filled triangle (vertex in counter-clockwise order!)
// RLAPI void DrawTriangleGradient(Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3);       // Draw triangle with interpolated colors (vertex in counter-clockwise order!)
// RLAPI void DrawTriangleLines(Vector2 v1, Vector2 v2, Vector2 v3, Color color);                           // Draw triangle outline (vertex in counter-clockwise order!)
// RLAPI void DrawTriangleFan(const Vector2 *points, int pointCount, Color color);                          // Draw a triangle fan defined by points (first vertex is the center)
// RLAPI void DrawTriangleStrip(const Vector2 *points, int pointCount, Color color);                        // Draw a triangle strip defined by points
// RLAPI void DrawPoly(Vector2 center, int sides, float radius, float rotation, Color color);               // Draw a polygon of n sides
// RLAPI void DrawPolyLines(Vector2 center, int sides, float radius, float rotation, Color color);          // Draw a polygon outline of n sides
// RLAPI void DrawPolyLinesEx(Vector2 center, int sides, float radius, float rotation, float lineThick, Color color); // Draw a polygon outline of n sides with extended parameters
//
// // Splines drawing functions
// RLAPI void DrawSplineLinear(const Vector2 *points, int pointCount, float thick, Color color);            // Draw spline: Linear, minimum 2 points
// RLAPI void DrawSplineBasis(const Vector2 *points, int pointCount, float thick, Color color);             // Draw spline: B-Spline, minimum 4 points
// RLAPI void DrawSplineCatmullRom(const Vector2 *points, int pointCount, float thick, Color color);        // Draw spline: Catmull-Rom, minimum 4 points
// RLAPI void DrawSplineBezierQuadratic(const Vector2 *points, int pointCount, float thick, Color color);   // Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
// RLAPI void DrawSplineBezierCubic(const Vector2 *points, int pointCount, float thick, Color color);       // Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
// RLAPI void DrawSplineSegmentLinear(Vector2 p1, Vector2 p2, float thick, Color color);                    // Draw spline segment: Linear, 2 points
// RLAPI void DrawSplineSegmentBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color); // Draw spline segment: B-Spline, 4 points
// RLAPI void DrawSplineSegmentCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float thick, Color color); // Draw spline segment: Catmull-Rom, 4 points
// RLAPI void DrawSplineSegmentBezierQuadratic(Vector2 p1, Vector2 c2, Vector2 p3, float thick, Color color); // Draw spline segment: Quadratic Bezier, 2 points, 1 control point
// RLAPI void DrawSplineSegmentBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float thick, Color color); // Draw spline segment: Cubic Bezier, 2 points, 2 control points
//
// // Spline segment point evaluation functions, for a given t [0.0f .. 1.0f]
// RLAPI Vector2 GetSplinePointLinear(Vector2 startPos, Vector2 endPos, float t);                           // Get (evaluate) spline point: Linear
// RLAPI Vector2 GetSplinePointBasis(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);              // Get (evaluate) spline point: B-Spline
// RLAPI Vector2 GetSplinePointCatmullRom(Vector2 p1, Vector2 p2, Vector2 p3, Vector2 p4, float t);         // Get (evaluate) spline point: Catmull-Rom
// RLAPI Vector2 GetSplinePointBezierQuadratic(Vector2 p1, Vector2 c2, Vector2 p3, float t);                // Get (evaluate) spline point: Quadratic Bezier
// RLAPI Vector2 GetSplinePointBezierCubic(Vector2 p1, Vector2 c2, Vector2 c3, Vector2 p4, float t);        // Get (evaluate) spline point: Cubic Bezier
//
// // Basic shapes collision detection functions
// RLAPI bool CheckCollisionRecs(Rectangle rec1, Rectangle rec2);                                           // Check collision between two rectangles
// RLAPI bool CheckCollisionCircles(Vector2 center1, float radius1, Vector2 center2, float radius2);        // Check collision between two circles
// RLAPI bool CheckCollisionCircleRec(Vector2 center, float radius, Rectangle rec);                         // Check collision between circle and rectangle
// RLAPI bool CheckCollisionCircleLine(Vector2 center, float radius, Vector2 p1, Vector2 p2);               // Check if circle collides with a line created between two points [p1] and [p2]
// RLAPI bool CheckCollisionPointRec(Vector2 point, Rectangle rec);                                         // Check if point is inside rectangle
// RLAPI bool CheckCollisionPointCircle(Vector2 point, Vector2 center, float radius);                       // Check if point is inside circle
// RLAPI bool CheckCollisionPointTriangle(Vector2 point, Vector2 p1, Vector2 p2, Vector2 p3);               // Check if point is inside a triangle
// RLAPI bool CheckCollisionPointLine(Vector2 point, Vector2 p1, Vector2 p2, int threshold);                // Check if point belongs to line created between two points [p1] and [p2] with defined margin in pixels [threshold]
// RLAPI bool CheckCollisionPointPoly(Vector2 point, const Vector2 *points, int pointCount);                // Check if point is within a polygon described by array of vertices
// RLAPI bool CheckCollisionLines(Vector2 startPos1, Vector2 endPos1, Vector2 startPos2, Vector2 endPos2, Vector2 *collisionPoint); // Check the collision between two lines defined by two points each, returns collision point by reference
// RLAPI Rectangle GetCollisionRec(Rectangle rec1, Rectangle rec2);                                         // Get collision rectangle for two rectangles collision
