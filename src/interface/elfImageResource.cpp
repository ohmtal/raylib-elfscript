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
#include <core/strings/stringUnit.h>
#include <vector>

namespace ElfResource {

    // ------------------------------------------------------------------------
    // Image loading functions
    // ------------------------------------------------------------------------
    DefineEngineFunction(LoadImage, S32, (String fileName), ,
                         "Load image from file into CPU memory (RAM) and return the ImageID") {

        Image img = LoadImage(fileName.c_str());
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    DefineEngineFunction(UnloadImage, void, (S32 imageId), ,
                         "Unload image from CPU memory (RAM)") {

        ImageMap.remove( imageId);
    }


    // RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);
    DefineEngineFunction(LoadImageRaw, S32, (String fileName, S32 width, S32 height, S32 format, S32 headerSize), ,
                         "Load image from RAW file data") {
        Image img = LoadImageRaw(fileName.c_str(), width, height, format, headerSize);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    DefineEngineFunction(LoadImageAnim, S32, (String fileName), ,
                         "Load image sequence from file. Outputs frames to console.") {
        int frames = 0;
        Image img = LoadImageAnim(fileName.c_str(), &frames);
        if (!IsImageValid(img)) return 0;

        Con::printf("LoadImageAnim: %s geladen mit %d Frames.", fileName.c_str(), frames);
        return ImageMap.add(img);
    }


    DefineEngineFunction(LoadImageFromTexture, S32, (S32 textureId), ,
                         "Load image from GPU texture data") {
        Texture2D* tex = TextureMap.get(textureId);
        if (!tex) {
            Con::errorf("LoadImageFromTexture: Ungültige Texture-ID %d", textureId);
            return 0;
        }

        Image img = LoadImageFromTexture(*tex);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image LoadImageFromScreen(void);
    DefineEngineFunction(LoadImageFromScreen, S32, (), ,
                         "Load image from screen buffer (screenshot)") {
        Image img = LoadImageFromScreen();
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI bool IsImageValid(Image image);
    DefineEngineFunction(IsImageValid, bool, (S32 imageId), ,
                         "Check if an image is valid") {
        Image* img = ImageMap.get(imageId);
        if (!img) return false;
        return IsImageValid(*img);
    }

    // RLAPI bool ExportImage(Image image, const char *fileName);
    DefineEngineFunction(ExportImage, bool, (S32 imageId, String fileName), ,
                         "Export image data to file, returns true on success") {
        Image* img = ImageMap.get(imageId);
        if (!img) return false;
        return ExportImage(*img, fileName.c_str());
    }

    // RLAPI bool ExportImageAsCode(Image image, const char *fileName);
    DefineEngineFunction(ExportImageAsCode, bool, (S32 imageId, String fileName), ,
                         "Export image as code file defining an array of bytes, returns true on success") {
        Image* img = ImageMap.get(imageId);
        if (!img) return false;
        return ExportImageAsCode(*img, fileName.c_str());
    }

    // ------------------------------------------------------------------------
    // Image loading functions
    // ------------------------------------------------------------------------
    // RLAPI Image GenImageColor(int width, int height, Color color);
    DefineEngineFunction(GenImageColor, S32, (S32 width, S32 height, Color color), ,
                        "Generate image: plain color") {
        Image img = GenImageColor(width, height, color);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image GenImageGradientLinear(int width, int height, int direction, Color start, Color end);
    DefineEngineFunction(GenImageGradientLinear, S32, (S32 width, S32 height, S32 direction, Color start, Color end), ,
                        "Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient") {
        Image img = GenImageGradientLinear(width, height, direction, start, end);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);
    DefineEngineFunction(GenImageGradientRadial, S32, (S32 width, S32 height, F32 density, Color inner, Color outer), ,
                        "Generate image: radial gradient") {
        Image img = GenImageGradientRadial(width, height, density, inner, outer);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image GenImageGradientSquare(int width, int height, float density, Color inner, Color outer);
    DefineEngineFunction(GenImageGradientSquare, S32, (S32 width, S32 height, F32 density, Color inner, Color outer), ,
                        "Generate image: square gradient") {
        Image img = GenImageGradientSquare(width, height, density, inner, outer);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);
    DefineEngineFunction(GenImageChecked, S32, (S32 width, S32 height, S32 checksX, S32 checksY, Color col1, Color col2), ,
                        "Generate image: checked") {
        Image img = GenImageChecked(width, height, checksX, checksY, col1, col2);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image GenImageWhiteNoise(int width, int height, float factor);
    DefineEngineFunction(GenImageWhiteNoise, S32, (S32 width, S32 height, F32 factor), ,
                        "Generate image: white noise") {
        Image img = GenImageWhiteNoise(width, height, factor);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);
    DefineEngineFunction(GenImagePerlinNoise, S32, (S32 width, S32 height, S32 offsetX, S32 offsetY, F32 scale), ,
                        "Generate image: perlin noise") {
        Image img = GenImagePerlinNoise(width, height, offsetX, offsetY, scale);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image GenImageCellular(int width, int height, int tileSize);
    DefineEngineFunction(GenImageCellular, S32, (S32 width, S32 height, S32 tileSize), ,
                        "Generate image: cellular algorithm, bigger tileSize means bigger cells") {
        Image img = GenImageCellular(width, height, tileSize);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image GenImageText(int width, int height, const char *text);
    DefineEngineFunction(GenImageText, S32, (S32 width, S32 height, String text), ,
                        "Generate image: grayscale image from text data") {
        Image img = GenImageText(width, height, text.c_str());
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }
    // ------------------------------------------------------------------------
    // Image manipulation functions
    // ------------------------------------------------------------------------
    // RLAPI Image ImageCopy(Image image);
    DefineEngineFunction(ImageCopy, S32, (S32 imageId), ,
                        "Create an image duplicate") {
        Image* img = ImageMap.get(imageId);
        if (!img) return 0;
        Image newImg = ImageCopy(*img);
        if (!IsImageValid(newImg)) return 0;
        return ImageMap.add(newImg);
    }

    // RLAPI Image ImageFromImage(Image image, Rectangle rec);
    DefineEngineFunction(ImageFromImage, S32, (S32 imageId, Rectangle rec), ,
                        "Create an image from another image piece") {
        Image* img = ImageMap.get(imageId);
        if (!img) return 0;
        Image newImg = ImageFromImage(*img, rec);
        if (!IsImageValid(newImg)) return 0;
        return ImageMap.add(newImg);
    }

    // RLAPI Image ImageFromChannel(Image image, int selectedChannel);
    DefineEngineFunction(ImageFromChannel, S32, (S32 imageId, S32 selectedChannel), ,
                        "Create an image from a selected channel of another image (GRAYSCALE)") {
        Image* img = ImageMap.get(imageId);
        if (!img) return 0;
        Image newImg = ImageFromChannel(*img, selectedChannel);
        if (!IsImageValid(newImg)) return 0;
        return ImageMap.add(newImg);
    }

    // RLAPI Image ImageText(const char *text, int fontSize, Color color);
    DefineEngineFunction(ImageText, S32, (String text, S32 fontSize, Color color), ,
                        "Create an image from text (default font)") {
        Image img = ImageText(text.c_str(), fontSize, color);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint);
    DefineEngineFunction(ImageTextEx, S32, (S32 fontId, String text, F32 fontSize, F32 spacing, Color tint), ,
                        "Create an image from text (custom sprite font)") {
        Font* font = FontMap.get(fontId);
        if (!font) return 0;
        Image img = ImageTextEx(*font, text.c_str(), fontSize, spacing, tint);
        if (!IsImageValid(img)) return 0;
        return ImageMap.add(img);
    }

    // RLAPI void ImageFormat(Image *image, int newFormat);
    DefineEngineFunction(ImageFormat, void, (S32 imageId, S32 newFormat), ,
                        "Convert image data to desired format") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageFormat(img, newFormat);
    }

    // RLAPI void ImageToPOT(Image *image, Color fill);
    DefineEngineFunction(ImageToPOT, void, (S32 imageId, Color fill), ,
                        "Convert image to POT (power-of-two)") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageToPOT(img, fill);
    }

    // RLAPI void ImageCrop(Image *image, Rectangle crop);
    DefineEngineFunction(ImageCrop, void, (S32 imageId, Rectangle crop), ,
                        "Crop an image to a defined rectangle") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageCrop(img, crop);
    }

    // RLAPI void ImageAlphaCrop(Image *image, float threshold);
    DefineEngineFunction(ImageAlphaCrop, void, (S32 imageId, F32 threshold), ,
                        "Crop image depending on alpha value") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageAlphaCrop(img, threshold);
    }

    // RLAPI void ImageAlphaClear(Image *image, Color color, float threshold);
    DefineEngineFunction(ImageAlphaClear, void, (S32 imageId, Color color, F32 threshold), ,
                        "Clear alpha channel to desired color") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageAlphaClear(img, color, threshold);
    }

    // RLAPI void ImageAlphaMask(Image *image, Image alphaMask);
    DefineEngineFunction(ImageAlphaMask, void, (S32 imageId, S32 alphaMaskId), ,
                        "Apply alpha mask to image") {
        Image* img = ImageMap.get(imageId);
        Image* mask = ImageMap.get(alphaMaskId);
        if (img && mask) ImageAlphaMask(img, *mask);
    }

    // RLAPI void ImageAlphaPremultiply(Image *image);
    DefineEngineFunction(ImageAlphaPremultiply, void, (S32 imageId), ,
                        "Premultiply alpha channel") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageAlphaPremultiply(img);
    }

    // RLAPI void ImageBlurGaussian(Image *image, int blurSize);
    DefineEngineFunction(ImageBlurGaussian, void, (S32 imageId, S32 blurSize), ,
                        "Apply Gaussian blur using a box blur approximation") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageBlurGaussian(img, blurSize);
    }

    // RLAPI void ImageResize(Image *image, int newWidth, int newHeight);
    DefineEngineFunction(ImageResize, void, (S32 imageId, S32 newWidth, S32 newHeight), ,
                        "Resize image (Bicubic scaling algorithm)") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageResize(img, newWidth, newHeight);
    }

    // RLAPI void ImageResizeNN(Image *image, int newWidth, int newHeight);
    DefineEngineFunction(ImageResizeNN, void, (S32 imageId, S32 newWidth, S32 newHeight), ,
                        "Resize image (Nearest-Neighbor scaling algorithm)") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageResizeNN(img, newWidth, newHeight);
    }

