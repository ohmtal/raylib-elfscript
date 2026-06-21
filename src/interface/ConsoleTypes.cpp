//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------#include "raylib.h"
#include "ConsoleTypes.h"
#include <console/console.h>
#include <console/engineAPI.h>
#include <core/strings/stringUnit.h>



// -----------------------------------------------------------------------------
// TypeColor
// -----------------------------------------------------------------------------
IMPLEMENT_STRUCT( Color, Color,,
   "RGBA color in byte format: 255 255 255 255 << pure white ;)" )

   FIELD( r, red, 1, "Red channel value." )
   FIELD( g, green, 1, "Green channel value." )
   FIELD( b, blue, 1, "Blue channel value." )
   FIELD( a, alpha, 1, "Alpha channel value." )

END_IMPLEMENT_STRUCT;

ConsoleType(Color, TypeColor, Color, "")
ImplementConsoleTypeCasters( TypeColor, Color )

ConsoleGetType( TypeColor )
{
   // Fetch color.
   const Color* color = (Color*)dptr;
   // Format as color components.
   static const U32 bufSize = 16;
   char* returnBuffer = Con::getReturnBuffer(bufSize);
   dSprintf(returnBuffer, bufSize, "%d %d %d %d", color->r, color->g, color->b, color->a);
   return(returnBuffer);
}

ConsoleSetType( TypeColor )
{
   Color *tmpColor = (Color *) dptr;
   if(argc == 1)
   {
      S32 r,g,b,a;
      S32 args = dSscanf(argv[0], "%d %d %d %d", &r, &g, &b, &a);
      tmpColor->r = r;
      tmpColor->g = g;
      tmpColor->b = b;
      if (args == 4) tmpColor->a = a;
      else tmpColor->a = 255;

   }
   else if(argc == 3)
   {
      tmpColor->r    = dAtoi(argv[0]);
      tmpColor->g  = dAtoi(argv[1]);
      tmpColor->b   = dAtoi(argv[2]);
      tmpColor->a  = 255;
   }
   else if(argc == 4)
   {
      tmpColor->r    = dAtoi(argv[0]);
      tmpColor->g  = dAtoi(argv[1]);
      tmpColor->b   = dAtoi(argv[2]);
      tmpColor->a  = dAtoi(argv[3]);
   }
   else
      Con::printf("Color must be set as { r, g, b [,a] }, { r g b [a] } ");

}

//-----------------------------------------------------------------------------
// Vector2
//-----------------------------------------------------------------------------

IMPLEMENT_STRUCT( Vector2,
                  Vector2, ,
                  "" )

FIELD( x, x, 1, "X coordinate." )
FIELD( y, y, 1, "Y coordinate." )
END_IMPLEMENT_STRUCT;
//-----------------------------------------------------------------------------
// TypeVector2
//-----------------------------------------------------------------------------
ConsoleType(Vector2, TypeVector2, Vector2, "")
ImplementConsoleTypeCasters( TypeVector2, Vector2 )

ConsoleGetType( TypeVector2 )
{
    Vector2 *pt = (Vector2 *) dptr;
    static const U32 bufSize = 256;
    char* returnBuffer = Con::getReturnBuffer(bufSize);
    dSprintf(returnBuffer, bufSize, "%g %g", pt->x, pt->y);
    return returnBuffer;
}

ConsoleSetType( TypeVector2 )
{
    if(argc == 1)
        dSscanf(argv[0], "%g %g", &((Vector2 *) dptr)->x, &((Vector2 *) dptr)->y);
    else if(argc == 2)
        *((Vector2 *) dptr) = Vector2(dAtof(argv[0]), dAtof(argv[1]));
    else
        Con::printf("Vector2 must be set as { x, y } or \"x y\"");
}

//-----------------------------------------------------------------------------
// Vector3
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( Vector3,
                  Vector3, ,
                  "" )

