#include "console/engineAPI.h"
#include <console/consoleTypes.h>

    // class EmptyObject : public SimObject
    // {
    //     typedef SimObject Parent;
    //
    // public:
    //     DECLARE_CONOBJECT(EmptyObject);
    // };
    // IMPLEMENT_CONOBJECT(EmptyObject);
//--------------

struct Point2F{
    F32 x = 0;
    F32 y = 0;
};

class TestObj: public SimObject
{
    typedef SimObject Parent;
public:
    DECLARE_CONOBJECT(TestObj);
    F32 mX, mY, mZ;
    F64 mDouble;
    S32 mIndex;
    bool mBool;
    StringTableEntry mTestName;
    S32 mSlots[3];
    Vector<Point2F> mPoints;

    TestObj() {
        mX = mY = mZ = 0.f;
        mDouble = 0.f;
        mIndex = 0;
        mBool = false;
        mTestName = StringTable->insert("NoName");
        for (S32 i = 0; i < 3; i++) mSlots[i]=0;
    }

    static bool _setPointSize(void* obj,const char* , const char* data) {
        TestObj* object = static_cast<TestObj*>(obj);
        if (!object || !data) {
            Con::errorf("Failed to set pointSize!");
            return false;
        }
        S32 size = dAtoi(data);
        if ( size >= 0 ) {
            object->mPoints.setSize(size);
            dMemset(object->mPoints.address(), 0, object->mPoints.size() * sizeof(Point2F));
            Con::printf("New point size is: %d", size);
            //NOT! return true;
        }
        return false;
    }
    static const char *_getPointSize(void* obj, const char* data) {
        TestObj* object = static_cast<TestObj*>(obj);
        if (!object) return "";
        return Con::getIntArg(object->mPoints.size());
    }


    static void initPersistFields()
    {
        // Parent::initPersistFields();
        addField("x",     TypeF32,     Offset(mX, TestObj));
        addField("y",     TypeF32,     Offset(mY, TestObj));
        addField("z",     TypeF32,     Offset(mZ, TestObj));
        addField("testFloat", TypeF64,   Offset(mDouble, TestObj));
        addField("testInt",  TypeS32,    Offset(mIndex, TestObj));
        addField("testBool", TypeBool,   Offset(mBool, TestObj));
        addField("testString", TypeString, Offset(mTestName, TestObj));
        addField("testSlot", TypeS32, Offset(mSlots, TestObj), 3); //WARNING count is not validated!!!
        //----
        addProtectedField("pointSize", TypeS32, 0, &_setPointSize,&_getPointSize, "Set the point size (element count).");


    }

    void setPos(F32 x, F32 y, F32 z) {
        mX = x;
        mY = y;
        mZ = z;
    }
};

IMPLEMENT_CONOBJECT(TestObj);

DefineEngineMethod(TestObj, getPos, String, (), , "get the position") {
    // we do nothing special here
    StringBuilder str;
    str.format("%g %g %g", object->mX, object->mY, object->mZ);
    return Con::getStringArg(str.end());
}

DefineEngineMethod(TestObj, getX, F32, (), , "") {
  return object->mX;
}
DefineEngineMethod(TestObj, getY, F32, (), , "") {
    return object->mY;
}
DefineEngineMethod(TestObj, getZ, F32, (), , "") {
    return object->mZ;
}

DefineEngineMethod(TestObj, walk, void, (F32 x, F32 y, F32 z), , "Set point where to walk to") {
    // we do nothing special here
    object->setPos(x,y,z);
}

DefineEngineMethod(TestObj, setPoint, bool, (S32 index, F32 x, F32 y), , "Set point at index") {
    if (index < 0 || index >= object->mPoints.size()) return false;
    object->mPoints[index] = { x, y};
    return true;
}


DefineEngineMethod(TestObj, getPoint, Vector<F32>, (S32 index), , "Get point at index") {
    if (index < 0 || index >= object->mPoints.size()) return {};
    Vector<F32> tmpVector;
    tmpVector.clear();
    tmpVector.push_back(object->mPoints[index].x);
    tmpVector.push_back(object->mPoints[index].y);
    return tmpVector;
}

DefineEngineMethod(TestObj, pushPoint, bool, (S32 index), , "push point at index to x,y") {
    if (index < 0 || index >= object->mPoints.size()) return false;

    object->mX =  object->mPoints[index].x;
    object->mY = object->mPoints[index].y;
    return true;
}

// this is executed at the same speed as .pushPoint. so the VM does NOT cache %this object in functions
// Console value need a pointer field
DefineEngineFunction(Test_PushPoint, bool, (S32 pId, S32 index), , "same as pushpoint but as function") {
    TestObj* object = static_cast<TestObj*>(Sim::findObject(pId));
    if (!object || index < 0 || index >= object->mPoints.size()) return false;
    object->mX =  object->mPoints[index].x;
    object->mY = object->mPoints[index].y;
    return true;
}
