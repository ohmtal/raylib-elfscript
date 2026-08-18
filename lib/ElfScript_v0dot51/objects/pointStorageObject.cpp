//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// ElfScript PointStorageObject
// The idea is we have a virutally unlimited (not really - 1000000 is the
// limit) Point Storage.
// Store a VectorType with 4 Points inside a Vector
// this can be used for a Vector2/3/4, Rectangle or UV
//-----------------------------------------------------------------------------
// applyMathOnPoints give special power to modify points in one call using tinyexpr.
//-----------------------------------------------------------------------------
// Examples:
//  - store points for custom particles
//  - results of a pathfind.
//  and much more ;)
//-----------------------------------------------------------------------------
// Example usage:
// Create a new Storage with space for 1k points:
//     new PointStorageObject(sto) { storageSize = 1000; };
//     print(sto.storageSize);
// set the point at index 0 to {10,20,30,40}
//     sto.setPointVec(0,{10,20,30,40});
//     print(sto.getPointVec(0));
// set the current x,y,z,w values from the storage at index 0
//     sto.fetchPoint(0);
//     sto.dumpFields();
// modify y
//     sto.points[1] = 66.67;
// push it to storage at index 0
//     sto.pushPoint(0);
//     print(sto.getPointVec(0));
// set new values at x,y,z,w
//     sto.setPos(11,12,13,14);
// push them to storage at index 1
//     sto.pushPoint(1);
//     print(sto.getPointVec(1));
// for (%i = 0; %i < 1000; %i++) { sto.setPoint(%i, getRandomF(1.0),getRandomF(1.0),getRandomF(1.0),getRandomF(1.0)); } echo("DONE!");
// for (%i = 0; %i < 1000; %i++) { print("#",%i SPC sto.getPointVec(%i)); }
// for (%i = 0; %i < 1000; %i++) { sto.fetchPoint(%i); echo("#",%i SPC sto.points[0] SPC sto.points[1] SPC sto.points[3]idth SPC sto.height); }
// for (%i = 0; %i < 1000; %i++) { echo(sto.getPointx(%i) SPC sto.getPointy(%i) SPC sto.getPointz(%i) SPC sto.getPointw(%i)); }
//-----------------------------------------------------------------------------
#include "console/engineAPI.h"
#include "console/consoleTypes.h"
#include "console/simFieldDictionary.h"
#include "math/mMathRand.h"
#include "math/mMathFn.h"
#include "ext/tinyexpr.h"

// //  nice but slower #include "console/localVar.h"

// ------------ Vector2 helper ----------------
inline float lengthSquaredXY(const F32 x, const F32 y) {
    return x * x + y * y;
}

inline float lengthXY(const F64 x, const F64 y) {
    return ElfMath::mSqrt(lengthSquaredXY(static_cast<F32>(x) ,static_cast<F32>(y) ));
}

inline float lengthXY(const F32 x, const F32 y) {
    return ElfMath::mSqrt(lengthSquaredXY(x,y));
}

void normalizeXY(F32& x, F32& y) {
    float len = lengthXY(x,y);
    if (len > 0.0f) {
        x /= len;
        y /= len;
    }
}


// ------------ tinyexpr wrapped random: -------------------
static double tinyexpr_randf_0() {
    return (double)ElfMath::mRandF();
}
static double tinyexpr_randf_1(double min) {
    return (double)ElfMath::mRandF((F32) min, 0.f);
}
static double tinyexpr_randf_2(double min, double max) {
    return (double)ElfMath::mRandF((F32)min, (F32)max);
}

// For accessing current object from tinyexpr function
class PointStorageObject;
static PointStorageObject* sCurrentInstance = nullptr;

class PointStorageObject: public SimObject
{
    typedef SimObject Parent;
public:
    DECLARE_CONOBJECT(PointStorageObject);
    ConsoleVector mVector;

    /*
     * Storing Point in a vector Vector implementation
     *
     * property pointSize set/get the size of this vector to speed up access
     *          i fo not use push at mPoints this should be pretty fast
     * setPoint store x,y at a index in this vector
     * storePoint
     * fetchPoint
     */
    Vector<ConsoleVector> mPoints;

