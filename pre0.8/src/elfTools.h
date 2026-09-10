//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// Tools and Helper functions
//-----------------------------------------------------------------------------
#pragma once

#include "raylib.h"
#include <console/console.h>
#include <vector>

namespace ElfTools {

//-----------------------------------------------------------------------------
// Helper-Funktion um RayCollision sauber für TorqueScript als String aufzubereiten
// Format: "hitPoint.x hitPoint.y hitPoint.z hitNormal.x hitNormal.y hitNormal.z distance"
inline const char* FormatRayCollision(RayCollision collision) {
    if (!collision.hit) {
        return "";
    }
    char* ret = Con::getReturnBuffer(128);
    dSprintf(ret, 128, "%g %g %g %g %g %g %g",
             collision.point.x,  collision.point.y,  collision.point.z,
             collision.normal.x, collision.normal.y, collision.normal.z,
             collision.distance);
    return ret;
}
// -----------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------
// Helper func to get Vector2  from: Vector<F32> pointValues, S32 pointCount
inline std::vector<Vector2> getVector2List(Vector<F32> pointValues, S32 pointCount) {
    std::vector<Vector2> points;
    if ( pointCount <= 0) return points;

    if (pointValues.size() != (pointCount * 2)) {
        Con::errorf("PointValues size (%d) does not match pointCount * 2 (%d)!", (int)pointValues.size(), pointCount * 2);
        return points;
    }

    points.reserve(pointCount);

    for (S32 i = 0; i < pointCount; ++i) {
        points.push_back( { pointValues[i*2], pointValues[i*2+1] });
    }
    return points;
}
// -----------------------------------------------------------------------------------

inline std::vector<Vector3> getVector3List(Vector<F32> pointValues, S32 pointCount) {
    std::vector<Vector3> points;
    if (pointCount <= 0) return points;

    if (pointValues.size() != (size_t)(pointCount * 3)) {
        Con::errorf("getVector3List: pointValues size (%d) does not match pointCount * 3 (%d)!", (int)pointValues.size(), pointCount * 3);
        return points;
    }

    points.reserve(pointCount);

    for (S32 i = 0; i < pointCount; ++i) {
        S32 idx = i * 3;
        points.push_back({ pointValues[idx], pointValues[idx + 1], pointValues[idx + 2] });
    }
    return points;
}
// -----------------------------------------------------------------------------------

inline std::vector<Vector4> getVector4List(Vector<F32> pointValues, S32 pointCount) {
    std::vector<Vector4> points;
    if (pointCount <= 0) return points;

    if (pointValues.size() != (size_t)(pointCount * 4)) {
        Con::errorf("getVector4List: pointValues size (%d) does not match pointCount * 4 (%d)!", (int)pointValues.size(), pointCount * 4);
        return points;
    }

    points.reserve(pointCount);

    for (S32 i = 0; i < pointCount; ++i) {
        S32 idx = i * 4;
        points.push_back({ pointValues[idx], pointValues[idx + 1], pointValues[idx + 2], pointValues[idx + 3] });
    }
    return points;
}

//-----------------------------------------------------------------------------



} //namespace
