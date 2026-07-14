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

#include "raylib.h"

// Map some Types for code compat with ohmFlux:
typedef Vector2 Point2F ;
typedef Vector3 Point3F ;
typedef Vector4 Point4F ;
typedef Rectangle RectF ;

DECLARE_STRUCT(Color);
DefineConsoleType( TypeColor, Color )

DECLARE_STRUCT( Vector2 );
DefineConsoleType( TypeVector2, Vector2 )

DECLARE_STRUCT( Vector3 );
DefineConsoleType( TypeVector3, Vector3 )

DECLARE_STRUCT( Vector4 );
DefineConsoleType( TypeVector4, Vector4 )


DECLARE_STRUCT( Rectangle );
DefineConsoleType( TypeRectangle, Rectangle )

DECLARE_STRUCT( Ray );
DefineConsoleType( TypeRay, Ray )


DECLARE_STRUCT( BoundingBox );
DefineConsoleType( TypeBoundingBox, BoundingBox )

DECLARE_STRUCT( Matrix );
DefineConsoleType( TypeMatrix, Matrix );

