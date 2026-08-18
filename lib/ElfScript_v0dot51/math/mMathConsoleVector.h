//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// NOTE: untested so far
//-----------------------------------------------------------------------------
#pragma once

#include "console/console.h"
#include "mMathFn.h"

namespace ElfMath {

inline ConsoleVector Vec4Add(const ConsoleVector& v1, const ConsoleVector& v2){
    return {
          v1.points[0] + v2.points[0]
        , v1.points[1] + v2.points[1]
        , v1.points[2] + v2.points[2]
        , v1.points[3] + v2.points[3]
    };
}
inline ConsoleVector Vec4Sub(const ConsoleVector& v1, const ConsoleVector& v2){
    return {
        v1.points[0] - v2.points[0]
        , v1.points[1] - v2.points[1]
        , v1.points[2] - v2.points[2]
        , v1.points[3] - v2.points[3]
    };
}



inline ConsoleVector Vec4Mul(const ConsoleVector& v1, const ConsoleVector& v2){
    return {
        v1.points[0] * v2.points[0]
        , v1.points[1] * v2.points[1]
        , v1.points[2] * v2.points[2]
        , v1.points[3] * v2.points[3]
    };
}

inline ConsoleVector Vec4Mul(const ConsoleVector& v1, F32 f){
    return {
          v1.points[0] * f
        , v1.points[1] * f
        , v1.points[2] * f
        , v1.points[3] * f
    };
}


inline ConsoleVector Vec4Div(const ConsoleVector& v1, const ConsoleVector& v2){
    return {
        v1.points[0]   / v2.points[0] != 0.f ? v2.points[0] :  1e-9f
        ,v1.points[1]   / v2.points[1] != 0.f ? v2.points[1] :  1e-9f
        ,v1.points[2]   / v2.points[2] != 0.f ? v2.points[2] :  1e-9f
        ,v1.points[3]   / v2.points[3] != 0.f ? v2.points[3] :  1e-9f
    };
}
inline ConsoleVector Vec4Div(const ConsoleVector& v1, F32 f){
    if (f == 0.0f) f = 1e-9f;
    return {
         v1.points[0]   / f
        ,v1.points[1]   / f
        ,v1.points[2]   / f
        ,v1.points[3]   / f
    };
}


inline bool Vec4Equal(const ConsoleVector& v1, const ConsoleVector& v2){
    return
        v1.points[0]  ==  v2.points[0]
        && v1.points[1]  ==  v2.points[1]
        && v1.points[2]  ==  v2.points[2]
        && v1.points[3]  ==  v2.points[3]
        ;
}
inline bool Vec3Equal(const ConsoleVector& v1, const ConsoleVector& v2){
    return
    v1.points[0]  ==  v2.points[0]
    && v1.points[1]  ==  v2.points[1]
    && v1.points[2]  ==  v2.points[2]
    ;
}
inline bool Vec2Equal(const ConsoleVector& v1, const ConsoleVector& v2){
    return
    v1.points[0]  ==  v2.points[0]
    && v1.points[1]  ==  v2.points[1]
    ;
}

inline ConsoleVector operator +  (const ConsoleVector& v1, const ConsoleVector& v2)  { return Vec4Add(v1,v2); }
inline ConsoleVector operator += ( ConsoleVector& v1, const ConsoleVector& v2)  { v1 = Vec4Add(v1,v2); return v1;}

inline ConsoleVector operator -  (const ConsoleVector& v1, const ConsoleVector& v2)  { return Vec4Sub(v1,v2); }
inline ConsoleVector operator -= ( ConsoleVector& v1, const ConsoleVector& v2)  { v1 = Vec4Sub(v1,v2); return v1;}

inline ConsoleVector operator *  (const ConsoleVector& v1, const ConsoleVector& v2)  { return Vec4Mul(v1,v2); }
inline ConsoleVector operator *= ( ConsoleVector& v1, const ConsoleVector& v2)  { v1 = Vec4Mul(v1,v2); return v1;}

inline ConsoleVector operator /  (const ConsoleVector& v1, const ConsoleVector& v2)  { return Vec4Div(v1,v2); }
inline ConsoleVector operator /= ( ConsoleVector& v1, const ConsoleVector& v2)  { v1 = Vec4Div(v1,v2); return v1;}

inline bool operator == ( ConsoleVector& v1, const ConsoleVector& v2)  { return Vec4Equal(v1,v2); }

bool pointInRect(const ConsoleVector& pt, const ConsoleVector& v)  {
    return (
           pt.points[0] >= v.points[0]
        && pt.points[0] <  v.points[0] + v.points[2]
        && pt.points[1] >= v.points[1]
        && pt.points[1] <  v.points[1] + v.points[3]
    );
}
bool pointInRect(F32 x, F32 y, const ConsoleVector& v)  {
    return (
           x >= v.points[0]
        && x <  v.points[0] + v.points[2]
        && y >= v.points[1]
        && y <  v.points[1] + v.points[3]
    );
}

bool contains( ConsoleVector& v1, const ConsoleVector& v2)  {
    return (v2.points[0] >= v1.points[0] &&
    v2.points[1] >= v1.points[1] &&
    v2.points[0] + v2.points[2] <= v1.points[0] + v1.points[2] &&
    v2.points[1] + v2.points[3] <= v1.points[1] + v1.points[3]);
}

bool intersects(ConsoleVector& v1, const ConsoleVector& v2)  {
    return (v1.points[0] < v2.points[0] + v2.points[2] &&
    v1.points[0] + v1.points[2] > v2.points[0] &&
    v1.points[1] < v2.points[1] + v2.points[3] &&
    v1.points[1] + v1.points[3] > v2.points[1]);
}

// ----------------
inline float Vec2LengthSq(const ConsoleVector& v) {
    return (v.points[0] * v.points[0] + v.points[1] * v.points[1]);
}
inline float Vec3LengthSq(const ConsoleVector& v) {
    return (v.points[0] * v.points[0] + v.points[1] * v.points[1] + v.points[2] * v.points[2]);
}


inline float Vec2Length(const ConsoleVector& v) {
    return ElfMath::mSqrt(Vec2LengthSq(v));
}
inline float Vec3Length(const ConsoleVector& v) {
    return ElfMath::mSqrt(Vec3LengthSq(v));
}

inline ConsoleVector Vec2Normalized(const ConsoleVector& v1){
    F32 l = Vec2Length(v1);
    if (l <= 0.0f) return {0};
    return {
         v1.points[0]   / l
        ,v1.points[1]   / l
    };
}

inline ConsoleVector Vec3Normalized(const ConsoleVector& v1){
    F32 l = Vec3Length(v1);
    if (l <= 0.0f) return {0};
    return {
         v1.points[0]   / l
        ,v1.points[1]   / l
        ,v1.points[2]   / l
    };
}

inline float Vec2Dot(const ConsoleVector& v1, const ConsoleVector& v2) {
    return (v1.points[0] * v2.points[0] + v1.points[1] * v2.points[1]);
}

inline float Vec3Dot(const ConsoleVector& v1, const ConsoleVector& v2) {
    return (v1.points[0] * v2.points[0] + v1.points[1] * v2.points[1] + v1.points[2] * v2.points[2]);
}

inline float Vec2Cross(const ConsoleVector& v1, const ConsoleVector& v2) {
    return (v1.points[0] * v2.points[0] - v1.points[1] * v2.points[1]);
}

inline float Vec3Cross(const ConsoleVector& v1, const ConsoleVector& v2) {
    return (v1.points[0] * v2.points[0] - v1.points[1] * v2.points[1] - v1.points[2] * v2.points[2]);
}


} //namespace ElfMath {