    // RLAPI void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill);
    DefineEngineFunction(ImageResizeCanvas, void, (S32 imageId, S32 newWidth, S32 newHeight, S32 offsetX, S32 offsetY, Color fill), ,
                        "Resize canvas and fill with color") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageResizeCanvas(img, newWidth, newHeight, offsetX, offsetY, fill);
    }

    // RLAPI void ImageMipmaps(Image *image);
    DefineEngineFunction(ImageMipmaps, void, (S32 imageId), ,
                        "Compute all mipmap levels for a provided image") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageMipmaps(img);
    }

    // RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);
    DefineEngineFunction(ImageDither, void, (S32 imageId, S32 rBpp, S32 gBpp, S32 bBpp, S32 aBpp), ,
                        "Dither image data to 16bpp or lower") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageDither(img, rBpp, gBpp, bBpp, aBpp);
    }

    // RLAPI void ImageFlipVertical(Image *image);
    DefineEngineFunction(ImageFlipVertical, void, (S32 imageId), ,
                        "Flip image vertically") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageFlipVertical(img);
    }

    // RLAPI void ImageFlipHorizontal(Image *image);
    DefineEngineFunction(ImageFlipHorizontal, void, (S32 imageId), ,
                        "Flip image horizontally") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageFlipHorizontal(img);
    }

    // RLAPI void ImageRotate(Image *image, int degrees);
    DefineEngineFunction(ImageRotate, void, (S32 imageId, S32 degrees), ,
                        "Rotate image by input angle in degrees (-359 to 359)") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageRotate(img, degrees);
    }

    // RLAPI void ImageRotateCW(Image *image);
    DefineEngineFunction(ImageRotateCW, void, (S32 imageId), ,
                        "Rotate image clockwise 90deg") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageRotateCW(img);
    }

    // RLAPI void ImageRotateCCW(Image *image);
    DefineEngineFunction(ImageRotateCCW, void, (S32 imageId), ,
                        "Rotate image counter-clockwise 90deg") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageRotateCCW(img);
    }

    // RLAPI void ImageColorTint(Image *image, Color color);
    DefineEngineFunction(ImageColorTint, void, (S32 imageId, Color color), ,
                        "Modify image color: tint") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageColorTint(img, color);
    }

    // RLAPI void ImageColorInvert(Image *image);
    DefineEngineFunction(ImageColorInvert, void, (S32 imageId), ,
                        "Modify image color: invert") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageColorInvert(img);
    }

    // RLAPI void ImageColorGrayscale(Image *image);
    DefineEngineFunction(ImageColorGrayscale, void, (S32 imageId), ,
                        "Modify image color: grayscale") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageColorGrayscale(img);
    }

    // RLAPI void ImageColorContrast(Image *image, int contrast);
    DefineEngineFunction(ImageColorContrast, void, (S32 imageId, S32 contrast), ,
                        "Modify image color: contrast (-100 to 100)") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageColorContrast(img, contrast);
    }

    // RLAPI void ImageColorBrightness(Image *image, int brightness);
    DefineEngineFunction(ImageColorBrightness, void, (S32 imageId, S32 brightness), ,
                        "Modify image color: brightness (-255 to 255)") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageColorBrightness(img, brightness);
    }

    // RLAPI void ImageColorReplace(Image *image, Color color, Color replace);
    DefineEngineFunction(ImageColorReplace, void, (S32 imageId, Color color, Color replace), ,
                        "Modify image color: replace color") {
        Image* img = ImageMap.get(imageId);
        if (img) ImageColorReplace(img, color, replace);
    }