    // math (tinyexpr) operation direct access:
    F32 mtX, mtY, mtZ, mtW;

    // -------------------------------------------------------------------------
    PointStorageObject() {
        // mVector.points[0] = mVector.points[1] = mVector.points[2] = mVector.points[3] = 0.f;
        mVector = {0};
        mtX =  mtY = mtZ =  mtW = 0.f;
    }

    // -------------------------------------------------------------------------
    bool onAdd() override {
        populate();
        return Parent::onAdd();
    }
    // -------------------------------------------------------------------------

    void setStorageSize(U32 size) {
        if ( size <= 1000000) {
            U32 oldSize = this->mPoints.size();
            this->mPoints.setSize(size);
            if (size > oldSize) {
                U32 newElements = size - oldSize;
                ConsoleVector* startOfNewData = this->mPoints.address() + oldSize;
                dMemset(startOfNewData, 0, newElements * sizeof(ConsoleVector));
            }
        } else {
            Con::errorf("setStorageSize value too high! max: 1000000, send:%u", size);
        }
    }


    static bool _setStorageSize(void* obj,const char* , const char* data) {
        PointStorageObject* object = static_cast<PointStorageObject*>(obj);
        if (!object || !data) {
            Con::errorf("Failed to set pointSize!");
            return false;
        }
        object->setStorageSize(dAtoui(data));
        return false;
    }
    static const char *_getStorageSize(void* obj, const char* data) {
        PointStorageObject* object = static_cast<PointStorageObject*>(obj);
        if (!object) return "";
        return Con::getIntArg(object->mPoints.size());
    }

    // -------------------------------------------------------------------------

    static void initPersistFields()
    {
        Parent::initPersistFields();

        addField("point", TypeVector,  Offset(mVector, PointStorageObject));
        addField("x",     TypeF32,     Offset(mVector.points[0], PointStorageObject));
        addField("y",     TypeF32,     Offset(mVector.points[1], PointStorageObject));
        addField("z",     TypeF32,     Offset(mVector.points[2], PointStorageObject));
        addField("w",     TypeF32,     Offset(mVector.points[3], PointStorageObject));

        // Rectangle aliases
        addField("width",     TypeF32,     Offset(mVector.points[2], PointStorageObject),  "alias for z");
        addField("height",    TypeF32,     Offset(mVector.points[3], PointStorageObject), "alias for w - yes w.");

        // Color aliases
        addField("r",     TypeF32,     Offset(mVector.points[0], PointStorageObject), "alias for x");
        addField("g",     TypeF32,     Offset(mVector.points[1], PointStorageObject), "alias for y");
        addField("b",     TypeF32,     Offset(mVector.points[2], PointStorageObject), "alias for z");
        addField("a",     TypeF32,     Offset(mVector.points[3], PointStorageObject), "alias for w");

        //----
        addProtectedField("storageSize", TypeU32, 0, &_setStorageSize,&_getStorageSize, "Set the storage size (how many points we can work with) Max:1000000.");


    }

    // -------------------------------------------------------------------------
    void setPos(F32 x, F32 y, F32 z, F32 w) {
        mVector.points[0] = x;
        mVector.points[1] = y;
        mVector.points[2] = z;
        mVector.points[3] = w;
    }

    // -------------------------------------------------------------------------
    void setPos(const ConsoleVector& vec4) {
        this->mVector = vec4;
    }