FIELD( x, x, 1, "X coordinate." )
FIELD( y, y, 1, "Y coordinate." )
FIELD( z, z, 1, "Z coordinate." )

END_IMPLEMENT_STRUCT;
//-----------------------------------------------------------------------------
// TypeVector3
//-----------------------------------------------------------------------------
ConsoleType(Vector3, TypeVector3, Vector3, "")
ImplementConsoleTypeCasters(TypeVector3, Vector3)

ConsoleGetType( TypeVector3 )
{
    Vector3 *pt = (Vector3 *) dptr;
    static const U32 bufSize = 256;
    char* returnBuffer = Con::getReturnBuffer(bufSize);
    dSprintf(returnBuffer, bufSize, "%g %g %g", pt->x, pt->y, pt->z);
    return returnBuffer;
}

ConsoleSetType( TypeVector3 )
{
    if(argc == 1)
        dSscanf(argv[0], "%g %g %g", &((Vector3 *) dptr)->x, &((Vector3 *) dptr)->y, &((Vector3 *) dptr)->z);
    else if(argc == 3)
        *((Vector3 *) dptr) = Vector3(dAtof(argv[0]), dAtof(argv[1]), dAtof(argv[2]));
    else
        Con::printf("Vector3 must be set as { x, y, z } or \"x y z\"");
}
//-----------------------------------------------------------------------------
// Vector4
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( Vector4,
                  Vector4, ,
                  "" )

FIELD( x, x, 1, "X coordinate." )
FIELD( y, y, 1, "Y coordinate." )
FIELD( z, z, 1, "Z coordinate." )
FIELD( w, w, 1, "W coordinate." )
END_IMPLEMENT_STRUCT;
//-----------------------------------------------------------------------------
// TypeVector4
//-----------------------------------------------------------------------------
ConsoleType(Vector4, TypeVector4, Vector4, "")
ImplementConsoleTypeCasters(TypeVector4, Vector4)

ConsoleGetType( TypeVector4 )
{
    Vector4 *pt = (Vector4 *) dptr;
    static const U32 bufSize = 256;
    char* returnBuffer = Con::getReturnBuffer(bufSize);
    dSprintf(returnBuffer, bufSize, "%g %g %g %g", pt->x, pt->y, pt->z, pt->w);
    return returnBuffer;
}

ConsoleSetType( TypeVector4 )
{
    if(argc == 1)
    {
        dSscanf(argv[0], "%g %g %g %g",
                &((Vector4 *) dptr)->x,
                &((Vector4 *) dptr)->y,
                &((Vector4 *) dptr)->z,
                &((Vector4 *) dptr)->w);
    }
    else if(argc == 4)
    {
        *((Vector4 *) dptr) = Vector4(dAtof(argv[0]), dAtof(argv[1]), dAtof(argv[2]), dAtof(argv[3]));
    }
    else
    {
        Con::printf("Vector4 must be set as { x, y, z, w } or \"x y z w\"");
    }
}



//-----------------------------------------------------------------------------
// TypeRectangle
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( Rectangle,
                  Rectangle, ,
                  "" )

FIELD( x, x, 1, "Rectangle top-left corner position x" )
FIELD( y, y, 1, " Rectangle top-left corner position y" )
FIELD( width, width, 1, "Rectangle width." )
FIELD( height, height, 1, "Rectangle height." )

END_IMPLEMENT_STRUCT;

ConsoleType(Rectangle, TypeRectangle, Rectangle, "")
ImplementConsoleTypeCasters( TypeRectangle, Rectangle )

ConsoleGetType( TypeRectangle )
{
    Rectangle *rect = (Rectangle *) dptr;
    static const U32 bufSize = 256;
    char* returnBuffer = Con::getReturnBuffer(bufSize);
    dSprintf(returnBuffer, bufSize, "%g %g %g %g", rect->x, rect->y,
             rect->width, rect->height);
    return returnBuffer;
}

