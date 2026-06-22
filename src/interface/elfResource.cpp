//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------

#include "elfResource.h"
#include <console/console.h>
#include "console/engineAPI.h"
#include "ConsoleTypes.h"

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
    // RLAPI Texture2D LoadTexture(const char *fileName);                                     // Load texture from file into GPU memory (VRAM)
    DefineEngineFunction( LoadTexture, S32, (String fileName), , "Load texture from file into GPU memory (VRAM) and return the TextureID") {
        Texture2D tex = LoadTexture(fileName.c_str());
        if (!IsTextureValid(tex)) return 0;
        return TextureMap.add(tex);
    }

    // RLAPI void UnloadTexture(Texture2D texture);                                           // Unload texture from GPU memory (VRAM)
    DefineEngineFunction( UnloadTexture, void, (S32 textureId), , "Unload texture from GPU memory (VRAM)") {
        TextureMap.remove(textureId);
    }

    // RLAPI Texture2D LoadTextureFromImage(Image image);                                     // Load texture from image data
    DefineEngineFunction( LoadTextureFromImage, S32, (S32 imageId), , "Load texture from image data and return the TextureID") {
        Image* img = ImageMap.get(imageId);
        if (!img) return 0;

        Texture2D tex = LoadTextureFromImage(*img);
        if (!IsTextureValid(tex)) return 0;
        return TextureMap.add(tex);
    }

    // RLAPI TextureCubemap LoadTextureCubemap(Image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
    // Hinweis: TextureCubemap ist in Raylib technisch identisch mit Texture2D
    DefineEngineFunction( LoadTextureCubemap, S32, (S32 imageId, int layout), , "Load cubemap from image, multiple image cubemap layouts supported") {
        Image* img = ImageMap.get(imageId);
        if (!img || !IsImageValid(*img)) return 0;

        TextureCubemap cube = LoadTextureCubemap(*img, layout);
        if (!IsTextureValid(cube)) return 0;
        return TextureMap.add(cube);
    }

    // NOTE:: use RenderTextureObject
    // RLAPI RenderTexture2D LoadRenderTexture(int width, int height);                                          // Load texture for rendering (framebuffer)
    // DefineEngineFunction( LoadRenderTexture, S32, (int width, int height), , "Load texture for rendering (framebuffer) and return RenderTextureID") {
    //     RenderTexture2D target = LoadRenderTexture(width, height);
    //     if (!IsRenderTextureValid(target)) return 0;
    //     return RenderTextureMap.add(target);
    // }

    // RLAPI bool IsTextureValid(Texture2D texture);                                                            // Check if a texture is valid (loaded in GPU)
    DefineEngineFunction( IsTextureValid, bool, (S32 textureId), , "Check if a texture is valid (loaded in GPU)") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return false;
        return IsTextureValid(*tex);
    }

    // NOTE:: use RenderTextureObject
    // RLAPI bool IsRenderTextureValid(RenderTexture2D target);                                                 // Check if a render texture is valid (loaded in GPU)
    // DefineEngineFunction( IsRenderTextureValid, bool, (S32 renderTextureId), , "Check if a render texture is valid (loaded in GPU)") {
    //     RenderTexture2D* target = RenderTextureMap.get(renderTextureId);
    //     if (!target) return false;
    //     return IsRenderTextureValid(*target);
    // }
    //
    // // RLAPI void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory (VRAM)
    // DefineEngineFunction( UnloadRenderTexture, void, (S32 renderTextureId), , "Unload render texture from GPU memory (VRAM)") {
    //     RenderTextureMap.remove(renderTextureId);
    // }

    // RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data
    DefineEngineFunction( UpdateTexture, void, (S32 textureId, S32 imageId), , "Update GPU texture with data from an Image ID") {
        Texture2D* tex = TextureMap.get(textureId);
        Image* img = ImageMap.get(imageId);

        if (!tex || !img || img->data == nullptr) return;

        UpdateTexture(*tex, img->data);
    }

    // RLAPI void UpdateTextureRec(Texture2D texture, Rectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data
    DefineEngineFunction( UpdateTextureRec, void, (S32 textureId, Rectangle rec, S32 imageId), , "Update GPU texture rectangle with data from an Image ID") {
        Texture2D* tex = TextureMap.get(textureId);
        Image* img = ImageMap.get(imageId);

        if (!tex || !img || img->data == nullptr) return;

        UpdateTextureRec(*tex, rec, img->data);
    }

    // -----------------------------------------------------------------------------------
    // Texture configuration functions
    // -----------------------------------------------------------------------------------
    // RLAPI void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
    DefineEngineFunction( GenTextureMipmaps, void, (S32 textureId), , "Generate GPU mipmaps for a texture") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;
        GenTextureMipmaps(tex);
    }

    // RLAPI void SetTextureFilter(Texture2D texture, int filter);                                              // Set texture scaling filter mode
    DefineEngineFunction( SetTextureFilter, void, (S32 textureId, int filter), , "Set texture scaling filter mode (e.g., TEXTURE_FILTER_POINT, TEXTURE_FILTER_BILINEAR)") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;
        SetTextureFilter(*tex, filter);
    }

    // RLAPI void SetTextureWrap(Texture2D texture, int wrap);                                                  // Set texture wrapping mode
    DefineEngineFunction( SetTextureWrap, void, (S32 textureId, int wrap), , "Set texture wrapping mode (e.g., TEXTURE_WRAP_REPEAT, TEXTURE_WRAP_CLAMP)") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;

        SetTextureWrap(*tex, wrap);
    }

    // -----------------------------------------------------------------------------------
    // Texture drawing functions
    // -----------------------------------------------------------------------------------
    // RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);           // Draw a Texture2D
    DefineEngineFunction( DrawTexture, void, (S32 textureId, int posX, int posY, Color tint), (WHITE), "Draw a Texture2D using its TextureID") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;

        DrawTexture(*tex, posX, posY, tint);
    }
    // RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
    DefineEngineFunction( DrawTextureV, void, (S32 textureId, Vector2 position, Color tint), (WHITE), "Draw a Texture2D with position defined as Vector2") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;

        DrawTextureV(*tex, position, tint);
    }

    // RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
    DefineEngineFunction( DrawTextureEx, void, (S32 textureId, Vector2 position, float rotation, float scale, Color tint), (WHITE), "Draw a Texture2D with extended parameters (rotation, scale, tint)") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;

        DrawTextureEx(*tex, position, rotation, scale, tint);
    }

    // RLAPI void DrawTextureRec(Texture2D texture, Rectangle source, Vector2 position, Color tint);            // Draw a part of a texture defined by a rectangle
    DefineEngineFunction( DrawTextureRec, void, (S32 textureId, Rectangle source, Vector2 position, Color tint), (WHITE), "Draw a part of a texture defined by a rectangle") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;

        DrawTextureRec(*tex, source, position, tint);
    }

    // RLAPI void DrawTexturePro(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint); // Draw a part of a texture defined by a rectangle with 'pro' parameters
    DefineEngineFunction( DrawTexturePro, void, (S32 textureId, Rectangle source, Rectangle dest, Vector2 origin, float rotation, Color tint), (WHITE), "Draw a part of a texture defined by a rectangle with 'pro' parameters") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;

        DrawTexturePro(*tex, source, dest, origin, rotation, tint);
    }

    // RLAPI void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, Rectangle dest, Vector2 origin, float rotation, Color tint);
    DefineEngineFunction( DrawTextureNPatch, void,
                          (S32 textureId, Rectangle sourceRec, int left, int top, int right, int bottom, int layout, Rectangle destRec, Vector2 origin, float rotation, Color tint),
                          (WHITE),
                          "Draws a texture using 9-patch / N-patch scaling to prevent UI distortion.")
    {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) return;

        NPatchInfo nPatchInfo;
        nPatchInfo.source = sourceRec;
        nPatchInfo.left = left;
        nPatchInfo.top = top;
        nPatchInfo.right = right;
        nPatchInfo.bottom = bottom;
        nPatchInfo.layout = layout;

        DrawTextureNPatch(*tex, nPatchInfo, destRec, origin, rotation, tint);
    }

    // -----------------------------------------------------------------------------------
    // Color/pixel related functions
    // -----------------------------------------------------------------------------------
    // RLAPI bool ColorIsEqual(Color col1, Color col2);                            // Check if two colors are equal
    DefineEngineFunction( ColorIsEqual, bool, (Color col1, Color col2), , "Check if two colors are equal") {
        return ColorIsEqual(col1, col2);
    }

    // RLAPI Color Fade(Color color, float alpha);                                 // Get color with alpha applied, alpha goes from 0.0f to 1.0f
    DefineEngineFunction( Fade, Color, (Color color, float alpha), , "Get color with alpha applied, alpha goes from 0.0f to 1.0f") {
        return Fade(color, alpha);
    }

    // RLAPI int ColorToInt(Color color);                                          // Get hexadecimal value for a Color (0xRRGGBBAA)
    DefineEngineFunction( ColorToInt, int, (Color color), , "Get hexadecimal value for a Color (0xRRGGBBAA)") {
        return ColorToInt(color);
    }

    // RLAPI Vector4 ColorNormalize(Color color);                                  // Get Color normalized as float [0..1]
    DefineEngineFunction( ColorNormalize, Vector4, (Color color), , "Get Color normalized as float [0..1]") {
        return ColorNormalize(color);
    }

    // RLAPI Color ColorFromNormalized(Vector4 normalized);                        // Get Color from normalized values [0..1]
    DefineEngineFunction( ColorFromNormalized, Color, (Vector4 normalized), , "Get Color from normalized values [0..1]") {
        return ColorFromNormalized(normalized);
    }

    // RLAPI Vector3 ColorToHSV(Color color);                                      // Get HSV values for a Color, hue [0..360], saturation/value [0..1]
    DefineEngineFunction( ColorToHSV, Vector3, (Color color), , "Get HSV values for a Color, hue [0..360], saturation/value [0..1]") {
        return ColorToHSV(color);
    }

    // RLAPI Color ColorFromHSV(float hue, float saturation, float value);         // Get a Color from HSV values, hue [0..360], saturation/value [0..1]
    DefineEngineFunction( ColorFromHSV, Color, (float hue, float saturation, float value), , "Get a Color from HSV values, hue [0..360], saturation/value [0..1]") {
        return ColorFromHSV(hue, saturation, value);
    }

    // RLAPI Color ColorTint(Color color, Color tint);                             // Get color multiplied with another color
    DefineEngineFunction( ColorTint, Color, (Color color, Color tint), , "Get color multiplied with another color") {
        return ColorTint(color, tint);
    }

    // RLAPI Color ColorBrightness(Color color, float factor);                     // Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
    DefineEngineFunction( ColorBrightness, Color, (Color color, float factor), , "Get color with brightness correction, brightness factor goes from -1.0f to 1.0f") {
        return ColorBrightness(color, factor);
    }

    // RLAPI Color ColorContrast(Color color, float contrast);                     // Get color with contrast correction, contrast values between -1.0f and 1.0f
    DefineEngineFunction( ColorContrast, Color, (Color color, float contrast), , "Get color with contrast correction, contrast values between -1.0f and 1.0f") {
        return ColorContrast(color, contrast);
    }

    // RLAPI Color ColorAlpha(Color color, float alpha);                           // Get color with alpha applied, alpha goes from 0.0f to 1.0f
    DefineEngineFunction( ColorAlpha, Color, (Color color, float alpha), , "Get color with alpha applied, alpha goes from 0.0f to 1.0f") {
        return ColorAlpha(color, alpha);
    }

    // RLAPI Color ColorAlphaBlend(Color dst, Color src, Color tint);              // Get src alpha-blended into dst color with tint
    DefineEngineFunction( ColorAlphaBlend, Color, (Color dst, Color src, Color tint), , "Get src alpha-blended into dst color with tint") {
        return ColorAlphaBlend(dst, src, tint);
    }

    // RLAPI Color ColorLerp(Color color1, Color color2, float factor);            // Get color lerp interpolation between two colors, factor [0.0f..1.0f]
    DefineEngineFunction( ColorLerp, Color, (Color color1, Color color2, float factor), , "Get color lerp interpolation between two colors, factor [0.0f..1.0f]") {
        return ColorLerp(color1, color2, factor);
    }

    // RLAPI Color GetColor(unsigned int hexValue);                                // Get Color structure from hexadecimal value
    DefineEngineFunction( GetColor, Color, (int hexValue), , "Get Color structure from hexadecimal value (e.g. 0xFF0000FF)") {
        return GetColor((unsigned int)hexValue);
    }

    // RLAPI int GetPixelDataSize(int width, int height, int format);              // Get pixel data size in bytes for certain format
    DefineEngineFunction( GetPixelDataSize, int, (int width, int height, int format), , "Get pixel data size in bytes for certain format") {
        return GetPixelDataSize(width, height, format);
    }

