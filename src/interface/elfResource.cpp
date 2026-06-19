//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfStorage.h"
#include <console/console.h>

namespace ElfResource {


    void shutDown() {
        Con::printf("Unloading resources...");
        ImageMap.clear();
        TextureMap.clear();
        FontMap.clear();
    }
    // -----------------------------------------------------------------------------------
    // Texture loading functions
    // -----------------------------------------------------------------------------------

//     // NOTE: These functions require GPU access
//     RLAPI Texture2D LoadTexture(const char *fileName);                                                       // Load texture from file into GPU memory (VRAM)
//     RLAPI Texture2D LoadTextureFromImage(Image image);                                                       // Load texture from image data
//     RLAPI TextureCubemap LoadTextureCubemap(Image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
//     RLAPI RenderTexture2D LoadRenderTexture(int width, int height);                                          // Load texture for rendering (framebuffer)
//     RLAPI bool IsTextureValid(Texture2D texture);                                                            // Check if a texture is valid (loaded in GPU)
//     RLAPI void UnloadTexture(Texture2D texture);                                                             // Unload texture from GPU memory (VRAM)
//     RLAPI bool IsRenderTextureValid(RenderTexture2D target);                                                 // Check if a render texture is valid (loaded in GPU)
//     RLAPI void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory (VRAM)
//     RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data (pixels should be able to fill texture)
//     RLAPI void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data (pixels and rec should fit in texture)
//
//     // Texture configuration functions
//     RLAPI void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
//     RLAPI void SetTextureFilter(Texture2D texture, int filter);                                              // Set texture scaling filter mode
//     RLAPI void SetTextureWrap(Texture2D texture, int wrap);                                                  // Set texture wrapping mode
//
//     // Texture drawing functions
//     RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
//     RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
//     RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
//     RLAPI void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);            // Draw a part of a texture defined by a rectangle
//     RLAPI void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draw a part of a texture defined by a rectangle with 'pro' parameters
//     RLAPI void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draw a texture (or part of it) that stretches or shrinks nicely
//
//     // Color/pixel related functions
//     RLAPI bool ColorIsEqual(Color col1, Color col2);                            // Check if two colors are equal
//     RLAPI Color Fade(Color color, float alpha);                                 // Get color with alpha applied, alpha goes from 0.0f to 1.0f
//     RLAPI int ColorToInt(Color color);                                          // Get hexadecimal value for a Color (0xRRGGBBAA)
//     RLAPI Vector4 ColorNormalize(Color color);                                  // Get Color normalized as float [0..1]
//     RLAPI Color ColorFromNormalized(Vector4 normalized);                        // Get Color from normalized values [0..1]
//     RLAPI Vector3 ColorToHSV(Color color);                                      // Get HSV values for a Color, hue [0..360], saturation/value [0..1]
//     RLAPI Color ColorFromHSV(float hue, float saturation, float value);         // Get a Color from HSV values, hue [0..360], saturation/value [0..1]
//     RLAPI Color ColorTint(Color color, Color tint);                             // Get color multiplied with another color
//     RLAPI Color ColorBrightness(Color color, float factor);                     // Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
//     RLAPI Color ColorContrast(Color color, float contrast);                     // Get color with contrast correction, contrast values between -1.0f and 1.0f
//     RLAPI Color ColorAlpha(Color color, float alpha);                           // Get color with alpha applied, alpha goes from 0.0f to 1.0f
//     RLAPI Color ColorAlphaBlend(Color dst, Color src, Color tint);              // Get src alpha-blended into dst color with tint
//     RLAPI Color ColorLerp(Color color1, Color color2, float factor);            // Get color lerp interpolation between two colors, factor [0.0f..1.0f]
//     RLAPI Color GetColor(unsigned int hexValue);                                // Get Color structure from hexadecimal value
//     RLAPI Color GetPixelColor(void *srcPtr, int format);                        // Get Color from a source pixel pointer of certain format
//     RLAPI void SetPixelColor(void *dstPtr, Color color, int format);            // Set color formatted into destination pixel pointer
//     RLAPI int GetPixelDataSize(int width, int height, int format);              // Get pixel data size in bytes for certain format
//
//     //------------------------------------------------------------------------------------
//     // Font Loading and Text Drawing Functions (Module: text)
//     //------------------------------------------------------------------------------------
//
//     // Font loading/unloading functions
//     RLAPI Font GetFontDefault(void);                                                            // Get the default Font
//     RLAPI Font LoadFont(const char *fileName);                                                  // Load font from file into GPU memory (VRAM)
//     RLAPI Font LoadFontEx(const char *fileName, int fontSize, const int *codepoints, int codepointCount); // Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set, font size is provided in pixels height
//     RLAPI Font LoadFontFromImage(Image image, Color key, int firstChar);                        // Load font from Image (XNA style)
//     RLAPI Font LoadFontFromMemory(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, const int *codepoints, int codepointCount); // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
//     RLAPI bool IsFontValid(Font font);                                                          // Check if a font is valid (font data loaded, WARNING: GPU texture not checked)
//     RLAPI GlyphInfo *LoadFontData(const unsigned char *fileData, int dataSize, int fontSize, const int *codepoints, int codepointCount, int type, int *glyphCount); // Load font data for further use
//     RLAPI Image GenImageFontAtlas(const GlyphInfo *glyphs, Rectangle **glyphRecs, int glyphCount, int fontSize, int padding, int packMethod); // Generate image font atlas using chars info
//     RLAPI void UnloadFontData(GlyphInfo *glyphs, int glyphCount);                               // Unload font chars info data (RAM)
//     RLAPI void UnloadFont(Font font);                                                           // Unload font from GPU memory (VRAM)
//     RLAPI bool ExportFontAsCode(Font font, const char *fileName);                               // Export font as code file, returns true on success
//
//     // Text drawing functions
//     RLAPI void DrawFPS(int posX, int posY);                                                     // Draw current FPS
//     RLAPI void DrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
//     RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
//     RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
//     RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
//     RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple characters (codepoint)
//
//     // Text font info functions
//     RLAPI void SetTextLineSpacing(int spacing);                                                 // Set vertical line spacing when drawing with line-breaks
//     RLAPI int MeasureText(const char *text, int fontSize);                                      // Measure string width for default font
//     RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);    // Measure string size for Font
//     RLAPI Vector2 MeasureTextCodepoints(Font font, const int *codepoints, int length, float fontSize, float spacing); // Measure string size for an existing array of codepoints for Font
//     RLAPI int GetGlyphIndex(Font font, int codepoint);                                          // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
//     RLAPI GlyphInfo GetGlyphInfo(Font font, int codepoint);                                     // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
//     RLAPI Rectangle GetGlyphAtlasRec(Font font, int codepoint);                                 // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

} // ElfResource
