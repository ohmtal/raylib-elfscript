//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//-----------------------------------------------------------------------------

#include "elfResource.h"
#include <console/console.h>
#include "console/engineAPI.h"
#include "ConsoleTypes.h"

namespace ElfText {
    using namespace ElfResource;

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

} // ElfText