ConsoleSetType( TypeRectangle )
{
    if(argc == 1)
        dSscanf(argv[0], "%g %g %g %g", &((Rectangle *) dptr)->x, &((Rectangle *) dptr)->y,
                &((Rectangle *) dptr)->width, &((Rectangle *) dptr)->height);
        else if(argc == 4)
            *((Rectangle *) dptr) = Rectangle(dAtof(argv[0]), dAtof(argv[1]), dAtof(argv[2]), dAtof(argv[3]));
    else
        Con::printf("Rectangle must be set as { x, y, w, h } or \"x y w h\"");
}


//-----------------------------------------------------------------------------
// TypeRay
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( Ray,
                  Ray, ,
                  "" )

FIELD( position, position, 1, "Ray position (origin)" )
FIELD( direction, direction, 1, "Ray direction (normalized)" )

END_IMPLEMENT_STRUCT;

ConsoleType(Ray, TypeRay, Ray, "")
ImplementConsoleTypeCasters(TypeRay, Ray)

ConsoleGetType(TypeRay)
{
    Ray *ray = (Ray *) dptr;
    static const U32 bufSize = 256;
    char* returnBuffer = Con::getReturnBuffer(bufSize);

    dSprintf(returnBuffer, bufSize, "%g %g %g %g %g %g",
             ray->position.x,  ray->position.y,  ray->position.z,
             ray->direction.x, ray->direction.y, ray->direction.z);
    return returnBuffer;
}

ConsoleSetType(TypeRay)
{
    if(argc == 1)
    {
        // Wenn als einzelner String übergeben ("x y z dx dy dz")
        dSscanf(argv[0], "%g %g %g %g %g %g",
                &((Ray *) dptr)->position.x,  &((Ray *) dptr)->position.y,  &((Ray *) dptr)->position.z,
                &((Ray *) dptr)->direction.x, &((Ray *) dptr)->direction.y, &((Ray *) dptr)->direction.z);
    }
    else if(argc == 6)
    {
        ((Ray *) dptr)->position.x  = dAtof(argv[0]);
        ((Ray *) dptr)->position.y  = dAtof(argv[1]);
        ((Ray *) dptr)->position.z  = dAtof(argv[2]);
        ((Ray *) dptr)->direction.x = dAtof(argv[3]);
        ((Ray *) dptr)->direction.y = dAtof(argv[4]);
        ((Ray *) dptr)->direction.z = dAtof(argv[5]);
    }
    else
    {
        Con::printf("Ray must be set as { px, py, pz, dx, dy, dz } or \"px py pz dx dy dz\"");
    }
}

//-----------------------------------------------------------------------------
// TypeBoundingBox ("min.x min.y min.z max.x max.y max.z")
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( BoundingBox,
                  BoundingBox, ,
                  "" )

FIELD( min, min, 1, "point 1 min" )
FIELD( max, max, 1, "point 2 max" )

END_IMPLEMENT_STRUCT;

ConsoleType(BoundingBox, TypeBoundingBox, BoundingBox, "")
ImplementConsoleTypeCasters(TypeBoundingBox, BoundingBox)

ConsoleGetType(TypeBoundingBox)
{
    BoundingBox *box = (BoundingBox *) dptr;
    static const U32 bufSize = 256;
    char* returnBuffer = Con::getReturnBuffer(bufSize);

    // Gibt alle 6 Werte durch Leerzeichen getrennt aus
    dSprintf(returnBuffer, bufSize, "%g %g %g %g %g %g",
             box->min.x, box->min.y, box->min.z,
             box->max.x, box->max.y, box->max.z);
    return returnBuffer;
}

