//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// raymath.h interface WARNING: not completed!!
//-----------------------------------------------------------------------------
#include "console/engineAPI.h"
#include "ConsoleTypes.h"
#include "raymath.h"
// #include "interface/elfTools.h"
#include <raymath.h>


DefineEngineFunction( Vector3Add, Vector3, (Vector3 v1, Vector3 v2), , "Adds two Vector3 values together.") {
    return ::Vector3Add(v1, v2);
}

DefineEngineFunction( Vector3Subtract, Vector3, (Vector3 v1, Vector3 v2), , "Subtracts v2 from v1.") {
    return ::Vector3Subtract(v1, v2);
}

DefineEngineFunction( Vector3Scale, Vector3, (Vector3 v, F32 scale), , "Scales a Vector3 by a float multiplier.") {
    return ::Vector3Scale(v, scale);
}

DefineEngineFunction( Vector3Normalize, Vector3, (Vector3 v), , "Normalizes a Vector3 to a length of 1.0.") {
    return ::Vector3Normalize(v);
}

DefineEngineFunction( Vector3Length, F32, (Vector3 v), , "Returns the length of a Vector3.") {
    return ::Vector3Length(v);
}

DefineEngineFunction( Vector3Distance, F32, (Vector3 v1, Vector3 v2), , "Returns the distance between two Vector3 points.") {
    return ::Vector3Distance(v1, v2);
}
