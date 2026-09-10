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
#include "raymath.h"

namespace ElfText {
    using namespace ElfResource;

    //------------------------------------------------------------------------------------
    // Font Loading and Text Drawing Functions (Module: text)
    //------------------------------------------------------------------------------------
    // Font loading/unloading functions
    //------------------------------------------------------------------------------------
    // RLAPI Font GetFontDefault(void);                                                            // Get the default Font
    DefineEngineFunction( GetFontDefault, S32, (), , "Get the default Raylib Font and return the FontID") {
        return 0; // when get is calles it use the default font on 0
    }

    // RLAPI Font LoadFont(const char *fileName);                                                  // Load font from file into GPU memory (VRAM)
    DefineEngineFunction( LoadFont, S32, (String fileName), , "Load font from file into GPU memory (VRAM) and return the FontID") {
        Font font = LoadFont(fileName.c_str());
        if (!IsFontValid(font)) return 0;
        return FontMap.add(font);
    }

    // RLAPI Font LoadFontEx(const char *fileName, int fontSize, const int *codepoints, int codepointCount); // Load font from file with extended parameters
    DefineEngineFunction( LoadFontEx, S32, (String fileName, int fontSize, Vector<S32> codepointValues, int codepointCount), , "Load font from file with extended parameters. Pass 0 for codepointCount to use default set.") {

        Font font;
        bool valuesEmpty = codepointValues.size() == 1 && codepointValues[0] == 0;
        if ( valuesEmpty && codepointCount > 0) {
             font = LoadFontEx(fileName.c_str(), fontSize, nullptr, codepointCount);
        } else  if (codepointCount <= 0 || valuesEmpty) {
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
    , float fontSize, float spacing, Color tint, bool doShadow, Color shadowColor )
    , (20.f ,1.f, RAYWHITE, false, DARKGRAY), "Draw text using font and additional parameters, fontId 0 means default font")
    {
        Font* font = ElfResource::FontMap.get(fontId);
        if (!font) return;
        if (doShadow) DrawTextEx(*font,text, position + Vector2(1.f, 1.f), fontSize, spacing, shadowColor);
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
    // not really usable ... use strFormat also if it's only one parameter
    // ConsoleFunction( TextFormat, const char *, 3, 0, "Text formatting with variables (sprintf() style)")
    // {
    //     // argc is the argument count
    //     // argv[1] is text
    //     // argv[2..n] are the parameters
    //     // *TextFormat(const char *text, ...);
    // }

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



} // ElfText
