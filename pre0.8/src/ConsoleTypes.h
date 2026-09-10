//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#pragma once
#include "math/mMathFn.h"
#ifndef _DYNAMIC_CONSOLETYPES_H_
#include "console/dynamicTypes.h"
#endif

#ifndef _ENGINEPRIMITIVES_H_
#include "console/enginePrimitives.h"
#endif

#ifndef _ENGINESTRUCTS_H_
#include "console/engineStructs.h"
#endif


#ifndef _ENGINEAPI_H_
#include "console/engineAPI.h"
#endif

#include "raylib.h"

// Map some Types for code compat with ohmFlux:
typedef Vector2 Point2F ;
typedef Vector3 Point3F ;
typedef Vector4 Point4F ;
typedef Rectangle RectF ;


// ----------------------------------------------------------------------------
DECLARE_STRUCT(Color);
DefineConsoleType( TypeColor, Color )

inline ConsoleVector toConsoleVector(const Color& value) { return { (F32)value.r,(F32)value.g,(F32)value.b,(F32)value.a}; }
inline Color toColor(const ConsoleVector& value) { return { (U8)value.points[0],(U8)value.points[1],(U8)value.points[2],(U8)value.points[3]}; }

#ifdef ENABLE_CONSOLE_VECTOR
template<>
struct EngineUnmarshallData< Color >
{
    Color operator()( ConsoleValue &ref ) const
    {
        ConsoleVector v = ref.getVector();
        // I did lazy add only 3 params so i need to set 255 if 0! alpha 0 is not possible .. but ok
        U8 a =  (v.points[3] == 0.f) ? 255 : (U8)v.points[3];
        return {(U8)v.points[0], (U8)v.points[1], (U8)v.points[2], a};
    }

    Color operator()( const char* str ) const
    {
        Color result = {0};
        if (str && str[0] != '\0') {
            // dSscanf(str, "%hhu %hhu %hhu %hhu",
            dSscanf(str, "%d %d %d %d",
                    result.r,
                    result.g,
                    result.b,
                    result.a
            );
        }
        return result;
    }
};
#endif


// ----------------------------------------------------------------------------
DECLARE_STRUCT( Vector2 );
DefineConsoleType( TypeVector2, Vector2 )

inline ConsoleVector toConsoleVector(const Vector2& value) { return { value.x,value.y,0.f,0.f}; }
inline Vector2 toVector2(const ConsoleVector& value) { return { value.points[0],value.points[1]}; }

#ifdef ENABLE_CONSOLE_VECTOR
template<>
struct EngineUnmarshallData< Vector2 >
{
    Vector2 operator()( ConsoleValue &ref ) const
    {
        ConsoleVector v = ref.getVector();
        return {v.points[0], v.points[1]};
    }

    Vector2 operator()( const char* str ) const
    {
        Vector2 result = {0};
        if (str && str[0] != '\0') {
            dSscanf(str, "%g %g",
                    result.x,
                    result.y
            );
        }
        return result;
    }
};
#endif

// ----------------------------------------------------------------------------
DECLARE_STRUCT( Vector3 );
DefineConsoleType( TypeVector3, Vector3 )

inline ConsoleVector toConsoleVector(const Vector3& value) { return { value.x,value.y,value.z, 0.f}; }
inline Vector3 toVector3(const ConsoleVector& value) { return { value.points[0],value.points[1],value.points[2]}; }

#ifdef ENABLE_CONSOLE_VECTOR
template<>
struct EngineUnmarshallData< Vector3 >
{
    Vector3 operator()( ConsoleValue &ref ) const
    {
        ConsoleVector v = ref.getVector();
        return {v.points[0], v.points[1], v.points[2]};
    }

    Vector3 operator()( const char* str ) const
    {
        Vector3 result = {0};
        if (str && str[0] != '\0') {
            dSscanf(str, "%g %g %g",
                    result.x,
                    result.y,
                    result.z
            );
        }
        return result;
    }
};
#endif

// ----------------------------------------------------------------------------
DECLARE_STRUCT( Vector4 );
DefineConsoleType( TypeVector4, Vector4 )


inline ConsoleVector toConsoleVector(const Vector4& value) { return { value.x,value.y,value.z,value.w}; }
inline Vector4 toVector4(const ConsoleVector& value) { return { value.points[0],value.points[1],value.points[2],value.points[3]}; }

#ifdef ENABLE_CONSOLE_VECTOR
template<>
struct EngineUnmarshallData< Vector4 >
{
    Vector4 operator()( ConsoleValue &ref ) const
    {
        ConsoleVector v = ref.getVector();
        return {v.points[0], v.points[1], v.points[2], v.points[3]};
    }

    Vector4 operator()( const char* str ) const
    {
        Vector4 result = {0};
        if (str && str[0] != '\0') {
            dSscanf(str, "%g %g %g %g",
                    result.x,
                    result.y,
                    result.z,
                    result.w
            );
        }
        return result;
    }
};
#endif


// ----------------------------------------------------------------------------
DECLARE_STRUCT( Rectangle );
DefineConsoleType( TypeRectangle, Rectangle )

inline ConsoleVector toConsoleVector(const Rectangle& value) { return { value.x,value.y,value.width,value.height}; }
inline Rectangle toRectangle(const ConsoleVector& value) { return { value.points[0],value.points[1],value.points[2],value.points[3]}; }

#ifdef ENABLE_CONSOLE_VECTOR
template<>
struct EngineUnmarshallData< Rectangle >
{
    Rectangle operator()( ConsoleValue &ref ) const
    {
        ConsoleVector v = ref.getVector();
        return {v.points[0], v.points[1], v.points[2], v.points[3]};
    }

    Rectangle operator()( const char* str ) const
    {
        RectF result = {0};
        if (str && str[0] != '\0') {
            dSscanf(str, "%g %g %g %g",
                    result.x,
                    result.y,
                    result.width,
                    result.height
            );
        }
        return result;
    }
};
#endif

// ----------------------------------------------------------------------------
DECLARE_STRUCT( Ray );
DefineConsoleType( TypeRay, Ray )

// ----------------------------------------------------------------------------
DECLARE_STRUCT( BoundingBox );
DefineConsoleType( TypeBoundingBox, BoundingBox )

// ----------------------------------------------------------------------------
DECLARE_STRUCT( Matrix );
DefineConsoleType( TypeMatrix, Matrix );