ConsoleSetType(TypeBoundingBox)
{
    if(argc == 1)
    {
        // Wenn als kompakter String übergeben: "minX minY minZ maxX maxY maxZ"
        dSscanf(argv[0], "%g %g %g %g %g %g",
                &((BoundingBox *) dptr)->min.x, &((BoundingBox *) dptr)->min.y, &((BoundingBox *) dptr)->min.z,
                &((BoundingBox *) dptr)->max.x, &((BoundingBox *) dptr)->max.y, &((BoundingBox *) dptr)->max.z);
    }
    else if(argc == 6)
    {
        // Wenn als 6 Einzelfelder übergeben
        ((BoundingBox *) dptr)->min.x = dAtof(argv[0]);
        ((BoundingBox *) dptr)->min.y = dAtof(argv[1]);
        ((BoundingBox *) dptr)->min.z = dAtof(argv[2]);
        ((BoundingBox *) dptr)->max.x = dAtof(argv[3]);
        ((BoundingBox *) dptr)->max.y = dAtof(argv[4]);
        ((BoundingBox *) dptr)->max.z = dAtof(argv[5]);
    }
    else
    {
        Con::printf("BoundingBox must be set as { minX, minY, minZ, maxX, maxY, maxZ } or \"minX minY minZ maxX maxY maxZ\"");
    }
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// TypeMatrix
//-----------------------------------------------------------------------------
IMPLEMENT_STRUCT( Matrix, Matrix, , "4x4 transformation matrix (column-major)" )
FIELD( m0,  m0,  1, "Component m0" )
FIELD( m4,  m4,  1, "Component m4" )
FIELD( m8,  m8,  1, "Component m8" )
FIELD( m12, m12, 1, "Component m12" )
FIELD( m1,  m1,  1, "Component m1" )
FIELD( m5,  m5,  1, "Component m5" )
FIELD( m9,  m9,  1, "Component m9" )
FIELD( m13, m13, 1, "Component m13" )
FIELD( m2,  m2,  1, "Component m2" )
FIELD( m6,  m6,  1, "Component m6" )
FIELD( m10, m10, 1, "Component m10" )
FIELD( m14, m14, 1, "Component m14" )
FIELD( m3,  m3,  1, "Component m3" )
FIELD( m7,  m7,  1, "Component m7" )
FIELD( m11, m11, 1, "Component m11" )
FIELD( m15, m15, 1, "Component m15" )
END_IMPLEMENT_STRUCT;



ConsoleType(Matrix, TypeMatrix, Matrix, "")
ImplementConsoleTypeCasters(TypeMatrix, Matrix)

ConsoleGetType(TypeMatrix)
{
    Matrix *mat = (Matrix *) dptr;
    static const U32 bufSize = 512;
    char* returnBuffer = Con::getReturnBuffer(bufSize);

    dSprintf(returnBuffer, bufSize,
             "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
             mat->m0, mat->m4, mat->m8,  mat->m12,
             mat->m1, mat->m5, mat->m9,  mat->m13,
             mat->m2, mat->m6, mat->m10, mat->m14,
             mat->m3, mat->m7, mat->m11, mat->m15);
    return returnBuffer;
}

ConsoleSetType(TypeMatrix)
{
    if(argc == 1)
    {
        dSscanf(argv[0], "%g %g %g %g %g %g %g %g %g %g %g %g %g %g %g %g",
                &((Matrix *) dptr)->m0, &((Matrix *) dptr)->m4, &((Matrix *) dptr)->m8,  &((Matrix *) dptr)->m12,
                &((Matrix *) dptr)->m1, &((Matrix *) dptr)->m5, &((Matrix *) dptr)->m9,  &((Matrix *) dptr)->m13,
                &((Matrix *) dptr)->m2, &((Matrix *) dptr)->m6, &((Matrix *) dptr)->m10, &((Matrix *) dptr)->m14,
                &((Matrix *) dptr)->m3, &((Matrix *) dptr)->m7, &((Matrix *) dptr)->m11, &((Matrix *) dptr)->m15);
    }
    else
    {
        Con::printf("Matrix must be set as a space-separated string of 16 float values.");
    }
}


