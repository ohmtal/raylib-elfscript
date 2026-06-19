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

DECLARE_STRUCT(Color);
DefineConsoleType( TypeColor, Color )

DECLARE_STRUCT( Vector2 );
DefineConsoleType( TypeVector2, Vector2 )

DECLARE_STRUCT( Vector3 );
DefineConsoleType( TypeVector3, Vector3 )


DECLARE_STRUCT( Rectangle );
DefineConsoleType( TypeRectangle, Rectangle )

// DECLARE_STRUCT_R(Point2I);
// DefineConsoleType( TypePoint2I, Point2I )
//
// DECLARE_STRUCT( RectI );
// DECLARE_STRUCT( RectF );
// DECLARE_STRUCT( Point2F );

//
// DefineConsoleType( TypeRectI, RectI )
// DefineConsoleType( TypeRectF, RectF )