    // -------------------------------------------------------------------------
    /*
     * applyMathOnPoints
     * - Using tinyexpr
     * - Format each statement separated by ";" => "x+5; y*2; z; w"
     */
    bool applyMathOnPoints(String Expr, U32 startIndex = 0, U32 endIndex = 0) {
        if (endIndex == 0) endIndex = mPoints.size() -1;
        if ( endIndex >= mPoints.size()
            || startIndex >= mPoints.size()
            || startIndex > endIndex
        ) {
            Con::errorf("Invalid Range parameter applyMathOnPoints ( %u .. %u )", startIndex, endIndex);
            return false;
        }



        Vector<String> expressions;
        Expr.split(";", expressions);

        // special pathes !!
        if (expressions.size() == 1) {
            String trimmedExpr = Expr.trim();
            if (trimmedExpr.equal("normalizeXY()", String::NoCase)) {
                for (U32 i = startIndex; i <= endIndex; i++) {
                    F32 x = static_cast<F32>(mPoints[i].points[0]);
                    F32 y = static_cast<F32>(mPoints[i].points[1]);
                    normalizeXY( x,y );
                    mPoints[i].points[0] = static_cast<F32>(x);
                    mPoints[i].points[1] = static_cast<F32>(y);
                }
                return true;
            }
        }

        if (expressions.size() != 4) {

            Con::errorf("applyMathOnPoints: Expected 4 expressions separated by ';' (e.g., 'x+1; y; z; w')");
            return false;
        }


        sCurrentInstance = this;
        const int paramCount = 7;
        te_variable vars[paramCount] = {
            {"x", &mtX, TE_VARIABLE},
            {"y", &mtY, TE_VARIABLE},
            {"z", &mtZ, TE_VARIABLE},
            {"w", &mtW, TE_VARIABLE},
            {"randf", (const void*)&tinyexpr_randf_0, TE_FUNCTION0},
            {"randf1", (const void*)&tinyexpr_randf_1, TE_FUNCTION1},
            {"randf2", (const void*)&tinyexpr_randf_2, TE_FUNCTION2}
        };

        int err;
        te_expr* exprX = te_compile(expressions[0].c_str(), vars, paramCount, &err);
        te_expr* exprY = te_compile(expressions[1].c_str(), vars, paramCount, &err);
        te_expr* exprZ = te_compile(expressions[2].c_str(), vars, paramCount, &err);
        te_expr* exprW = te_compile(expressions[3].c_str(), vars, paramCount, &err);

        if (!exprX || !exprY || !exprZ || !exprW) {
            Con::errorf("applyMathOnPoints: Formula compilation failed!");
            if (exprX) te_free(exprX);
            if (exprY) te_free(exprY);
            if (exprZ) te_free(exprZ);
            if (exprW) te_free(exprW);
            return false;
        }

        for (U32 i = startIndex; i <= endIndex; i++) {
            ConsoleVector& p = mPoints[i];

            mtX = p.points[0];
            mtY = p.points[1];
            mtZ = p.points[2];
            mtW = p.points[3];

            mtX = (F32)te_eval(exprX);
            mtY = (F32)te_eval(exprY);
            mtZ = (F32)te_eval(exprZ);
            mtW = (F32)te_eval(exprW);

            p.points[0] = mtX;
            p.points[1] = mtY;
            p.points[2] = mtZ;
            p.points[3] = mtW;
        }

        sCurrentInstance = nullptr;

        te_free(exprX);
        te_free(exprY);
        te_free(exprZ);
        te_free(exprW);

        return true;
    }