//     RLAPI Color *LoadImageColors(Image image);                                                               // Load color data from image as a Color array (RGBA - 32bit)
//     RLAPI Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorCount);                         // Load colors palette from image as a Color array (RGBA - 32bit)
//     RLAPI void UnloadImageColors(Color *colors);                                                             // Unload color data loaded with LoadImageColors()
//     RLAPI void UnloadImagePalette(Color *colors);                                                            // Unload colors palette loaded with LoadImagePalette()

    // RLAPI Rectangle GetImageAlphaBorder(Image image, float threshold);
    DefineEngineFunction(GetImageAlphaBorder, Rectangle, (S32 imageId, F32 threshold), ,
                        "Get image alpha border rectangle") {
        Image* img = ImageMap.get(imageId);
        if (!img) return Rectangle{ 0, 0, 0, 0 }; // Sinnvoller Fallback bei ungültiger ID
        return GetImageAlphaBorder(*img, threshold);
    }

    // RLAPI Color GetImageColor(Image image, int x, int y);
    DefineEngineFunction(GetImageColor, Color, (S32 imageId, S32 x, S32 y), ,
                        "Get image pixel color at (x, y) position") {
        Image* img = ImageMap.get(imageId);
        if (!img) return Color{ 0, 0, 0, 0 }; // Sinnvoller Fallback bei ungültiger ID
        return GetImageColor(*img, x, y);
    }
    // ------------------------------------------------------------------------
    // Image drawing functions
    // ------------------------------------------------------------------------

    // RLAPI void ImageClearBackground(Image *dst, Color color);
    DefineEngineFunction(ImageClearBackground, void, (S32 dstId, Color color), ,
                        "Clear image background with given color") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageClearBackground(dst, color);
    }

    // RLAPI void ImageDrawPixel(Image *dst, int posX, int posY, Color color);
    DefineEngineFunction(ImageDrawPixel, void, (S32 dstId, S32 posX, S32 posY, Color color), ,
                        "Draw pixel within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawPixel(dst, posX, posY, color);
    }

    // RLAPI void ImageDrawPixelV(Image *dst, Vector2 position, Color color);
    DefineEngineFunction(ImageDrawPixelV, void, (S32 dstId, Vector2 position, Color color), ,
                        "Draw pixel within an image (Vector version)") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawPixelV(dst, position, color);
    }

    // RLAPI void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color);
    DefineEngineFunction(ImageDrawLine, void, (S32 dstId, S32 startPosX, S32 startPosY, S32 endPosX, S32 endPosY, Color color), ,
                        "Draw line within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawLine(dst, startPosX, startPosY, endPosX, endPosY, color);
    }

    // RLAPI void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color);
    DefineEngineFunction(ImageDrawLineV, void, (S32 dstId, Vector2 start, Vector2 end, Color color), ,
                        "Draw line within an image (Vector version)") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawLineV(dst, start, end, color);
    }

    // RLAPI void ImageDrawLineEx(Image *dst, Vector2 start, Vector2 end, int thick, Color color);
    DefineEngineFunction(ImageDrawLineEx, void, (S32 dstId, Vector2 start, Vector2 end, S32 thick, Color color), ,
                        "Draw a line defining thickness within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawLineEx(dst, start, end, thick, color);
    }

    // RLAPI void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color);
    DefineEngineFunction(ImageDrawCircle, void, (S32 dstId, S32 centerX, S32 centerY, S32 radius, Color color), ,
                        "Draw a filled circle within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawCircle(dst, centerX, centerY, radius, color);
    }

    // RLAPI void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color);
    DefineEngineFunction(ImageDrawCircleV, void, (S32 dstId, Vector2 center, S32 radius, Color color), ,
                        "Draw a filled circle within an image (Vector version)") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawCircleV(dst, center, radius, color);
    }

    // RLAPI void ImageDrawCircleLines(Image *dst, int centerX, int centerY, int radius, Color color);
    DefineEngineFunction(ImageDrawCircleLines, void, (S32 dstId, S32 centerX, S32 centerY, S32 radius, Color color), ,
                        "Draw circle outline within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawCircleLines(dst, centerX, centerY, radius, color);
    }

    // RLAPI void ImageDrawCircleLinesV(Image *dst, Vector2 center, int radius, Color color);
    DefineEngineFunction(ImageDrawCircleLinesV, void, (S32 dstId, Vector2 center, S32 radius, Color color), ,
                        "Draw circle outline within an image (Vector version)") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawCircleLinesV(dst, center, radius, color);
    }

    // RLAPI void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color);
    DefineEngineFunction(ImageDrawRectangle, void, (S32 dstId, S32 posX, S32 posY, S32 width, S32 height, Color color), ,
                        "Draw rectangle within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawRectangle(dst, posX, posY, width, height, color);
    }

    // RLAPI void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color);
    DefineEngineFunction(ImageDrawRectangleV, void, (S32 dstId, Vector2 position, Vector2 size, Color color), ,
                        "Draw rectangle within an image (Vector version)") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawRectangleV(dst, position, size, color);
    }

    // RLAPI void ImageDrawRectangleRec(Image *dst, Rectangle rec, Color color);
    DefineEngineFunction(ImageDrawRectangleRec, void, (S32 dstId, Rectangle rec, Color color), ,
                        "Draw rectangle within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawRectangleRec(dst, rec, color);
    }

    // RLAPI void ImageDrawRectangleLines(Image *dst, int posX, int posY, int width, int height, Color color);
    DefineEngineFunction(ImageDrawRectangleLines, void, (S32 dstId, S32 posX, S32 posY, S32 width, S32 height, Color color), ,
                        "Draw rectangle lines within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawRectangleLines(dst, posX, posY, width, height, color);
    }

    // RLAPI void ImageDrawRectangleLinesEx(Image *dst, Rectangle rec, int thick, Color color);
    DefineEngineFunction(ImageDrawRectangleLinesEx, void, (S32 dstId, Rectangle rec, S32 thick, Color color), ,
                        "Draw rectangle lines within an image with extended parameters") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawRectangleLinesEx(dst, rec, thick, color);
    }

    // RLAPI void ImageDrawTriangle(Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color);
    DefineEngineFunction(ImageDrawTriangle, void, (S32 dstId, Vector2 v1, Vector2 v2, Vector2 v3, Color color), ,
                        "Draw triangle within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawTriangle(dst, v1, v2, v3, color);
    }

    // RLAPI void ImageDrawTriangleGradient(Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3);
    DefineEngineFunction(ImageDrawTriangleGradient, void, (S32 dstId, Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3), ,
                        "Draw triangle with interpolated colors within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawTriangleGradient(dst, v1, v2, v3, c1, c2, c3);
    }

    // RLAPI void ImageDrawTriangleLines(Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color);
    DefineEngineFunction(ImageDrawTriangleLines, void, (S32 dstId, Vector2 v1, Vector2 v2, Vector2 v3, Color color), ,
                        "Draw triangle outline within an image") {
        Image* dst = ImageMap.get(dstId);
        if (dst) ImageDrawTriangleLines(dst, v1, v2, v3, color);
    }

    // ------------------------------------------------------------------------
    // Triangle Fan und Strip mit String-Parsing for PointData
    // ------------------------------------------------------------------------

    // RLAPI void ImageDrawTriangleFan(Image *dst, const Vector2 *points, int pointCount, Color color);
    DefineEngineFunction(ImageDrawTriangleFan, void, (S32 dstId, String pointsStr, S32 pointCount, Color color), ,
                        "Draw a triangle fan defined by points within an image (pointsStr format: 'x1 y1 x2 y2 ...')") {
        Image* dst = ImageMap.get(dstId);
        if (!dst || pointCount <= 0) return;

        std::vector<Vector2> points;
        points.reserve(pointCount);

        S32 currentElement = 0;
        for (S32 i = 0; i < pointCount; ++i) {
            const char* xStr = StringUnit::getUnit(pointsStr.c_str(), currentElement++, " ");
            const char* yStr = StringUnit::getUnit(pointsStr.c_str(), currentElement++, " ");

            if (!xStr || !yStr || *xStr == '\0' || *yStr == '\0') {
                Con::errorf("ImageDrawTriangleFan: Missing Points you gave me only: %d !", pointCount);
                return;
            }

            points.push_back(Vector2{ dAtof(xStr), dAtof(yStr) });
        }

        ImageDrawTriangleFan(dst, points.data(), pointCount, color);
    }

    // RLAPI void ImageDrawTriangleStrip(Image *dst, const Vector2 *points, int pointCount, Color color);
    DefineEngineFunction(ImageDrawTriangleStrip, void, (S32 dstId, String pointsStr, S32 pointCount, Color color), ,
                        "Draw a triangle strip defined by points within an image (pointsStr format: 'x1 y1 x2 y2 ...')") {
        Image* dst = ImageMap.get(dstId);
        if (!dst || pointCount <= 0) return;

        std::vector<Vector2> points;
        points.reserve(pointCount);

        S32 currentElement = 0;
        for (S32 i = 0; i < pointCount; ++i) {
            const char* xStr = StringUnit::getUnit(pointsStr.c_str(), currentElement++, " ");
            const char* yStr = StringUnit::getUnit(pointsStr.c_str(), currentElement++, " ");

            if (!xStr || !yStr || *xStr == '\0' || *yStr == '\0') {
                Con::errorf("ImageDrawTriangleFan: Missing Points you gave me only: %d !", pointCount);
                return;
            }

            points.push_back(Vector2{ dAtof(xStr), dAtof(yStr) });
        }

        ImageDrawTriangleStrip(dst, points.data(), pointCount, color);
    }

    // RLAPI void ImageDraw(Image *dst, Image src, Rectangle srcRec, Rectangle dstRec, Color tint);
    DefineEngineFunction(ImageDraw, void, (S32 dstId, S32 srcId, Rectangle srcRec, Rectangle dstRec, Color tint), ,
                        "Draw a source image within a destination image (tint applied to source)") {
        Image* dst = ImageMap.get(dstId);
        Image* src = ImageMap.get(srcId);
        if (dst && src) {
            ImageDraw(dst, *src, srcRec, dstRec, tint);
        }
    }

    // RLAPI void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color);
    DefineEngineFunction(ImageDrawText, void, (S32 dstId, String text, S32 posX, S32 posY, S32 fontSize, Color color), ,
                        "Draw text (using default font) within an image (destination)") {
        Image* dst = ImageMap.get(dstId);
        if (dst) {
            ImageDrawText(dst, text.c_str(), posX, posY, fontSize, color);
        }
    }

    // RLAPI void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint);
    DefineEngineFunction(ImageDrawTextEx, void, (S32 dstId, S32 fontId, String text, Vector2 position, F32 fontSize, F32 spacing, Color tint), ,
                        "Draw text (custom sprite font) within an image (destination)") {
        Image* dst = ImageMap.get(dstId);
        Font* font = FontMap.get(fontId);
        if (dst && font) {
            ImageDrawTextEx(dst, *font, text.c_str(), position, fontSize, spacing, tint);
        }
    }


} //ElfResource