//     RLAPI Color GetPixelColor(void *srcPtr, int format);                        // Get Color from a source pixel pointer of certain format
//     RLAPI void SetPixelColor(void *dstPtr, Color color, int format);            // Set color formatted into destination pixel pointer


    //------------------------------------------------------------------------------------
    // Font Loading and Text Drawing Functions (Module: text)
    //------------------------------------------------------------------------------------
    // Font loading/unloading functions
    //------------------------------------------------------------------------------------
    // RLAPI Font GetFontDefault(void);                                                            // Get the default Font
    // DefineEngineFunction( GetFontDefault, S32, (), , "Get the default Raylib Font and return the FontID") {
    //     Font font = GetFontDefault();
    //     return FontMap.add(font);
    // }

    // RLAPI Font LoadFont(const char *fileName);                                                  // Load font from file into GPU memory (VRAM)
    DefineEngineFunction( LoadFont, S32, (String fileName), , "Load font from file into GPU memory (VRAM) and return the FontID") {
        Font font = LoadFont(fileName.c_str());
        if (!IsFontValid(font)) return 0;
        return FontMap.add(font);
    }

    // RLAPI Font LoadFontEx(const char *fileName, int fontSize, const int *codepoints, int codepointCount); // Load font from file with extended parameters
    DefineEngineFunction( LoadFontEx, S32, (String fileName, int fontSize, Vector<S32> codepointValues, int codepointCount), , "Load font from file with extended parameters. Pass 0 for codepointCount to use default set.") {

        Font font;

        if (codepointCount <= 0 || codepointValues.size() == 0) {
            font = LoadFontEx(fileName.c_str(), fontSize, nullptr, 0);
        } else {
            if (codepointValues.size() < (size_t)codepointCount) {
                Con::errorf("LoadFontEx: Codepoint count (%d) mismatch with Vector size (%d)", codepointCount, codepointValues.size());
                return 0;
            }

            std::vector<int> points;
            for (int i = 0; i < codepointCount; i++) {
                points.push_back(codepointValues[i]);
            }

            font = LoadFontEx(fileName.c_str(), fontSize, points.data(), codepointCount);
        }

        if (!IsFontValid(font)) return 0;
        return FontMap.add(font);
    }

    // RLAPI Font LoadFontFromImage(Image image, Color key, int firstChar);                        // Load font from Image (XNA style)
    DefineEngineFunction( LoadFontFromImage, S32, (S32 imageId, Color key, int firstChar), , "Load font from Image data and return the FontID") {
        Image* img = ImageMap.get(imageId);
        if (!img || img->data == nullptr) return 0;

        Font font = LoadFontFromImage(*img, key, firstChar);
        if (!IsFontValid(font)) return 0;
        return FontMap.add(font);
    }