    // -------------------------------------------------------------------------
    // it's slower then fetch/store so i remove it again!
    // // **** direct local var access !!!! - i ignore fails here ...***
    // void getPosByReference(const char* varX,const char* varY,const char* varZ = nullptr,const char* varW = nullptr) {
    //     ElfScript::setLocalFloat(varX, mVector.points[0]);
    //     ElfScript::setLocalFloat(varY, mVector.points[1]);
    //     if (varZ) ElfScript::setLocalFloat(varZ, mVector.points[2]);
    //     if (varW) ElfScript::setLocalFloat(varW, mVector.points[3]);
    // }
    // // **** direct local var access for points !!!! - i ignore fails here ...***
    // bool getPointByReference(U32 index, const char* varX,const char* varY,const char* varZ = nullptr,const char* varW = nullptr) {
    //     if ( index >= this->mPoints.size()) return false;
    //     ElfScript::setLocalFloat(varX, this->mPoints[index].points[0]);
    //     ElfScript::setLocalFloat(varY, this->mPoints[index].points[1]);
    //     if (varZ) ElfScript::setLocalFloat(varZ, this->mPoints[index].points[2]);
    //     if (varW) ElfScript::setLocalFloat(varW, this->mPoints[index].points[3]);
    //     return true;
    // }
    // // **** direct local var access for points !!!! - i ignore fails here ...***
    // bool setPointByReference(U32 index, const char* varX,const char* varY,const char* varZ = nullptr,const char* varW = nullptr) {
    //     if ( index >= this->mPoints.size()) return false;
    //     this->mPoints[index].points[0] = ElfScript::getLocalFloat(varX);
    //     this->mPoints[index].points[1] = ElfScript::getLocalFloat(varY);
    //     if (varZ) this->mPoints[index].points[2] = ElfScript::getLocalFloat(varZ);
    //     if (varW) this->mPoints[index].points[3] = ElfScript::getLocalFloat(varW);
    //     return true;
    // }
    // -------------------------------------------------------------------------
    void write(Stream &stream, U32 tabStop, U32 flags) override {
        // Parent::write >>>>>>>>>>>>>>>>>>>>>>>>>>
        if( !getCanSave() && !( flags & IgnoreCanSave ) )
            return;

        // Only output selected objects if they want that.
        if((flags & SelectedOnly) && !isSelected())
            return;

        stream.writeTabs(tabStop);
        char buffer[1024];
        dSprintf(buffer, sizeof(buffer), "new %s(%s) {\r\n", getClassName(), getName() && !(flags & NoName) ? getName() : "");
        stream.write(dStrlen(buffer), buffer);
        writeFields(stream, tabStop + 1);

        // <<<<<<<<<<<<<<<<<<<<<<<< Parent::write
// mhhhh

        S32 count = this->mPoints.size();
        dSprintf(buffer, sizeof(buffer), "TypeS32 _populate = %d;\r\n", count); //magic populate ^^
        stream.writeTabs(tabStop);
            stream.write(dStrlen(buffer), buffer);
        for (S32 i = 0; i < count; i++) {
            ConsoleVector vec4 = this->mPoints[i];
            dSprintf(buffer, sizeof(buffer), "_p[%d] = { %g, %g, %g, %g};\r\n",i, vec4.points[0], vec4.points[1], vec4.points[2], vec4.points[3] );
            stream.writeTabs(tabStop);
            stream.write(dStrlen(buffer), buffer);
        }

        stream.writeTabs(tabStop);
        stream.write(4, "};\r\n");
    }

    // -------------------------------------------------------------------------
    // set the point in the Point Storage at index by Vector (String)
    bool setPointVec( U32 index, String strVector ) {
        if ( index >= this->mPoints.size()) return false;
        ConsoleVector vec4;
        dSscanf(strVector.c_str(), "%g %g %g %g",&vec4.points[0], &vec4.points[1], &vec4.points[2], &vec4.points[3]);
        this->mPoints[index] = vec4;
        return true;
    }

    // -------------------------------------------------------------------------
    // onAdd we check if we need to populate ....
    void populate() {
        bool test = false;

        if (test) {
            Con::printSeparator();
            Con::printf(" populate [id:%d] >>>>", this->getId());
        }

        if (this->mPoints.size() == 0) {
            if (test) Con::warnf("populate with a empty pointStorage!");
            return;
        }

        SimFieldDictionary* dict = getFieldDictionary();
        if (!dict) {
            if (test) Con::infof(" populate [id:%d] no SimFieldDictionary found...", this->getId());
            return; //nothing here
        }

        S32 count =0;
        StringTableEntry fieldName = nullptr;
        SimFieldDictionary::Entry* entry = nullptr;
        fieldName = StringTable->insert( "_populate" );
        entry = dict->findDynamicField(fieldName);
        if (!entry) {
             if (test) Con::printf(" populate [id:%d] no _populate field found!", this->getId());
            // we have no populate exit here
            return;
        }
        count = entry->mValue.getInt();
        if (count != this->mPoints.size()) {
            Con::errorf("Populate [id:%d] failed size missmatch! (%d!=%d)", this->getId(), count, this->mPoints.size());
            return;
        }
        if (test) Con::printf("Populate says we should store %d points.", count);
        if (!test) dict->setFieldValue(fieldName, nullptr); //pop _populate

        char buffer[128];
        String vec;

        for (S32 index = 0; index < count; index++) {
            dSprintf(buffer, sizeof(buffer), "_p%d", index);
            fieldName = StringTable->insert( buffer ) ;
            entry = dict->findDynamicField(fieldName);
            if (!entry) {
                Con::errorf("populate [id:%d] : No point found at %d", this->getId(), index);
            } else {
                vec = entry->mValue.getString();
                if (test) Con::printf("populate [id:%d] : _p%d = %s", this->getId(), index, vec.c_str());
                this->setPointVec(index, vec);
                if (!test) dict->setFieldValue(fieldName, nullptr); // pop _pXX
            }
        }

        // getFieldDictionary()->findDynamicField( strFieldName )
        // if (!isField("_populate", ))


        if (test) {
            Con::printf(" <<<< populate");
            Con::printf(" <<<< populate [id:%d]", this->getId());
            Con::printSeparator();
        }
    }
    // -------------------------------------------------------------------------



};

