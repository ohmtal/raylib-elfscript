//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT

//-----------------------------------------------------------------------------
// Console Types source
//-----------------------------------------------------------------------------
#pragma once
#include "math/mMathFn.h"
#include <SDL3/SDL.h>
#ifndef _DYNAMIC_CONSOLETYPES_H_
#include "console/dynamicTypes.h"
#endif

#ifndef _ENGINEPRIMITIVES_H_
#include "console/enginePrimitives.h"
#endif

#ifndef _ENGINESTRUCTS_H_
#include "console/engineStructs.h"
#endif

typedef SDL_FColor Color4F;
typedef SDL_Color Color;
typedef SDL_FRect RectF;
typedef SDL_Rect RectI;
typedef SDL_Point Point2I;
typedef SDL_FPoint Point2F;


inline bool isValid(const RectF& rect) {
    return (rect.w > 0 && rect.h > 0);
}

// -------------- SDL_Color --------------------
inline bool operator==(const SDL_Color& a, const SDL_Color& b) {
    return (
        a.r == b.r &&
        a.g == b.g &&
        a.b == b.b &&
        a.a == b.a
    );
}
inline bool operator != (const SDL_Color& a, const SDL_Color& b) {
    return (
        a.r != b.r ||
        a.g != b.g ||
        a.b != b.b ||
        a.a != b.a
    );
}
inline void setValueScale(SDL_Color& color, F32 scale){
    scale = ElfMath::mClampF(scale, 0.0f, 1.0f);

    F32 gray = 1.0f; //(color.r * 0.299f) + (color.g * 0.587f) + (color.b * 0.114f);

    color.r = static_cast<Uint8>(gray + (scale * (color.r - gray)));
    color.g = static_cast<Uint8>(gray + (scale * (color.g - gray)));
    color.b = static_cast<Uint8>(gray + (scale * (color.b - gray)));
}

inline void setScale(SDL_Color& color, F32 scale){
    scale = ElfMath::mClampF(scale, 0.0f, 3.0f); //let overscale 3 times

    color.r = static_cast<Uint8>(ElfMath::mClamp((F32)color.r * scale, 0, 255));
    color.g = static_cast<Uint8>(ElfMath::mClamp((F32)color.g * scale, 0, 255));
    color.b = static_cast<Uint8>(ElfMath::mClamp((F32)color.b * scale, 0, 255));

}


inline void setSaturationScale(SDL_Color& color, F32 scale){
    scale = ElfMath::mClampF(scale, 0.0f, 1.0f);
    F32 maxChan = static_cast<F32>(std::max({color.r, color.g, color.b}));
    F32 minChan = static_cast<F32>(std::min({color.r, color.g, color.b}));
    if (maxChan == minChan || maxChan == 0.0f) {
        return;
    }
    F32 newMinChan = maxChan * (1.0f - scale);
    F32 rangeOld = maxChan - minChan;
    F32 rangeNew = maxChan - newMinChan;
    color.r = static_cast<Uint8>(maxChan - ((maxChan - color.r) * rangeNew / rangeOld) + 0.5f);
    color.g = static_cast<Uint8>(maxChan - ((maxChan - color.g) * rangeNew / rangeOld) + 0.5f);
    color.b = static_cast<Uint8>(maxChan - ((maxChan - color.b) * rangeNew / rangeOld) + 0.5f);
}


inline SDL_Color fromHSV(S32 hue, F32 saturation, F32 value, U8 alpha = 255) {
    hue        = ElfMath::mClamp(hue, 0, 359);
    saturation = ElfMath::mClampF(saturation, 0.f, 1.f);
    value      = ElfMath::mClampF(value, 0.f, 1.f);

    SDL_Color color;
    color.a = alpha;

    // grayscale
    if (saturation == 0.f) {
        U8 gray = static_cast<U8>(value * 255.f + 0.5f);
        color.r = gray;
        color.g = gray;
        color.b = gray;
        return color;
    }

    S32 sector = hue / 60;
    F32 remainder = (hue % 60) / 60.f;

    F32 v_float = value * 255.f;
    F32 p_float = v_float * (1.f - saturation);
    F32 q_float = v_float * (1.f - (saturation * remainder));
    F32 t_float = v_float * (1.f - (saturation * (1.f - remainder)));

    U8 v = static_cast<U8>(v_float + 0.5f);
    U8 p = static_cast<U8>(p_float + 0.5f);
    U8 q = static_cast<U8>(q_float + 0.5f);
    U8 t = static_cast<U8>(t_float + 0.5f);

    switch (sector) {
        case 0:  color.r = v; color.g = t; color.b = p; break;
        case 1:  color.r = q; color.g = v; color.b = p; break;
        case 2:  color.r = p; color.g = v; color.b = t; break;
        case 3:  color.r = p; color.g = q; color.b = v; break;
        case 4:  color.r = t; color.g = p; color.b = v; break;
        default: color.r = v; color.g = p; color.b = q; break;
    }

    return color;
}


