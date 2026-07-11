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

//-----------------------------------------------------------------------------
//       -------------------------  Vector2  -------------------------
//-----------------------------------------------------------------------------
DefineEngineFunction( Vector2Add, Vector2, (Vector2 v1, Vector2 v2), , "Adds two Vector2 values together.") {
    return ::Vector2Add(v1, v2);
}

DefineEngineFunction( Vector2AddValue, Vector2, (Vector2 v1, F32 value), , "Adds a value to Vector2.") {
    return ::Vector2AddValue(v1, value);
}

DefineEngineFunction( Vector2Subtract, Vector2, (Vector2 v1, Vector2 v2), , "Subtracts v2 from v1.") {
    return ::Vector2Subtract(v1, v2);
}

DefineEngineFunction( Vector2SubtractValue, Vector2, (Vector2 v1, F32 value), , "Subtracts a value to Vector2.") {
    return ::Vector2SubtractValue(v1, value);
}

DefineEngineFunction( Vector2Scale, Vector2, (Vector2 v, F32 scale), , "Scales a Vector2 by a float multiplier.") {
    return ::Vector2Scale(v, scale);
}

DefineEngineFunction( Vector2Multiply, Vector2, (Vector2 v1, Vector2 v2), , "Multiply vector by vector.") {
    return ::Vector2Multiply(v1, v2);
}




DefineEngineFunction( Vector2Length, F32, (Vector2 v), , "Returns the length of a Vector2.") {
    return ::Vector2Length(v);
}

DefineEngineFunction( Vector2LengthSqr, F32, (Vector2 v), , "Calculate vector3 square length") {
    return ::Vector2LengthSqr(v);
}

DefineEngineFunction( Vector2DotProduct, F32, (Vector2 v1, Vector2 v2), , "Calculate two vectors dot product") {
    return ::Vector2DotProduct(v1, v2);
}

DefineEngineFunction( Vector2DistanceSqr, F32, (Vector2 v1, Vector2 v2), , "Returns the squared distance between two Vector2 points.") {
    return ::Vector2DistanceSqr(v1, v2);
}

DefineEngineFunction( Vector2Angle, F32, (Vector2 v1, Vector2 v2), , "Calculate angle between two vectors") {
    return ::Vector2Angle(v1, v2);
}

DefineEngineFunction( Vector2Distance, F32, (Vector2 v1, Vector2 v2), , "Returns the distance between two Vector2 points.") {
    return ::Vector2Distance(v1, v2);
}

DefineEngineFunction( Vector2Negate, Vector2, (Vector2 v), , "Negate provided vector (invert direction)") {
    return ::Vector2Negate(v);
}

DefineEngineFunction( Vector2Divide, Vector2, (Vector2 v1, Vector2 v2), , "Divide vector by vector") {
    return ::Vector2Divide(v1,v2);
}

DefineEngineFunction( Vector2Normalize, Vector2, (Vector2 v), , "Normalizes a Vector2 to a length of 1.0.") {
    return ::Vector2Normalize(v);
}



DefineEngineFunction( Vector2Transform, Vector2, (Vector2 v1, Matrix mat), , "Transforms a Vector2 by a given Matrix") {
    return ::Vector2Transform(v1,mat);
}


DefineEngineFunction( Vector2MoveTowards, Vector2, (Vector2 v1, Vector2 v2, F32 maxDistance), , "Move Vector towards target") {
    return ::Vector2MoveTowards(v1,v2, maxDistance);
}

// FIXME ... tired .. more to come << Vector2Invert ....
//-----------------------------------------------------------------------------
//       -------------------------  Vector3  -------------------------
//-----------------------------------------------------------------------------
DefineEngineFunction( Vector3Add, Vector3, (Vector3 v1, Vector3 v2), , "Adds two Vector3 values together.") {
    return ::Vector3Add(v1, v2);
}

DefineEngineFunction( Vector3AddValue, Vector3, (Vector3 v1, F32 value), , "Adds a value to Vector3.") {
    return ::Vector3AddValue(v1, value);
}

DefineEngineFunction( Vector3Subtract, Vector3, (Vector3 v1, Vector3 v2), , "Subtracts v2 from v1.") {
    return ::Vector3Subtract(v1, v2);
}