IMPLEMENT_CONOBJECT(PointStorageObject);

// ---------- get/set Vector String ----------
DefineEngineMethod(PointStorageObject, getPosVec, ConsoleVector, (), , "get the position as Vector ") {
    return object->mVector;
}
DefineEngineMethod(PointStorageObject, setPosVec, void, (ConsoleVector vector), , "set the position by Vector (String)") {
       object->mVector = vector;
}

// DefineEngineMethod(PointStorageObject, getPosByReference, void,
//                    (const char* varX, const char* varY, const char* varZ, const char* varW ),("","")
//                    , "set the position by by Referency on up to 4 Variables\n"
//                      "NOTE: the variables must exists before this is called it does NOT create them."
// ) {
//     object->getPosByReference(varX, varY, varZ, varW);
// }


// ---------- set Pos by float's ----------
DefineEngineMethod(PointStorageObject, setPos, void, (F32 x, F32 y, F32 z, F32 w),(0.f,0.f) ,
                   "Set position by method ") {
    object->setPos(x,y,z,w);
}
DefineEngineMethod(PointStorageObject, normalizeXZ, void, (), ,
                   "normalize the current position") {
    normalizeXY(object->mVector.points[0],object->mVector.points[1]);
}
DefineEngineMethod(PointStorageObject, getLen, F32, (), ,
                   "len of current position") {
    return lengthXY( object->mVector.points[0], object->mVector.points[1]);
}
// -------------------------------------
// ---------- mPoints storage ----------
DefineEngineMethod(PointStorageObject, setPoint, bool, (U32 index, F32 x, F32 y, F32 z, F32 w),(0.f, 0.f) ,
            "Set a  point at index in the point storage.") {
    if ( index >= object->mPoints.size()) return false;
    object->mPoints[index] = { x, y, z, w};
    return true;
}

// THIS IS SLOWER  then fetch / store !!!!
// DefineEngineMethod(PointStorageObject, getPointByReference, void,
//                    (U32 index,const char* varX, const char* varY, const char* varZ, const char* varW ),("","")
//                    , "set the point at index  by Reference to 2-4 Variables\n"
//                    "NOTE: the variables must exists before this is called it does NOT create them."
// ) {
//     object->getPointByReference(index,varX, varY, varZ, varW);
// }
// DefineEngineMethod(PointStorageObject, setPointByReference, void,
//                    (U32 index,const char* varX, const char* varY, const char* varZ, const char* varW ),("","")
//                    , "get the point at index  by Reference from 2-4 Variables\n"
//                    "NOTE: the variables must exists before this is called it does NOT create them."
// ) {
//     object->setPointByReference(index,varX, varY, varZ, varW);
// }