// -------------- SDL_FPoint -------------------
// SDL_FPoint functions FIXME can be moved to addons
inline float length(const SDL_FPoint& p) {
    return ElfMath::mSqrt(p.x * p.x + p.y * p.y);
}

inline float isZero(const SDL_FPoint& p) {
    return (p.x == 0.f && p.y == 0.f);
}

inline SDL_FPoint normalize(const SDL_FPoint& p) {
    float len = length(p);
    if (len > 0.0f) {
        return SDL_FPoint{ p.x / len, p.y / len };
    }
    return SDL_FPoint{ 0.0f, 0.0f };
}

inline bool operator==(const SDL_FPoint& a, const SDL_FPoint& b) {
    return ( a.x == b.x && a.y == b.y );
}
inline bool operator!=(const SDL_FPoint& a, const SDL_FPoint& b) {
    return ( a.x != b.x || a.y != b.y );
}

inline SDL_FPoint operator+(const SDL_FPoint& a, const SDL_FPoint& b) {
    return SDL_FPoint{ a.x + b.x, a.y + b.y };
}

inline SDL_FPoint operator-(const SDL_FPoint& a, const SDL_FPoint& b) {
    return SDL_FPoint{ a.x - b.x, a.y - b.y };
}

inline SDL_FPoint operator*(const SDL_FPoint& p, float scalar) {
    return SDL_FPoint{ p.x * scalar, p.y * scalar };
}

inline SDL_FPoint operator/(const SDL_FPoint& p, float scalar) {
    return SDL_FPoint{ p.x / scalar, p.y / scalar };
}

inline SDL_FPoint& operator+=(SDL_FPoint& a, const SDL_FPoint& b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline SDL_FPoint& operator-=(SDL_FPoint& a, const SDL_FPoint& b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}
// ------------------------------

// // from OhmFlux
// struct Point3F {
//     F32 x = 0.f, y=0.f, z=0.f;
//
//     F32 distSq(const Point3F& other) const {
//         F32 dx = x - other.x;
//         F32 dy = y - other.y;
//         F32 dz = z - other.z;
//         return dx*dx + dy*dy + dz*dz;
//     }
//
//     F32 lenSquared() const {
//         return (x * x + y * y + z * z);
//     }
//     F32 len() const {
//         return sqrt(x*x + y*y + z*z);
//     }
//
//     Point3F operator+(const Point3F& v) const { return {x + v.x, y + v.y, z + v.z}; }
//     Point3F operator-(const Point3F& v) const { return {x - v.x, y - v.y, z - v.z}; }
//     Point3F operator*(const Point3F& v) const { return {x * v.x, y * v.y, z * v.z}; }
//     Point3F operator/(const Point3F& v) const {
//         return {
//             x / v.x != 0.f ? v.x : 1e-9f,
//             y / v.y != 0.f ? v.y : 1e-9f,
//             z / v.z != 0.f ? v.z : 1e-9f
//         };
//     }
//
//     bool operator==(const Point3F& v) const { return (x == v.x && y == v.y && z == v.z); }
//
//     Point3F& operator+=(const Point2F& v) { x += v.x; y += v.y; return *this; }
//
//     F32 dot(const Point3F& v) const { return (x * v.x + y * v.y + z * v.z); }
//
//     Point2F toPoint2F() const { return { x,y}; }
//
//     bool isZero() const { return (x == 0.f && y == 0.f && z == 0.f); }
//
//     void normalize() {
//         F32 l = len();
//         if (l > 0.0f) { x /= l; y /= l; z /= l;}
//     }
// };

//


DECLARE_STRUCT(Color);
DECLARE_STRUCT(Color4F);
DECLARE_STRUCT( RectI );
DECLARE_STRUCT( RectF );
DECLARE_STRUCT( Point2I );
DECLARE_STRUCT( Point2F );
// DECLARE_STRUCT( Point3F );

DefineConsoleType( TypeColor, Color )
DefineConsoleType( TypeColorF, Color4F )
DefineConsoleType( TypeRectI, RectI )
DefineConsoleType( TypeRectF, RectF )
DefineConsoleType( TypePoint2I, Point2I )
DefineConsoleType( TypePoint2F, Point2F )
// DefineConsoleType( TypePoint3F, Point3F )