DefineEngineFunction( Vector3SubtractValue, Vector3, (Vector3 v1, F32 value), , "Subtracts a value to Vector3.") {
    return ::Vector3SubtractValue(v1, value);
}

DefineEngineFunction( Vector3Scale, Vector3, (Vector3 v, F32 scale), , "Scales a Vector3 by a float multiplier.") {
    return ::Vector3Scale(v, scale);
}

DefineEngineFunction( Vector3Multiply, Vector3, (Vector3 v1, Vector3 v2), , "Multiply vector by vector.") {
    return ::Vector3Multiply(v1, v2);
}


DefineEngineFunction( Vector3CrossProduct, Vector3, (Vector3 v1, Vector3 v2), , "Calculate two vectors cross product") {
    return ::Vector3CrossProduct(v1, v2);
}

DefineEngineFunction( Vector3Perpendicular, Vector3, (Vector3 v), , "Calculate one vector perpendicular vector") {
    return ::Vector3Perpendicular(v);
}


DefineEngineFunction( Vector3Length, F32, (Vector3 v), , "Returns the length of a Vector3.") {
    return ::Vector3Length(v);
}

DefineEngineFunction( Vector3LengthSqr, F32, (Vector3 v), , "Calculate vector3 square length") {
    return ::Vector3LengthSqr(v);
}

DefineEngineFunction( Vector3DotProduct, F32, (Vector3 v1, Vector3 v2), , "Calculate two vectors dot product") {
    return ::Vector3DotProduct(v1, v2);
}

DefineEngineFunction( Vector3DistanceSqr, F32, (Vector3 v1, Vector3 v2), , "Returns the squared distance between two Vector3 points.") {
    return ::Vector3DistanceSqr(v1, v2);
}

DefineEngineFunction( Vector3Angle, F32, (Vector3 v1, Vector3 v2), , "Calculate angle between two vectors") {
    return ::Vector3Angle(v1, v2);
}

DefineEngineFunction( Vector3Distance, F32, (Vector3 v1, Vector3 v2), , "Returns the distance between two Vector3 points.") {
    return ::Vector3Distance(v1, v2);
}

DefineEngineFunction( Vector3Negate, Vector3, (Vector3 v), , "Negate provided vector (invert direction)") {
    return ::Vector3Negate(v);
}

DefineEngineFunction( Vector3Divide, Vector3, (Vector3 v1, Vector3 v2), , "Divide vector by vector") {
    return ::Vector3Divide(v1,v2);
}

DefineEngineFunction( Vector3Normalize, Vector3, (Vector3 v), , "Normalizes a Vector3 to a length of 1.0.") {
    return ::Vector3Normalize(v);
}

DefineEngineFunction( Vector3Project, Vector3, (Vector3 v1, Vector3 v2), , "Calculate the projection of the vector v1 on to v2") {
    return ::Vector3Project(v1,v2);
}

DefineEngineFunction( Vector3Reject, Vector3, (Vector3 v1, Vector3 v2), , "Calculate the rejection of the vector v1 on to v2") {
    return ::Vector3Reject(v1,v2);
}

// Vector3OrthoNormalize... << skipped


DefineEngineFunction( Vector3Transform, Vector3, (Vector3 v1, Matrix mat), , "Transforms a Vector3 by a given Matrix") {
    return ::Vector3Transform(v1,mat);
}

DefineEngineFunction( Vector3RotateByQuaternion, Vector3, (Vector3 v1, Vector4 v2), , "Transform a vector by quaternion rotation") {
    return ::Vector3RotateByQuaternion(v1,v2);
}

DefineEngineFunction( Vector3RotateByAxisAngle, Vector3, (Vector3 v1, Vector3 axis, F32 angle)
    , , "Rotates a vector around an axis") {
    return ::Vector3RotateByAxisAngle(v1,axis, angle);
}

DefineEngineFunction( Vector3MoveTowards, Vector3, (Vector3 v1, Vector3 v2, F32 maxDistance), , "Move Vector towards target") {
    return ::Vector3MoveTowards(v1,v2, maxDistance);
}

// FIXME ... tired .. more to come << Vector3Lerp ....