DefineEngineMethod(PointStorageObject, getPointX, F32, (U32 index),
                   , "get the point.points[0] from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return 0.f;
    return (object->mPoints[index].points[0]);
}
DefineEngineMethod(PointStorageObject, getPointY, F32, (U32 index),
                   , "get the point.points[0] from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return 0.f;
    return (object->mPoints[index].points[1]);
}
DefineEngineMethod(PointStorageObject, getPointZ, F32, (U32 index),
                   , "get the point.points[2] from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return 0.f;
    return (object->mPoints[index].points[2]);
}
DefineEngineMethod(PointStorageObject, getPointW, F32, (U32 index),
                   , "get the point.points[3] from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return 0.f;
    return (object->mPoints[index].points[3]);
}
DefineEngineMethod(PointStorageObject, setPointX, bool, (U32 index, F32 value),
                   , "set the point.points[0] from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return false;
    object->mPoints[index].points[0] = value;
    return true;
}
DefineEngineMethod(PointStorageObject, setPointY, bool, (U32 index, F32 value),
                   , "set the point.points[1] from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return false;
    object->mPoints[index].points[1] = value;
    return true;
}
DefineEngineMethod(PointStorageObject, setPointZ, bool, (U32 index, F32 value),
                   , "set the point.points[2] from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return false;
    object->mPoints[index].points[2] = value;
    return true;
}
DefineEngineMethod(PointStorageObject, setPointW, bool, (U32 index, F32 value),
                   , "set the point.points[2] from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return false;
    object->mPoints[index].points[3] = value;
    return true;
}

DefineEngineMethod(PointStorageObject, getPointVec, ConsoleVector, (U32 index),
                   , "get the point from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return {0};
    return object->mPoints[index];
}
DefineEngineMethod(PointStorageObject, setPointVec, bool, ( U32 index, ConsoleVector vec4), ,
                   "set the point in the Point Storage at index by Vector (String)") {
    if ( index >= object->mPoints.size()) return false;

    object->mPoints[index] = vec4;
    return true;


}

DefineEngineMethod(PointStorageObject, getPoint2Vec, String, (U32 index),
                   , "get the point xy from the point storage at index as Vector (String)") {
    if ( index >= object->mPoints.size()) return "";
    ConsoleVector vec4 = object->mPoints[index];
    StringBuilder str;
    str.format("%g %g", vec4.points[0], vec4.points[1]);
    return Con::getStringArg(str.end());
}
DefineEngineMethod(PointStorageObject, setPoint2Vec, bool, ( U32 index, String strVector), ,
                   "set the point xy in the Point Storage at index by Vector (String)") {
    if ( index >= object->mPoints.size()) return false;
    F32 x,y;
    dSscanf(strVector.c_str(), "%g %g",&x, &y);
    object->mPoints[index].points[0] = x;
    object->mPoints[index].points[1] = y;
    return true;
}
// ---------- mPoints storage from/to objects position ----------
DefineEngineMethod(PointStorageObject, storePoint, bool, (U32 index), ,
                   "store the current values x,y,z,w, to the point storage") {
    if ( index >= object->mPoints.size()) return false;

    object->mPoints[index] = object->mVector;

    return true;
}

DefineEngineMethod(PointStorageObject, fetchPoint, bool, (U32 index), ,
                   "fetch the point from the point storage at index to the current values x,y,z,w") {
    if ( index >= object->mPoints.size()) return false;

    object->setPos( object->mPoints[index] );

    return true;
}

// ---------- mPoints storage tinyexpr ----------
// Test:
//
/*
function PointMathTest() {
if (!isObject(sto)) new PointStorageObject(sto) { storageSize = 1000; };
sto.applyMathOnPoints("x+3.14; sin(x);randf1(1.0);w");
for (%i = 0; %i < 1000; %i++) { echo(sto.getPointVec(%i));}
}
*/
DefineEngineMethod(PointStorageObject, applyMathOnPoints, bool, (String Expr, U32 startIndex, U32 endIndex),(0,0)
        ,"Apply a Math expression on point Storage.\n"
        "expected format: \"x+5; y*2; z; w\" separated by ';'\n"
        "this execute 4 statements. one for each field. "
        "abs (calls to fabs), acos, asin, atan, atan2, ceil, cos, cosh, exp, floor, ln (calls to log), log (calls to log10 by default, see below), log10, pow, sin, sinh, sqrt, tan, tanh\n"
        "Random: randf(), randf1(5.0), randf2(1.0,2.0)\n"
        "Example ranomize all: sto.applyMathOnPoints(\"mrandf(),mrandf(),mrandf(),mrandf()\");"
        "Special one parameter expression: \n"
        "  normalizeXY => applyMathOnPoints(\"normalizeXY()\");"
        ) {
    return object->applyMathOnPoints( Expr, startIndex, endIndex);
}