//     RLAPI Font LoadFontFromMemory(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, const int *codepoints, int codepointCount); // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
//     RLAPI bool IsFontValid(Font font);                                                          // Check if a font is valid (font data loaded, WARNING: GPU texture not checked)
//     RLAPI GlyphInfo *LoadFontData(const unsigned char *fileData, int dataSize, int fontSize, const int *codepoints, int codepointCount, int type, int *glyphCount); // Load font data for further use
//     RLAPI Image GenImageFontAtlas(const GlyphInfo *glyphs, Rectangle **glyphRecs, int glyphCount, int fontSize, int padding, int packMethod); // Generate image font atlas using chars info
//     RLAPI void UnloadFontData(GlyphInfo *glyphs, int glyphCount);                               // Unload font chars info data (RAM)


    // RLAPI void UnloadFont(Font font);                                                           // Unload font from GPU memory (VRAM)
    DefineEngineFunction( UnloadFont, void, (S32 fontId), , "Unload font from GPU memory (VRAM)") {
        FontMap.remove(fontId);
    }

    // RLAPI bool ExportFontAsCode(Font font, const char *fileName);                               // Export font as code file, returns true on success
    DefineEngineFunction( ExportFontAsCode, bool, (S32 fontId, String fileName),
        , "Export font data as a C code file (.h), returns true on success") {
        Font* font = FontMap.get(fontId);
        if (!font) return false;

        return ExportFontAsCode(*font, fileName.c_str());
    }


    // -----------------------------------------------------------------------------
    // Text drawing functions
    // -----------------------------------------------------------------------------
    // RLAPI void DrawFPS(int posX, int posY);
    DefineEngineFunction( DrawFPS, void, (int posX, int posY), , "Draw current FPS") {
        DrawFPS(posX, posY);
    }

    DefineEngineFunction( DrawText, void, (const char *text, int posX, int posY
    , int fontSize, Color color, bool doShadow, Color shadowColor),
        (20 , RAYWHITE, false, DARKGRAY), "Draw text (using default font") {
        if (doShadow) DrawText(text,posX+1.f, posY+1.f, fontSize, shadowColor);
        DrawText(text,posX, posY, fontSize, color);
    }


    // RLAPI void DrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
    DefineEngineFunction( DrawTextEx, void, (S32 fontId, const char *text, Vector2 position
    , float fontSize, float spacing, Color tint)
    , (RAYWHITE), "Draw text using font and additional parameters, fontId 0 means default font")
    {
        Font* font = ElfResource::FontMap.get(fontId);
        if (!font) return;
        DrawTextEx(*font, text, position, fontSize, spacing, tint);
    }

    // RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
    DefineEngineFunction( DrawTextPro, void, (S32 fontId, const char *text, Vector2 position,
                                            Vector2 origin, float rotation, float fontSize, float spacing, Color tint), (RAYWHITE),
                        "Draw text using Font and pro parameters (rotation)")
    {

        Font* font = ElfResource::FontMap.get(fontId);
        if (!font) return;
        DrawTextPro(*font, text, position, origin, rotation, fontSize, spacing, tint);
    }
    // RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
    DefineEngineFunction(DrawTextCodepoint, void, (S32 fontId,S32 codepoint, Vector2 position,
                                                float fontSize,  Color tint), (RAYWHITE),
                        " Draw one character (codepoint)")
    {
        Font* font = ElfResource::FontMap.get(fontId);
        if (!font) return;
        DrawTextCodepoint(*font, codepoint, position, fontSize, tint);
    }

    // RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple characters (codepoint)
    DefineEngineFunction(DrawTextCodepoints, void, (S32 fontId,Vector<S32> codepoints, S32 codepointCount,
                                                    Vector2 position,  F32 fontSize, F32 spacing, Color tint), (RAYWHITE),
                        " Draw one character (codepoint)")
    {
        Font* font = ElfResource::FontMap.get(fontId);
        if (!font) return;

        if (codepoints.size() < codepointCount) {
            Con::errorf("Codepoint count (%d) missmatch Count of codepoints (%d)", codepointCount, codepoints.size());
        }
        // i do a copy ...maybe i could use mArray from Vector but ...
        std::vector<S32> points;
        for (S32 i = 0; i < codepointCount; i++) {
            points.push_back(codepoints[i]);
        }
        DrawTextCodepoints(*font, points.data(),codepointCount, position, fontSize, spacing, tint);
    }


    // -----------------------------------------------------------------------------
    // Text font info functions
    // -----------------------------------------------------------------------------


    // RLAPI void SetTextLineSpacing(int spacing);                                                 // Set vertical line spacing when drawing with line-breaks
    DefineEngineFunction( SetTextLineSpacing, void, (int spacing), , "Set vertical line spacing when drawing with line-breaks") {
        SetTextLineSpacing(spacing);
    }

    // RLAPI int MeasureText(const char *text, int fontSize);                                      // Measure string width for default font
    DefineEngineFunction( MeasureText, int, (String text, int fontSize), , "Measure string width in pixels for the default font") {
        return MeasureText(text.c_str(), fontSize);
    }

    // RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);    // Measure string size for Font
    DefineEngineFunction( MeasureTextEx, Vector2, (S32 fontId, String text, float fontSize, float spacing), , "Measure string width and height as Vector2 for a specific Font") {
        Font* font = FontMap.get(fontId);
        if (!font) return Vector2{0.0f, 0.0f};

        return MeasureTextEx(*font, text.c_str(), fontSize, spacing);
    }

    // RLAPI Vector2 MeasureTextCodepoints(Font font, const int *codepoints, int length, float fontSize, float spacing); // Measure string size for an existing array of codepoints for Font
    DefineEngineFunction( MeasureTextCodepoints, Vector2, (S32 fontId, Vector<S32> codepointValues, int length, float fontSize, float spacing), , "Measure string size for an array of codepoints") {
        Font* font = FontMap.get(fontId);
        if (!font) return Vector2{0.0f, 0.0f};

        if (codepointValues.size() < (size_t)length) {
            Con::errorf("MeasureTextCodepoints: Length (%d) mismatch with Vector size (%d)", length, codepointValues.size());
            return Vector2{0.0f, 0.0f};
        }

        std::vector<int> points;
        for (int i = 0; i < length; i++) {
            points.push_back(codepointValues[i]);
        }

        return MeasureTextCodepoints(*font, points.data(), length, fontSize, spacing);
    }

    // RLAPI int GetGlyphIndex(Font font, int codepoint);                                          // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
    DefineEngineFunction( GetGlyphIndex, int, (S32 fontId, int codepoint), , "Get glyph index position in font for a codepoint") {
        Font* font = FontMap.get(fontId);
        if (!font) return -1;

        return GetGlyphIndex(*font, codepoint);
    }

    // RLAPI Rectangle GetGlyphAtlasRec(Font font, int codepoint);                                 // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found
    DefineEngineFunction( GetGlyphAtlasRec, Rectangle, (S32 fontId, int codepoint), , "Get glyph rectangle in font atlas for a codepoint") {
        Font* font = FontMap.get(fontId);
        if (!font) {
            // Falls die Schriftart komplett ungültig ist, geben wir ein leeres Rechteck zurück
            Rectangle empty = { 0.0f, 0.0f, 0.0f, 0.0f };
            return empty;
        }

        return GetGlyphAtlasRec(*font, codepoint);
    }

    // RLAPI GlyphInfo GetGlyphInfo(Font font, int codepoint);                                     // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
    DefineEngineFunction( GetGlyphInfo, String, (S32 fontId, int codepoint),
                          , "Get glyph info (offsetX, offsetY, advanceX) for a codepoint") {
        Font* font = FontMap.get(fontId);
        if (!font) return "";

        // Raylib-Funktion aufrufen, um den Index des Zeichens zu finden
        int glyphIndex = GetGlyphIndex(*font, codepoint);
        if (glyphIndex < 0) return "";

        GlyphInfo glyph = font->glyphs[glyphIndex];

        char* ret = Con::getReturnBuffer(128);
        dSprintf(ret, 128, "%d %d %d", glyph.offsetX, glyph.offsetY, glyph.advanceX);
        return ret;
    }

} // ElfResource
