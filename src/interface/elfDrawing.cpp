//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfResource.h"
#include <console/console.h>
#include "console/engineAPI.h"
#include "ConsoleTypes.h"
#include "elfResource.h"

// -----------------------------------------------------------------------------
// Basic shapes drawing functions
// -----------------------------------------------------------------------------
// Set texture and rectangle to be used on shapes drawing
// NOTE: It can be useful when using basic shapes and one single font,
// defining a font char white rectangle would allow drawing everything in a single draw call
// RLAPI void SetShapesTexture(Texture2D texture, Rectangle source); // Set texture and rectangle to be used on shapes drawing
DefineEngineFunction( SetShapesTexture, void, (S32 textureId, Rectangle source), , "Set texture and source rectangle to be used on shapes drawing") {
    Texture2D* tex = ElfResource::TextureMap.get(textureId);
    if (!tex) return;

    SetShapesTexture(*tex, source);
}

// RLAPI Texture2D GetShapesTexture(void);                 // Get texture that is used for shapes drawing
DefineEngineFunction( GetShapesTexture, S32, (), , "Get texture ID currently used for shapes drawing") {
    Texture2D tex = GetShapesTexture();

    // Da diese Textur von Raylib verwaltet wird (oft die interne Standard-Weiß-Textur),
    // fügen wir sie der Map hinzu, damit TorqueScript eine gültige ID bekommt.
    if (!IsTextureValid(tex)) return 0;
    return ElfResource::TextureMap.add(tex);
}

// RLAPI Rectangle GetShapesTextureRectangle(void);        // Get texture source rectangle that is used for shapes drawing
DefineEngineFunction( GetShapesTextureRectangle, Rectangle, (), , "Get texture source rectangle that is used for shapes drawing") {
    return GetShapesTextureRectangle();
}

// -----------------------------------------------------------------------------
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


// RLAPI void DrawLineStrip(const Vector2 *points, int pointCount, Color color);                            // Draw lines sequence (using gl lines)
DefineEngineFunction( DrawLineStrip, void, (Vector<F32> pointValues, int pointCount, Color color), (RAYWHITE), "Draw lines sequence (using gl lines)") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;
    DrawLineStrip(points.data(), pointCount, color);
}

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


// RLAPI void DrawTriangleFan(const Vector2 *points, int pointCount, Color color);                          // Draw a triangle fan defined by points (first vertex is the center)
DefineEngineFunction( DrawTriangleFan, void, (Vector<F32> pointValues, int pointCount, Color color), (RAYWHITE), "Draw a triangle fan defined by points (first vertex is the center)") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;

    DrawTriangleFan(points.data(), pointCount, color);
}


// RLAPI void DrawTriangleStrip(Vector<F32> pointValues, int pointCount, Color color);                        // Draw a triangle strip defined by points
DefineEngineFunction( DrawTriangleStrip, void, (Vector<F32> pointValues, int pointCount, Color color), (RAYWHITE), "Draw a triangle strip defined by points") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;
    DrawTriangleStrip(points.data(), pointCount, color);
}

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
DefineEngineFunction( DrawSplineLinear, void, (Vector<F32> pointValues, int pointCount, float thick, Color color), (RAYWHITE), "Draw spline: Linear, minimum 2 points") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;
    DrawSplineLinear(points.data(), pointCount, thick, color);
}

// RLAPI void DrawSplineBasis(const Vector2 *points, int pointCount, float thick, Color color);             // Draw spline: B-Spline, minimum 4 points
DefineEngineFunction( DrawSplineBasis, void, (Vector<F32> pointValues, int pointCount, float thick, Color color), (RAYWHITE), "Draw spline: B-Spline, minimum 4 points") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;
    DrawSplineBasis(points.data(), pointCount, thick, color);
}

// RLAPI void DrawSplineCatmullRom(const Vector2 *points, int pointCount, float thick, Color color);        // Draw spline: Catmull-Rom, minimum 4 points
DefineEngineFunction( DrawSplineCatmullRom, void, (Vector<F32> pointValues, int pointCount, float thick, Color color), (RAYWHITE), "Draw spline: Catmull-Rom, minimum 4 points") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;
    DrawSplineCatmullRom(points.data(), pointCount, thick, color);
}

// RLAPI void DrawSplineBezierQuadratic(const Vector2 *points, int pointCount, float thick, Color color);   // Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]
DefineEngineFunction( DrawSplineBezierQuadratic, void, (Vector<F32> pointValues, int pointCount, float thick, Color color), (RAYWHITE), "Draw spline: Quadratic Bezier, minimum 3 points (1 control point): [p1, c2, p3, c4...]") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;
    DrawSplineBezierQuadratic(points.data(), pointCount, thick, color);
}

// RLAPI void DrawSplineBezierCubic(const Vector2 *points, int pointCount, float thick, Color color);       // Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]
DefineEngineFunction( DrawSplineBezierCubic, void, (Vector<F32> pointValues, int pointCount, float thick, Color color), (RAYWHITE), "Draw spline: Cubic Bezier, minimum 4 points (2 control points): [p1, c2, c3, p4, c5, c6...]") {
    auto points = ElfResource::getVector2List(pointValues, pointCount);
    if (points.size() != (size_t) pointCount ) return;
    DrawSplineBezierCubic(points.data(), pointCount, thick, color);
}

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
