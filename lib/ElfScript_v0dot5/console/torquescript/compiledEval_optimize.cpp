//-----------------------------------------------------------------------------
// Copyright (c) 2013 GarageGames, LLC
// Copyright (c) 2015 Faust Logic, Inc.
// Copyright (c) 2021 TGEMIT Authors & Contributors
// Copyright (c) 2026 Thomas Hühn (XXTH)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------

#include "platform/platform.h"

#include "ast.h"
#include "compiler.h"

#include "core/strings/stringUnit.h"
#include "console/consoleInternal.h"

#include "console/simBase.h"
// #include "sim/netStringTable.h"
#include "console/stringStack.h"
#include "core/util/messaging/message.h"
#include "core/frameAllocator.h"

#include "console/returnBuffer.h"
#include "console/consoleValueStack.h"
// #include "console/telnetDebugger.h"


using namespace Compiler;

//XXTH macro to pop stk
#define POP_STK() {  _STK--; }
#define PUSH_STK() {  _STK++; }

enum EvalConstants
{
   MaxStackSize = 1024,
   FieldBufferSizeString = 2048,
   FieldBufferSizeNumeric = 128,
   ConcatBufferInitialSize = 8192,
   MethodOnComponent = -2
};

/// Frame data for a foreach/foreach$ loop.
struct IterStackRecord
{
   /// If true, this is a foreach$ loop; if not, it's a foreach loop.
   U32 mMode; //1=string, 2, 102=Range, 0(default) = SimObject

   /// True if the variable referenced is a global
   bool mIsGlobalVariable;

   union
   {

      /// The iterator variable if we are a global variable
      Dictionary::Entry* mVariable;

      /// The register variable if we are a local variable
      S32 mRegister;
   } mVar;

   /// Information for an object iterator loop.
   struct ObjectPos
   {
      /// The set being iterated over.
      SimSet* mSet;

      /// Current index in the set.
      U32 mIndex;
   };

   /// Information for a string iterator loop.
   struct StringPos
   {
      /// The raw string data on the string stack.
      const char* mString;

      /// Current parsing position.
      U32 mIndex;
   };

   struct RangePos
   {
      S32  mStart; // first number (included)
      S32  mEnd;  // last number (included)
      S32  mInc;  // -1, +1 maybe we can add STEP :)
      S32  mStop; //we stop at ...
   };

   union
   {
      ObjectPos mObj;
      StringPos mStr;
      RangePos  mRange;
   } mData;
};

ConsoleValueStack<4096> gCallStack;

StringStack STR;

IterStackRecord iterStack[MaxStackSize];
U32 _ITER = 0;    ///< Stack pointer for iterStack.

// #define POP_ITER() { \
// --_ITER;                \
// --iterDepth;            \
// POP_STK();              \
// if (iterStack[_ITER].mMode == 2) { \
//       POP_STK();        \
// }                       \
// iterStack[_ITER].mMode = 0;   \
// } \
//

#define POP_ITER() { \
--_ITER;                \
--iterDepth;            \
POP_STK();              \
iterStack[_ITER].mMode = 0;   \
} \

#define CLEAR_ITER_STATE() \
do { \
      while (iterDepth > 0) \
      { \
            POP_ITER(); \
      } \
} while(0)




ConsoleValue stack[MaxStackSize];
S32 _STK = 0;

ReturnBuffer retBuffer;

char *getReturnBuffer(U32 bufferSize)
{
   return retBuffer.getBuffer(bufferSize);
}

const char* tsconcat(const char* strA, const char* strB, S32& outputLen)
{
   S32 lenA = dStrlen(strA);
   S32 lenB = dStrlen(strB);

   S32 len = lenA + lenB + 1;

   char* concatBuffer = (char*)dMalloc(len);

   concatBuffer[len - 1] = '\0';
   memcpy(concatBuffer, strA, lenA);
   memcpy(concatBuffer + lenA, strB, lenB);

   outputLen = lenA + lenB;
   return concatBuffer;
}

namespace Con
{
   // Current script file name and root, these are registered as
   // console variables.
   extern StringTableEntry gCurrentFile;
   extern StringTableEntry gCurrentRoot;
   extern S32 gObjectCopyFailures;
}

namespace Con
{
   const char *getNamespaceList(Namespace *ns)
   {
      U32 size = 1;
      Namespace * walk;
      for (walk = ns; walk; walk = walk->mParent)
         size += dStrlen(walk->mName) + 4;
      char *ret = getReturnBuffer(size);
      ret[0] = 0;
      for (walk = ns; walk; walk = walk->mParent)
      {
         dStrcat(ret, walk->mName, size);
         if (walk->mParent)
            dStrcat(ret, " -> ", size);
      }
      return ret;
   }
}

// -----------------------------------------------------------------------------
static void stackFieldComponent(SimObject* object, StringTableEntry field, const char* array
      , StringTableEntry subField, ConsoleValue* pStack, S32 currentLocalRegister)
{

      /*ConsoleValueType*/ S32 targetType = pStack->type;

      static ConsoleValue srcStoreValue = {};
      ConsoleValue* srcValue = nullptr;
      // Local Variable

      if (object && field) {
#ifdef ENABLE_CONSOLE_VECTOR
            srcStoreValue.type = ConsoleValueType::cvVector;
#else
            srcStoreValue.type = ConsoleValueType::cvString;
#endif
            srcValue = &srcStoreValue;
            object->stackDataField(field, array, srcValue); //get the current
            // Con::debugf("srcStoreValue.type is: %d value: %s", srcStoreValue.type, srcStoreValue.getString());
      } else if (currentLocalRegister != -1) {
            srcValue = Script::gEvalState.getLocalConsoleValue(currentLocalRegister);
      } else if (Script::gEvalState.currentVariable) {
            srcValue = Script::gEvalState.getConsoleValue();
      }

      // no srcValue empty target pStack
      if (!srcValue) {
            pStack->setEmptyString();
            return;
      }


      // -----
      static const StringTableEntry xyzw[] =
      {
            StringTable->insert("x"),
            StringTable->insert("y"),
            StringTable->insert("z"),
            StringTable->insert("w")
      };

      //XXTH added
      static const StringTableEntry wh[] =
      {
            StringTable->insert("width"),
            StringTable->insert("height")
      };


      static const StringTableEntry rgba[] =
      {
            StringTable->insert("r"),
            StringTable->insert("g"),
            StringTable->insert("b"),
            StringTable->insert("a")
      };
      // -----
      F64 targetValue = 0.f;

      int componentIndex = -1;
      if      (subField == xyzw[0] || subField == rgba[0]) componentIndex = 0;
      else if (subField == xyzw[1] || subField == rgba[1]) componentIndex = 1;
      else if (subField == xyzw[2] || subField == rgba[2] || subField == wh[0]) componentIndex = 2;
      else if (subField == xyzw[3] || subField == rgba[3] || subField == wh[1]) componentIndex = 3;

      if (componentIndex < 0) {
            pStack->setEmptyString();
            return;
      }

#ifdef  ENABLE_CONSOLE_VECTOR
       if (srcValue->type == cvVector) {
             targetValue = (F64)srcValue->v.points[componentIndex];
       } else
#endif
      {
            const char* srcStr = srcValue->getString();
            const char* pStr = srcStr;
            int compCount = 0;

            const char* tokenStart = nullptr;
            size_t tokenLen = 0;

            while (*pStr != '\0') {
                  while (*pStr == ' ' || *pStr == '\t' || *pStr == '\n' || *pStr == '\r') {
                        pStr++;
                  }
                  if (*pStr == '\0') break;

                  if (compCount == componentIndex) {
                        tokenStart = pStr;
                  }

                  while (*pStr != '\0' && *pStr != ' ' && *pStr != '\t' && *pStr != '\n' && *pStr != '\r') {
                        pStr++;
                  }

                  if (compCount == componentIndex) {
                        tokenLen = pStr - tokenStart;
                        break;
                  }

                  compCount++;
            }

            if (tokenLen > 0) {
                  char tokenBuffer[32];
                  if (tokenLen >= 32) tokenLen = 31;

                  memcpy(tokenBuffer, tokenStart, tokenLen);
                  tokenBuffer[tokenLen] = '\0';

                  targetValue = dAtof(tokenBuffer);
            } else {
                  targetValue = 0.0;
            }

      }

      switch ( targetType ) {
            case cvInteger: pStack->setFastInt(static_cast<S64>(targetValue)); break;
            case cvFloat: pStack->setFastFloat(targetValue); break;
            default: pStack->setFloat(targetValue); break;
      }

}

// -----------------------------------------------------------------------------

// replaced by stackFieldComponent
// static void getFieldComponent(SimObject* object, StringTableEntry field, const char* array, StringTableEntry subField, char val[], S32 currentLocalRegister)
// {
//    const char* prevVal = NULL;
//
//    if (object && field)
//       prevVal = object->getDataField(field, array);
//    else if (currentLocalRegister != -1)
//       prevVal = Script::gEvalState.getLocalStringVariable(currentLocalRegister);
//    else if (Script::gEvalState.currentVariable)
//       prevVal = Script::gEvalState.getStringVariable();
//
//    // Make sure we got a value.
//    if (prevVal && *prevVal)
//    {
//       static const StringTableEntry xyzw[] =
//       {
//          StringTable->insert("x"),
//          StringTable->insert("y"),
//          StringTable->insert("z"),
//          StringTable->insert("w")
//       };
//
//       //XXTH added
//       static const StringTableEntry wh[] =
//       {
//             StringTable->insert("width"),
//             StringTable->insert("height")
//       };
//
//
//       static const StringTableEntry rgba[] =
//       {
//          StringTable->insert("r"),
//          StringTable->insert("g"),
//          StringTable->insert("b"),
//          StringTable->insert("a")
//       };
//
//       // Translate xyzw and rgba into the indexed component
//       // of the variable or field.
//       if (subField == xyzw[0] || subField == rgba[0])
//          dStrcpy(val, StringUnit::getUnit(prevVal, 0, " \t\n"), 128);
//
//       else if (subField == xyzw[1] || subField == rgba[1])
//          dStrcpy(val, StringUnit::getUnit(prevVal, 1, " \t\n"), 128);
//
//       else if (subField == xyzw[2] || subField == rgba[2] || subField == wh[0])
//          dStrcpy(val, StringUnit::getUnit(prevVal, 2, " \t\n"), 128);
//
//       else if (subField == xyzw[3] || subField == rgba[3] || subField == wh[1])
//          dStrcpy(val, StringUnit::getUnit(prevVal, 3, " \t\n"), 128);
//
//       else
//          val[0] = 0;
//    }
//    else
//       val[0] = 0;
// }
// -----------------------------------------------------------------------------
// called at %foo.x = 1.0;
static void pushFieldComponent(SimObject* object, StringTableEntry field, const char* array
      , StringTableEntry subField, ConsoleValue* pSrcStack, S32 currentLocalRegister)
{
      static ConsoleValue dstStoreValue = {};
      ConsoleValue *dstValue = nullptr;

      if (object && field) {
            // not! dstStoreValue.type = ConsoleValueType::cvVector;
            dstStoreValue.type = ConsoleValueType::cvString;
            dstValue = &dstStoreValue;
            object->stackDataField(field,array,dstValue);
      } else if (currentLocalRegister != -1) {
            dstValue = Script::gEvalState.getLocalConsoleValue(currentLocalRegister);
      } else if (Script::gEvalState.currentVariable) {
            dstValue = Script::gEvalState.getConsoleValue();
      }

      // no dstValue nothing to do here
      if (!dstValue) {
            return;
      }

      // ----
      static const StringTableEntry xyzw[] =
      {
            StringTable->insert("x"),
            StringTable->insert("y"),
            StringTable->insert("z"),
            StringTable->insert("w")
      };

      static const StringTableEntry wh[] =
      {
            StringTable->insert("width"),
            StringTable->insert("height")
      };


      static const StringTableEntry rgba[] =
      {
            StringTable->insert("r"),
            StringTable->insert("g"),
            StringTable->insert("b"),
            StringTable->insert("a")
      };
      // ----

      int componentIndex = -1;
      if      (subField == xyzw[0] || subField == rgba[0]) componentIndex = 0;
      else if (subField == xyzw[1] || subField == rgba[1]) componentIndex = 1;
      else if (subField == xyzw[2] || subField == rgba[2] || subField == wh[0]) componentIndex = 2;
      else if (subField == xyzw[3] || subField == rgba[3] || subField == wh[1]) componentIndex = 3;

      if (componentIndex < 0) return;


#ifdef  ENABLE_CONSOLE_VECTOR
      // Con::debugf("dstValue->type == %d",  dstValue->type );
      if (/*dstValue->type < cvConsoleValueType && */ dstValue->type != ConsoleValueType::cvVector ) //TEST typecasting by component
      {
            dstValue->setVector(dstValue->getVector());
            // Con::debugf("*** typecast by component ?!...");
      }

      if (dstValue->type == ConsoleValueType::cvVector)
      {
            dstValue->v.points[componentIndex] = (F32)pSrcStack->getFloat();
      }
      else  //slow string ....
#endif
      {
            String currentStr = dstValue->getString();

            // -----------------------------------
            // only get ONE number:
            // -----------------------------------
            const char *s = pSrcStack->getString();
            const char *p = s;
            if (*p == '-' || *p == '+') p++;
            bool seen_point = false;
            while (*p != '\0') {
                  if (*p >= '0' && *p <= '9') {
                        p++;
                  } else if (*p == '.' && !seen_point) {
                        seen_point = true;
                        p++;
                  } else {
                        break;
                  }
            }
            size_t len = p - s;
            if (len >= 32) len = 31;
            static char buffer[32];
            if (len > 0) {
                  memcpy(buffer, s, len);
                  buffer[len] = '\0';
            } else {
                  buffer[0] = '0';
                  buffer[1] = '\0';
            }

            // -----------------------------------
            //
            //  speed up :D
            //

            const char* compStart[4] = { nullptr, nullptr, nullptr, nullptr };
            size_t compLen[4] = { 0, 0, 0, 0 };
            int compCount = 0;

            const char* pStr = currentStr.c_str();

            while (*pStr != '\0' && compCount < 4) {
                  while (*pStr == ' ' || *pStr == '\t' || *pStr == '\n' || *pStr == '\r') {
                        pStr++;
                  }
                  if (*pStr == '\0') break;

                  compStart[compCount] = pStr;

                  while (*pStr != '\0' && *pStr != ' ' && *pStr != '\t' && *pStr != '\n' && *pStr != '\r') {
                        pStr++;
                  }

                  compLen[compCount] = pStr - compStart[compCount];
                  compCount++;
            }

            char finalResult[128];
            char* out = finalResult;
            size_t bufferLen = strlen(buffer);

            for (int i = 0; i < 4; i++) {
                  if (i == componentIndex) {
                        memcpy(out, buffer, bufferLen);
                        out += bufferLen;
                  } else if (i < compCount) {
                        memcpy(out, compStart[i], compLen[i]);
                        out += compLen[i];
                  } else {
                        *out++ = '0';
                  }

                  if (i < 3) {
                        *out++ = ' ';
                  }
            }
            *out = '\0';

            dstValue->setString(finalResult);

      }

      if (object && field) {
            object->pushDataField(field,array,dstValue);
      }

}
// -----------------------------------------------------------------------------
// replaved by pushFieldComponent
// static void setFieldComponent(SimObject* object, StringTableEntry field, const char* array, StringTableEntry subField, S32 currentLocalRegister)
// {
//    // Copy the current string value
//    char strValue[1024];
//    dStrncpy(strValue, stack[_STK].getString(), 1024);
//
//    char val[1024] = "";
//    const char* prevVal = NULL;
//
//    if (object && field)
//       prevVal = object->getDataField(field, array);
//    else if (currentLocalRegister != -1)
//       prevVal = Script::gEvalState.getLocalStringVariable(currentLocalRegister);
//    // Set the value on a variable.
//    else if (Script::gEvalState.currentVariable)
//       prevVal = Script::gEvalState.getStringVariable();
//
//    // Ensure that the variable has a value
//    if (!prevVal)
//       return;
//
//    static const StringTableEntry xyzw[] =
//    {
//       StringTable->insert("x"),
//       StringTable->insert("y"),
//       StringTable->insert("z"),
//       StringTable->insert("w")
//    };
//
//    //XXTH added
//    static const StringTableEntry wh[] =
//    {
//          StringTable->insert("width"),
//          StringTable->insert("height")
//    };
//
//
//    static const StringTableEntry rgba[] =
//    {
//       StringTable->insert("r"),
//       StringTable->insert("g"),
//       StringTable->insert("b"),
//       StringTable->insert("a")
//    };
//
//    // Insert the value into the specified
//    // component of the string.
//    if (subField == xyzw[0] || subField == rgba[0])
//       dStrcpy(val, StringUnit::setUnit(prevVal, 0, strValue, " \t\n"), 128);
//
//    else if (subField == xyzw[1] || subField == rgba[1])
//       dStrcpy(val, StringUnit::setUnit(prevVal, 1, strValue, " \t\n"), 128);
//
//    else if (subField == xyzw[2] || subField == rgba[2] || subField == wh[0])
//       dStrcpy(val, StringUnit::setUnit(prevVal, 2, strValue, " \t\n"), 128);
//
//    else if (subField == xyzw[3] || subField == rgba[3] || subField == wh[1])
//       dStrcpy(val, StringUnit::setUnit(prevVal, 3, strValue, " \t\n"), 128);
//
//    if (val[0] != 0)
//    {
//       // Update the field or variable.
//       if (object && field)
//          object->setDataField(field, 0, val);
//       else if (currentLocalRegister != -1)
//          Script::gEvalState.setLocalStringVariable(currentLocalRegister, val, dStrlen(val));
//       else if (Script::gEvalState.currentVariable)
//          Script::gEvalState.setStringVariable(val);
//    }
// }

//------------------------------------------------------------

F64 consoleStringToNumber(const char *str, StringTableEntry file, U32 line)
{
   F64 val = dAtof(str);
   if (val != 0)
      return val;
   else if (!dStricmp(str, "true"))
      return 1;
   else if (!dStricmp(str, "false"))
      return 0;
   else if (file)
   {
      Con::warnf(ConsoleLogEntry::General, "%s (%d): string always evaluates to 0.", file, line);
      return 0;
   }
   return 0;
}

SimObject* getThisObject(ConsoleValue& simObjectLookupValue)
{
   SimObject* thisObject = NULL;

   // Optimization: If we're an integer, we can lookup the value by SimObjectId
   if (simObjectLookupValue.getType() == ConsoleValueType::cvInteger)
      thisObject = Sim::findObject(static_cast<SimObjectId>(simObjectLookupValue.getFastInt()));
   else
   {
      SimObject *foundObject = Sim::findObject(simObjectLookupValue.getString());

      // Optimization: If we're not an integer, let's make it so that the fast path exists
      // on the first argument of the method call (speeds up future usage of %this, for example)
      if (foundObject != NULL)
         simObjectLookupValue.setInt(static_cast<S64>(foundObject->getId()));

      thisObject = foundObject;
   }

   return thisObject;
}

//------------------------------------------------------------

void ExprEvalState::setCurVarName(StringTableEntry name)
{
   if (name[0] == '$')
      currentVariable = Con::gGlobalVars.lookup(name);
   else if (getStackDepth() > 0)
      currentVariable = getCurrentFrame().lookup(name);
   if (!currentVariable && gWarnUndefinedScriptVariables)
      Con::warnf(ConsoleLogEntry::Script, "Variable referenced before assignment: %s", name);
}

void ExprEvalState::setCurVarNameCreate(StringTableEntry name)
{
   if (name[0] == '$')
      currentVariable = Con::gGlobalVars.add(name);
   else if (getStackDepth() > 0)
      currentVariable = getCurrentFrame().add(name);
   else
   {
      currentVariable = NULL;
      Con::warnf(ConsoleLogEntry::Script, "Accessing local variable in global scope... failed: %s", name);
   }
}

//------------------------------------------------------------

S32 ExprEvalState::getIntVariable()
{
   return currentVariable ? currentVariable->getIntValue() : 0;
}

F64 ExprEvalState::getFloatVariable()
{
   return currentVariable ? currentVariable->getFloatValue() : 0;
}

const char *ExprEvalState::getStringVariable()
{
   return currentVariable ? currentVariable->getStringValue() : "";
}

ConsoleValue* ExprEvalState::getConsoleValue()
{
      if (!currentVariable) return nullptr;
      return &currentVariable->value;
}
//------------------------------------------------------------

void ExprEvalState::setIntVariable(S32 val)
{
   AssertFatal(currentVariable != NULL, "Invalid evaluator state - trying to set null variable!");
   currentVariable->setIntValue(val);
}

void ExprEvalState::setFloatVariable(F64 val)
{
   AssertFatal(currentVariable != NULL, "Invalid evaluator state - trying to set null variable!");
   currentVariable->setFloatValue(val);
}

void ExprEvalState::setStringVariable(const char *val)
{
   AssertFatal(currentVariable != NULL, "Invalid evaluator state - trying to set null variable!");
   currentVariable->setStringValue(val);
}
#ifdef  ENABLE_CONSOLE_VECTOR
void ExprEvalState::setVectorVariable(ConsoleVector vec)
{
      AssertFatal(currentVariable != NULL, "Invalid evaluator state - trying to set null variable!");
      currentVariable->setVectorVariable(vec);
}

ConsoleVector ExprEvalState::getVectorVariable()
{
      AssertFatal(currentVariable != NULL, "Invalid evaluator state - trying to set null variable!");
      if (!currentVariable) return ConsoleVector();
      return currentVariable->getVectorVariable();
}
#endif

//-----------------------------------------------------------------------------

enum class FloatOperation
{
   Add,
   Sub,
   Mul,
   Div,

   LT,
   LE,
   GR,
   GE,
   EQ,
   NE
};

template<FloatOperation Op>
TORQUE_NOINLINE void doSlowMathOp()
{
   ConsoleValue& a = stack[_STK];
   ConsoleValue& b = stack[_STK - 1];

   // Arithmetic
   if constexpr (Op == FloatOperation::Add)
      stack[_STK - 1].setFloat(a.getFloat() + b.getFloat());
   else if constexpr (Op == FloatOperation::Sub)
      stack[_STK - 1].setFloat(a.getFloat() - b.getFloat());
   else if constexpr (Op == FloatOperation::Mul) {
// #ifndef ENABLE_CONSOLE_VECTOR
//          // TESTING b cast as a float :P
//          // ok get parse error and *= is not here so i keep it but it's
//          // never called.
//       if ( b.type == ConsoleValueType::cvVector) {
//             F64 aFloat = a.getFloat();
//             for (S32 i = 0; i < CONSOLE_VALUE_VECTOR_FIELD_COUNT)
//                   b.v[i] *= aFloat;
//             // But i cant see it since i use it as string  which is not updated here^^
//             Con::printf("test setting scale on vector: %f,%f,%f,%f",
//                         b.v[0], b.v[1], b.v[2], b.v[3]);
//       }
//       else
// #endif
      stack[_STK - 1].setFloat(a.getFloat() * b.getFloat());
   }
   else if constexpr (Op == FloatOperation::Div)
      stack[_STK - 1].setFloat(a.getFloat() / b.getFloat());

   // Logical
   if constexpr (Op == FloatOperation::LT)
      stack[_STK - 1].setInt(a.getFloat() < b.getFloat());
   if constexpr (Op == FloatOperation::LE)
      stack[_STK - 1].setInt(a.getFloat() <= b.getFloat());
   if constexpr (Op == FloatOperation::GR)
      stack[_STK - 1].setInt(a.getFloat() > b.getFloat());
   if constexpr (Op == FloatOperation::GE)
      stack[_STK - 1].setInt(a.getFloat() >= b.getFloat());
   if constexpr (Op == FloatOperation::EQ)
      stack[_STK - 1].setInt(a.getFloat() == b.getFloat());
   if constexpr (Op == FloatOperation::NE)
      stack[_STK - 1].setInt(a.getFloat() != b.getFloat());

   POP_STK();
}

template<FloatOperation Op>
TORQUE_FORCEINLINE inline void doFloatMathOperation()
{
   ConsoleValue& a = stack[_STK];
   ConsoleValue& b = stack[_STK - 1];

   // S32 fastIf = (a.getType() == ConsoleValueType::cvFloat) & (b.getType() == ConsoleValueType::cvFloat);
   // XXTH FIX Compiler warning:
   S32 fastIf = static_cast<S32>(a.getType() == ConsoleValueType::cvFloat)
   & static_cast<S32>(b.getType() == ConsoleValueType::cvFloat);


   if (fastIf)
   {
      // ElfScript 0.5a restored .. without func calls is not really faster
      // Arithmetic
      if constexpr (Op == FloatOperation::Add)
         stack[_STK - 1].setFastFloat(a.getFastFloat() + b.getFastFloat());
      if constexpr (Op == FloatOperation::Sub)
         stack[_STK - 1].setFastFloat(a.getFastFloat() - b.getFastFloat());
      if constexpr (Op == FloatOperation::Mul)
         stack[_STK - 1].setFastFloat(a.getFastFloat() * b.getFastFloat());
      if constexpr (Op == FloatOperation::Div)
         stack[_STK - 1].setFastFloat(a.getFastFloat() / b.getFastFloat());

      // Logical
      if constexpr (Op == FloatOperation::LT)
         stack[_STK - 1].setFastInt(a.getFastFloat() < b.getFastFloat());
      if constexpr (Op == FloatOperation::LE)
         stack[_STK - 1].setFastInt(a.getFastFloat() <= b.getFastFloat());
      if constexpr (Op == FloatOperation::GR)
         stack[_STK - 1].setFastInt(a.getFastFloat() > b.getFastFloat());
      if constexpr (Op == FloatOperation::GE)
         stack[_STK - 1].setFastInt(a.getFastFloat() >= b.getFastFloat());
      if constexpr (Op == FloatOperation::EQ)
         stack[_STK - 1].setFastInt(a.getFastFloat() == b.getFastFloat());
      if constexpr (Op == FloatOperation::NE)
         stack[_STK - 1].setFastInt(a.getFastFloat() != b.getFastFloat());

      POP_STK();
   }
   else
   {
      doSlowMathOp<Op>();
   }
}

//-----------------------------------------------------------------------------

enum class IntegerOperation
{
   BitAnd,
   BitOr,
   Xor,
   LShift,
   RShift,

   LogicalAnd,
   LogicalOr
   #ifdef ELFSCRIPT_INT_HACK
   // ElfScript:
   ,LT,  // Less Than (<)
   GT,  // Greater Than (>)
   LE,  // Less Equal (<=)
   GE,  // Greater Equal (>=)
   EQ,  // Equal (==)
   NE   // Not Equal (!=)
#endif

};

template<IntegerOperation Op>
TORQUE_NOINLINE void doSlowIntegerOp()
{
   ConsoleValue& a = stack[_STK];
   ConsoleValue& b = stack[_STK - 1];

   // Bitwise Op
   if constexpr (Op == IntegerOperation::BitAnd)
      stack[_STK - 1].setInt(a.getInt() & b.getInt());
   if constexpr (Op == IntegerOperation::BitOr)
      stack[_STK - 1].setInt(a.getInt() | b.getInt());
   if constexpr (Op == IntegerOperation::Xor)
      stack[_STK - 1].setInt(a.getInt() ^ b.getInt());
   if constexpr (Op == IntegerOperation::LShift)
      stack[_STK - 1].setInt(a.getInt() << b.getInt());
   if constexpr (Op == IntegerOperation::RShift)
      stack[_STK - 1].setInt(a.getInt() >> b.getInt());

   // Logical Op
   if constexpr (Op == IntegerOperation::LogicalAnd)
      stack[_STK - 1].setBool(a.getInt() && b.getInt());
   if constexpr (Op == IntegerOperation::LogicalOr)
      stack[_STK - 1].setBool(a.getInt() || b.getInt());

   POP_STK();
}

template<IntegerOperation Op>
TORQUE_FORCEINLINE inline void doIntOperation()
{
   ConsoleValue& a = stack[_STK];
   ConsoleValue& b = stack[_STK - 1];

   if (a.isNumberType() && b.isNumberType())
   {
      // Bitwise Op
      if constexpr (Op == IntegerOperation::BitAnd)
         stack[_STK - 1].setFastInt(a.getFastInt() & b.getFastInt());
      if constexpr (Op == IntegerOperation::BitOr)
         stack[_STK - 1].setFastInt(a.getFastInt() | b.getFastInt());
      if constexpr (Op == IntegerOperation::Xor)
         stack[_STK - 1].setFastInt(a.getFastInt() ^ b.getFastInt());
      if constexpr (Op == IntegerOperation::LShift)
         stack[_STK - 1].setFastInt(a.getFastInt() << b.getFastInt());
      if constexpr (Op == IntegerOperation::RShift)
         stack[_STK - 1].setFastInt(a.getFastInt() >> b.getFastInt());

      // Logical Op
      if constexpr (Op == IntegerOperation::LogicalAnd)
         stack[_STK - 1].setBool(a.getFastInt() && b.getFastInt());
      if constexpr (Op == IntegerOperation::LogicalOr)
         stack[_STK - 1].setBool(a.getFastInt() || b.getFastInt());

#ifdef ELFSCRIPT_INT_HACK
      // ElfScript ==============================>>>>>>
         // Less Than (<)
         if constexpr (Op == IntegerOperation::LT) {
               // Con::printf("a:%d; b:%d", a.getFastInt(), b.getFastInt());
               stack[_STK - 1].setFastInt(a.getFastInt() < b.getFastInt() ? 1 : 0);
         }

         // Greater Than (>)
         else if constexpr (Op == IntegerOperation::GT)
               stack[_STK - 1].setFastInt(a.getFastInt() > b.getFastInt() ? 1 : 0);

         // Less Equal (<=)
         else if constexpr (Op == IntegerOperation::LE)
               stack[_STK - 1].setFastInt(a.getFastInt() <= b.getFastInt() ? 1 : 0);

         // Greater Equal (>=)
         else if constexpr (Op == IntegerOperation::GE)
               stack[_STK - 1].setFastInt(a.getFastInt() >= b.getFastInt() ? 1 : 0);

         // Equal (==)
         else if constexpr (Op == IntegerOperation::EQ)
               stack[_STK - 1].setFastInt(a.getFastInt() == b.getFastInt() ? 1 : 0);

         // Not Equal (!=)
         else if constexpr (Op == IntegerOperation::NE)
               stack[_STK - 1].setFastInt(a.getFastInt() != b.getFastInt() ? 1 : 0);

      // <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
#endif
      POP_STK();
   }
   else
   {
      doSlowIntegerOp<Op>();
   }
}

//-----------------------------------------------------------------------------

U32 gExecCount = 0;
Con::EvalResult CodeBlock::exec(U32 ip, const char* functionName, Namespace* thisNamespace, U32 argc, ConsoleValue* argv, bool noCalls, StringTableEntry packageName, S32 setFrame)
{
#ifdef TORQUE_DEBUG
   U32 stackStart = _STK;
   gExecCount++;
#endif

   const U32 TRACE_BUFFER_SIZE = 1024;
   static char traceBuffer[TRACE_BUFFER_SIZE];
   U32 i;

   U32 iterDepth = 0;
   ConsoleValue returnValue;
   const bool isCodelet = (!argv && setFrame == -2);

   incRefCount();
   F64* curFloatTable;
   char* curStringTable;
   S32 curStringTableLen = 0; //clint to ensure we dont overwrite it

   StringTableEntry thisFunctionName = NULL;
   bool popFrame = false;
   if (argv)
   {
      // assume this points into a function decl:
      U32 fnArgc = code[ip + 2 + 6];
      U32 regCount = code[ip + 2 + 7];
      thisFunctionName = CodeToSTE(code, ip);
      S32 wantedArgc = getMin(argc - 1, fnArgc); // argv[0] is func name
      if (Con::gTraceOn)
      {
         traceBuffer[0] = 0;
         dStrcat(traceBuffer, "Entering ", TRACE_BUFFER_SIZE);
         if (packageName)
         {
            dStrcat(traceBuffer, "[", TRACE_BUFFER_SIZE);
            dStrcat(traceBuffer, packageName, TRACE_BUFFER_SIZE);
            dStrcat(traceBuffer, "]", TRACE_BUFFER_SIZE);
         }
         if (thisNamespace && thisNamespace->mName)
         {
            dSprintf(traceBuffer + (U32)dStrlen(traceBuffer), sizeof(traceBuffer) - (U32)dStrlen(traceBuffer),
               "%s::%s(", thisNamespace->mName, thisFunctionName);
         }
         else
         {
            dSprintf(traceBuffer + (U32)dStrlen(traceBuffer), sizeof(traceBuffer) - (U32)dStrlen(traceBuffer),
               "%s(", thisFunctionName);
         }
         for (i = 0; i < wantedArgc; i++)
         {
            dStrcat(traceBuffer, argv[i + 1].getString(), TRACE_BUFFER_SIZE);
            if (i != wantedArgc - 1)
               dStrcat(traceBuffer, ", ", TRACE_BUFFER_SIZE);
         }
         dStrcat(traceBuffer, ")", TRACE_BUFFER_SIZE);
         Con::printf("%s", traceBuffer);
      }
      Script::gEvalState.pushFrame(thisFunctionName, thisNamespace, regCount);
      popFrame = true;
      for (i = 0; i < wantedArgc; i++)
      {
         S32 reg = code[ip + (2 + 6 + 1 + 1) + i];
         ConsoleValue& value = argv[i + 1];
         Script::gEvalState.moveConsoleValue(reg, (value));
      }

      // -----------------------------------------------------------------------
      // Handle missing arguments.
      //
      // For each absent arg that carries a default (argFlags bit 0x1), we
      // execute its codelet — a small bytecode expression compiled after the
      // function body that ends with OP_DEFAULT_END.
      //
      // The codelet is run in its own minimal frame via a nested exec() call.
      //
      // If the default offset is 0, the argument had no default expression and
      // the register keeps its zero-initialised value.
      // -----------------------------------------------------------------------
      if (wantedArgc < S32(fnArgc))
      {
         Namespace::Entry* temp = thisNamespace->lookup(thisFunctionName);

         // Offset into the header where arg flags begin.
         const U32 flagBase = ip + 10 + fnArgc;
         // Offset into the header where default codelet IPs begin.
         const U32 offsetBase = ip + 10 + 2 * fnArgc;

         for (; i < S32(fnArgc); i++)
         {
            const S32 reg = code[ip + 10 + i];
            const U32 argFlags = code[flagBase + i];

            if (argFlags & 0x1)   // argument has a default expression
            {
               const U32 codeletIp = (temp != NULL)
                  ? temp->mDefaultOffsets[i]
                  : code[offsetBase + i];

               if (codeletIp != 0)
               {
                  // Execute the default codelet.
                  //   argv=NULL   → uses globalStrings / globalFloats (correct,
                  //                  since codelets are compiled into those tables).
                  //   argc=0      → pushes a frame with 0 locals.
                  //   setFrame=-2  → reference to the codelet frame.
                  Con::EvalResult result = exec(
                     codeletIp,
                     NULL,       // functionName
                     NULL,       // thisNamespace
                     0,          // argc
                     NULL,       // argv  ← signals non-function (codelet) call
                     noCalls,    // noCalls NOTE: XXTH reactivated!!!! and deactivated again
                     NULL,       // packageName
                     -2          // setFrame
                  );

                  Script::gEvalState.moveConsoleValue(reg, result.value);
               }
               // codeletIp == 0: no default; register stays at its zero value.
            }
         }
      }

      // -----------------------------------------------------------------------
      // Advance ip to the start of the function BODY.
      //
      // The header now contains 3*fnArgc words after the fixed 10-word prefix:
      //   fnArgc words for register mappings
      //   fnArgc words for arg flags
      //   fnArgc words for default codelet IPs   ← new
      //
      // Old: ip + 10 + 2*fnArgc
      // New: ip + 10 + 3*fnArgc
      // -----------------------------------------------------------------------
      ip = ip + 10 + 3 * fnArgc;

      curFloatTable = functionFloats;
      curStringTable = functionStrings;
      curStringTableLen = functionStringsMaxLen;
   }
    else if (isCodelet)
    {
       // ---- Codelet path ----------------------------------------------------
       //
       // The codelet was compiled into functionStrings/functionFloats (see
       // compileStmt).
       //
       // functionStrings lives for the lifetime of the CodeBlock, which is
       // always at least as long as any call to a function it contains.
       curStringTable = functionStrings;
       curFloatTable = functionFloats;
       curStringTableLen = functionStringsMaxLen;

       // Push a minimal empty frame.  The codelet contains only an expression;
       // it has no local variables of its own.
       Script::gEvalState.pushFrame(NULL, NULL, 0);
       popFrame = true;

       // setFrame has served its purpose as a mode signal.  Reset it so the
       // telnet debugger guard `if (telDebuggerOn && setFrame < 0)` fires
       // correctly (codelets should not push a telnet stack frame).
       setFrame = -1;
   }
   else
   {
      curFloatTable = globalFloats;
      curStringTable = globalStrings;
      curStringTableLen = globalStringsMaxLen;

      // If requested stack frame isn't available, request a new one
      // (this prevents assert failures when creating local
      //  variables without a stack frame)
      if (Script::gEvalState.getStackDepth() <= setFrame)
         setFrame = -1;

      // Do we want this code to execute using a new stack frame?
      // compiling a file will force setFrame to 0, forcing us to get a new frame.
      if (setFrame <= 0)
      {
         // argc is the local count for eval
         Script::gEvalState.pushFrame(NULL, NULL, argc);
      }
      else
      {
         // We want to copy a reference to an existing stack frame
         // on to the top of the stack.  Any change that occurs to
         // the locals during this new frame will also occur in the
         // original frame.
         S32 stackIndex = Script::gEvalState.getTopOfStack() - setFrame - 1;
         Script::gEvalState.pushFrameRef(stackIndex);
      }

      popFrame = true;
   }

   Script::gEvalState.getCurrentFrame().module = this;
   Script::gEvalState.getCurrentFrame().ip = ip;

   // Grab the state of the telenet debugger here once
   // so that the push and pop frames are always balanced.
   // FIXME
   // const bool telDebuggerOn = TelDebugger && TelDebugger->isConnected();
   // if (telDebuggerOn && setFrame < 0)
   //    TelDebugger->pushStackFrame();

   StringTableEntry var, objParent;
   U32 failJump = 0;
   StringTableEntry fnName;
   StringTableEntry fnNamespace, fnPackage;

   static const U32 objectCreationStackSize = 32;
   S32 objectCreationStackIndex = 0;
   struct {
      SimObject* newObject;
      U32 failJump;
   } objectCreationStack[objectCreationStackSize] = {};

   SimObject* currentNewObject = 0;
   StringTableEntry prevField = NULL;
   StringTableEntry curField = NULL;
   SimObject* prevObject = NULL;
   SimObject* curObject = NULL;
   SimObject* thisObject = NULL;
   Namespace::Entry* nsEntry;
   Namespace* ns = NULL;
   const char* curFNDocBlock = NULL;
   const char* curNSDocBlock = NULL;
   const S32 nsDocLength = 128;
   char nsDocBlockClass[nsDocLength];

   S32 callArgc;
   ConsoleValue* callArgv;

   static char curFieldArray[256];
   static char prevFieldArray[256];

   if (this->name)
   {
      Con::gCurrentFile = this->name;
      Con::gCurrentRoot = this->modPath;
   }
   const char* val;
   S32 reg;
   S32 currentRegister = -1;

   // The frame temp is used by the variable accessor ops (OP_SAVEFIELD_* and
   // OP_LOADFIELD_*) to store temporary values for the fields.
   static S32 VAL_BUFFER_SIZE = 1024;
   FrameTemp<char> valBuffer(VAL_BUFFER_SIZE);


   // ==========================================================================
   //  D i r e c t  T h r e a d i n g
   //  ----- XXTH: insane change started at 2026-08-05 ------
   // ==========================================================================


   //XXTH ElfScript ( i guess i'am insane *haha* )
   /*static*/ const void* dispatch_table[] = {
         &&handle_OP_FUNC_DECL,
         &&handle_OP_DEFAULT_END,
         &&handle_OP_CREATE_OBJECT,
         &&handle_OP_ADD_OBJECT,
         &&handle_OP_END_OBJECT,
         &&handle_OP_FINISH_OBJECT,

         &&handle_OP_JMPIFFNOT,
         &&handle_OP_JMPIFNOT,
         &&handle_OP_JMPNOTSTRING,
         &&handle_OP_JMPIFF,
         &&handle_OP_JMPIF,
         &&handle_OP_JMPIFNOT_NP,
         &&handle_OP_JMPIF_NP,
         &&handle_OP_JMP,
         &&handle_OP_RETURN,
         &&handle_OP_RETURN_VOID,
         &&handle_OP_RETURN_FLT,
         &&handle_OP_RETURN_UINT,

         &&handle_OP_CMPEQ,
         &&handle_OP_CMPGR,
         &&handle_OP_CMPGE,
         &&handle_OP_CMPLT,
         &&handle_OP_CMPLE,
         &&handle_OP_CMPNE,
         &&handle_OP_XOR,
         &&handle_OP_MOD,
         &&handle_OP_BITAND,
         &&handle_OP_BITOR,
         &&handle_OP_NOT,
         &&handle_OP_NOTF,
         &&handle_OP_ONESCOMPLEMENT,

         &&handle_OP_SHR,
         &&handle_OP_SHL,
         &&handle_OP_AND,
         &&handle_OP_OR,

         &&handle_OP_ADD,
         &&handle_OP_SUB,
         &&handle_OP_MUL,
         &&handle_OP_DIV,
         &&handle_OP_NEG,
         &&handle_OP_INC,

         &&handle_OP_SETCURVAR,
         &&handle_OP_SETCURVAR_CREATE,
         &&handle_OP_SETCURVAR_ARRAY,
         &&handle_OP_SETCURVAR_ARRAY_CREATE,

         &&handle_OP_LOADVAR_UINT,
         &&handle_OP_LOADVAR_FLT,
         &&handle_OP_LOADVAR_STR,

         &&handle_OP_SAVEVAR_UINT,
         &&handle_OP_SAVEVAR_FLT,
         &&handle_OP_SAVEVAR_STR,

         &&handle_OP_LOAD_LOCAL_VAR_UINT,
         &&handle_OP_LOAD_LOCAL_VAR_FLT,
         &&handle_OP_LOAD_LOCAL_VAR_STR,

         &&handle_OP_SAVE_LOCAL_VAR_UINT,
         &&handle_OP_SAVE_LOCAL_VAR_FLT,
         &&handle_OP_SAVE_LOCAL_VAR_STR,

         &&handle_OP_SETCUROBJECT,
         &&handle_OP_SETCUROBJECT_NEW,
         &&handle_OP_SETCUROBJECT_INTERNAL,

         &&handle_OP_SETCURFIELD,
         &&handle_OP_SETCURFIELD_ARRAY,
         &&handle_OP_SETCURFIELD_TYPE,

         &&handle_OP_LOADFIELD_UINT,
         &&handle_OP_LOADFIELD_FLT,
         &&handle_OP_LOADFIELD_STR,

         &&handle_OP_SAVEFIELD_UINT,
         &&handle_OP_SAVEFIELD_FLT,
         &&handle_OP_SAVEFIELD_STR,

         &&handle_OP_POP_STK,

         &&handle_OP_LOADIMMED_UINT,
         &&handle_OP_LOADIMMED_FLT,
         &&handle_OP_TAG_TO_STR,
         &&handle_OP_LOADIMMED_STR,
         &&handle_OP_DOCBLOCK_STR,
         &&handle_OP_LOADIMMED_IDENT,

         &&handle_OP_CALLFUNC,

         &&handle_OP_ADVANCE_STR_APPENDCHAR,
         &&handle_OP_REWIND_STR,
         &&handle_OP_TERMINATE_REWIND_STR,
         &&handle_OP_COMPARE_STR,

         &&handle_OP_PUSH,
         &&handle_OP_PUSH_FRAME,

         &&handle_OP_ASSERT,
         &&handle_OP_BREAK,

         &&handle_OP_ITER_BEGIN,
         &&handle_OP_ITER,
         &&handle_OP_ITER_END,


         &&handle_OP_BUILD_VECTOR_STRING,
         &&handle_OP_SAVEFIELD_FASTPATH,

#ifdef ELFSCRIPT_INT_HACK
         &&handle_OP_CMPLT_UINT,
         &&handle_OP_CMPGR_UINT,
         &&handle_OP_CMPGE_UINT,
         &&handle_OP_CMPLE_UINT,
         &&handle_OP_CMPEQ_UINT,
         &&handle_OP_CMPNE_UINT,

         &&handle_OP_INC_UINT,
#endif

         &&handle_OP_DEC,

         &&handle_OP_INVALID
   };

   // magic macro:
   #define DISPATCH() goto *dispatch_table[code[ip++]]

   // replacement for  goto breakContinue; with op (old: instruction) parameter
   #define DISPATCH_OPCODE(op) goto *dispatch_table[op]
   // first command
   DISPATCH();

// ~~~~~~~~~~~~~~~~~~~~~~ FUNC_DECL
handle_OP_FUNC_DECL:
{
      //NOTE XXTH we have noCalls but we want to load the functions!
      // NOTE rolled back cause memory leak!!
      //orig: if (!noCalls)
      {
            fnName = CodeToSTE(code, ip);
            fnNamespace = CodeToSTE(code, ip + 2);
            fnPackage = CodeToSTE(code, ip + 4);
            bool hasBody = (code[ip + 6] & 0x01) != 0;

            Namespace::unlinkPackages();
            if (fnNamespace == NULL && fnPackage == NULL)
                  ns = Namespace::global();
            else
                  ns = Namespace::find(fnNamespace, fnPackage);

            ns->addFunction(fnName, this, hasBody ? ip : 0);

            if (curNSDocBlock)
            {
                  if (fnNamespace == StringTable->lookup(nsDocBlockClass))
                  {
                        char* usageStr = dStrdup(curNSDocBlock);
                        usageStr[dStrlen(usageStr)] = '\0';
                        ns->mUsage = usageStr;
                        ns->mCleanUpUsage = true;
                        curNSDocBlock = NULL;
                  }
            }

            const U32 fnArgc = code[ip + 8];

            Namespace::Entry* temp = ns->lookup(fnName);
            temp->mArgFlags.setSize(fnArgc);
            temp->mDefaultOffsets.setSize(fnArgc);

            // Arg flags: ip + 10 + fnArgc
            // Codelet IPs: ip + 10 + 2*fnArgc
            const U32 flagBase = ip + 10 + fnArgc;
            const U32 offsetBase = ip + 10 + 2 * fnArgc;

            for (U32 fa = 0; fa < fnArgc; ++fa)
            {
                  temp->mArgFlags[fa] = code[flagBase + fa];
                  temp->mDefaultOffsets[fa] = code[offsetBase + fa];
            }

            // No stack pops: mDefaultValues is gone.

            Namespace::relinkPackages();
            curFNDocBlock = NULL;
      }

      // Jump past header + body + codelets.  endIp is at code[ip + 7].
      ip = code[ip + 7];
      DISPATCH();
}

// ~~~~~~~~~~~~~~~~~~~~~~ DEFAULT_END
handle_OP_DEFAULT_END:
{
      returnValue = stack[_STK];
      POP_STK();

      CLEAR_ITER_STATE();


      goto execFinished;
}
// ~~~~~~~~~~~~~~~~~~~~~~ OBJECTS
// cleaned up code removed datablocks .. i kept the old OP_CREATE_OBJECT in the legacy part
handle_OP_CREATE_OBJECT:
{
      // Read some useful info.
      objParent = CodeToSTE(code, ip);
      // bool isDataBlock = code[ip + 2];
      bool isInternal = code[ip + 3];
      bool isSingleton = code[ip + 4];
      U32  lineNumber = code[ip + 5];
      failJump = code[ip + 6];

      // If we don't allow calls, we certainly don't allow creating objects!
      // Moved this to after failJump is set. Engine was crashing when
      // noCalls = true and an object was being created at the beginning of
      // a file. ADL.
      if (noCalls)
      {
            ip = failJump;
            DISPATCH(); // break;
      }

      // Push the old info to the stack
      //Assert( objectCreationStackIndex < objectCreationStackSize );
      objectCreationStack[objectCreationStackIndex].newObject = currentNewObject;
      objectCreationStack[objectCreationStackIndex++].failJump = failJump;

      // Get the constructor information off the stack.
      gCallStack.argvc(NULL, callArgc, &callArgv);
      AssertFatal(callArgc - 3 >= 0, avar("Call Arg needs at least 3, only has %d", callArgc));
      const char* objectName = callArgv[2].getString();

      currentNewObject = NULL;

      if (!isInternal)
      {
            AbstractClassRep* rep = AbstractClassRep::findClassRep(objectName);
            if (rep != NULL)
            {
                  Con::errorf(ConsoleLogEntry::General, "%s: Cannot name object [%s] the same name as a script class.",
                              getFileLine(ip), objectName);
                  ip = failJump;
                  gCallStack.popFrame();
                   DISPATCH(); // break;
            }

            SimObject* obj = Sim::findObject((const char*)objectName);
            if (obj)
            {
                  if (isSingleton)
                  {
                        // Make sure we're not trying to change types
                        if (dStricmp(obj->getClassName(), callArgv[1].getString()) != 0)
                        {
                              Con::errorf(ConsoleLogEntry::General, "%s: Cannot re-declare object [%s] with a different class [%s] - was [%s].",
                                          getFileLine(ip), objectName, callArgv[1].getString(), obj->getClassName());
                              ip = failJump;
                              gCallStack.popFrame();
                               DISPATCH(); // break;
                        }

                        // We're creating a singleton, so use the found object instead of creating a new object.
                        currentNewObject = obj;
                        Con::warnf("%s: Singleton Object was already created with name %s. Using existing object.",
                                   getFileLine(ip), objectName);
                  }
            }
      }

      gCallStack.popFrame();

      if (!currentNewObject)
      {
            // Well, looks like we have to create a new object.
            ConsoleObject* object = ConsoleObject::create(callArgv[1].getString());

            // Deal with failure!
            if (!object)
            {
                  Con::errorf(ConsoleLogEntry::General, "%s: Unable to instantiate non-conobject class %s.", getFileLine(ip - 1), callArgv[1].getString());
                  ip = failJump;
                  DISPATCH(); // break;
            }

            // Finally, set currentNewObject to point to the new one.
            currentNewObject = dynamic_cast<SimObject*>(object);

            // Deal with the case of a non-SimObject.
            if (!currentNewObject)
            {
                  Con::errorf(ConsoleLogEntry::General, "%s: Unable to instantiate non-SimObject class %s.", getFileLine(ip - 1), callArgv[1].getString());
                  delete object;
                  ip = failJump;
                  DISPATCH(); // break;
            }

            // Set the declaration line
            currentNewObject->setDeclarationLine(lineNumber);

            // Set the file that this object was created in
            currentNewObject->setFilename(this->name);

            // Does it have a parent object? (ie, the copy constructor : syntax, not inheriance)
            if (*objParent)
            {
                  // Find it!
                  SimObject* parent;
                  if (Sim::findObject(objParent, parent))
                  {
                        // Con::printf(" - Parent object found: %s", parent->getClassName());

                        currentNewObject->setCopySource(parent);
                        currentNewObject->assignFieldsFrom(parent);

                  }
                  else
                  {
                        if (Con::gObjectCopyFailures == -1)
                              Con::errorf(ConsoleLogEntry::General, "%s: Unable to find parent object %s for %s.", getFileLine(ip - 1), objParent, callArgv[1].getString());
                        ++Con::gObjectCopyFailures;

                        delete object;
                        currentNewObject = NULL;
                        ip = failJump;
                        DISPATCH(); // break;
                  }
            }

            // If a name was passed, assign it.
            if (objectName[0])
            {
                  if (!isInternal)
                        currentNewObject->assignName(objectName);
                  else
                        currentNewObject->setInternalName(objectName);

                  // Set the original name
                  currentNewObject->setOriginalName( objectName );
            }

            // Do the constructor parameters.
            if (!currentNewObject->processArguments(callArgc - 3, callArgv + 3))
            {
                  delete currentNewObject;
                  currentNewObject = NULL;
                  ip = failJump;
                  DISPATCH(); // break;
            }

            currentNewObject->setModStaticFields(true);
            currentNewObject->setModDynamicFields(true);
      }
      else
      {
            currentNewObject->reloadReset(); // AFX (reload-reset)

            // Does it have a parent object? (ie, the copy constructor : syntax, not inheriance)
            if (*objParent)
            {
                  // Find it!
                  SimObject* parent;
                  if (Sim::findObject(objParent, parent))
                  {
                        // Con::printf(" - Parent object found: %s", parent->getClassName());

                        // temporarily block name change
                        SimObject::preventNameChanging = true;
                        currentNewObject->setCopySource(parent);
                        currentNewObject->assignFieldsFrom(parent);
                        // restore name changing
                        SimObject::preventNameChanging = false;

                  }
                  else
                  {
                        Con::errorf(ConsoleLogEntry::General, "%d: Unable to find parent object %s for %s.", lineNumber, objParent, callArgv[1].getString());
                  }
            }
      }

      // Advance the IP past the create info...
      ip += 7;
      DISPATCH(); // break;
}

handle_OP_ADD_OBJECT:
{
      // See OP_SETCURVAR for why we do this.
      curFNDocBlock = NULL;
      curNSDocBlock = NULL;

      // Do we place this object at the root?
      bool placeAtRoot = code[ip++];

      // Con::printf("Adding object %s", currentNewObject->getName());

      // Make sure it wasn't already added, then add it.
      if (currentNewObject == NULL)
      {
            DISPATCH(); // break;
      }

      bool isMessage = dynamic_cast<Message*>(currentNewObject) != NULL;

      if (currentNewObject->isProperlyAdded() == false)
      {
            bool ret = false;
            if (isMessage)
            {
                  SimObjectId id = Message::getNextMessageID();
                  if (id != 0xffffffff)
                        ret = currentNewObject->registerObject(id);
                  else
                        Con::errorf("%s: No more object IDs available for messages", getFileLine(ip));
            }
            else
                  ret = currentNewObject->registerObject();

            if (!ret)
            {
                  // This error is usually caused by failing to call Parent::initPersistFields in the class' initPersistFields().
                  Con::warnf(ConsoleLogEntry::General, "%s: Register object failed for object %s of class %s.", getFileLine(ip - 2), currentNewObject->getName(), currentNewObject->getClassName());
                  ++Con::gObjectCopyFailures;
                  delete currentNewObject;
                  currentNewObject = NULL;
                  ip = failJump;
                  DISPATCH(); // break;
            }
      }


      // What group will we be added to, if any?
      U32 groupAddId = (U32)stack[_STK].getInt();
      SimGroup* grp = NULL;
      SimSet* set = NULL;

      if (!placeAtRoot || !currentNewObject->getGroup())
      {
            if (!isMessage)
            {
                  if (!placeAtRoot)
                  {
                        // Otherwise just add to the requested group or set.
                        if (!Sim::findObject(groupAddId, grp))
                              Sim::findObject(groupAddId, set);
                  }

                  if (placeAtRoot)
                  {
                        // Deal with the instantGroup if we're being put at the root or we're adding to a component.
                        if (Con::gInstantGroup.isEmpty() || !Sim::findObject(Con::gInstantGroup, grp))
                              grp = Sim::getRootGroup();
                  }
            }

            // If we didn't get a group, then make sure we have a pointer to
            // the rootgroup.
            if (!grp)
                  grp = Sim::getRootGroup();

            // add to the parent group
            grp->addObject(currentNewObject);

            // If for some reason the add failed, add the object to the
            // root group so it won't leak.
            if (currentNewObject->getGroup() == NULL)
                  Sim::getRootGroup()->addObject(currentNewObject);

            // add to any set we might be in
            if (set)
                  set->addObject(currentNewObject);
      }

      // store the new object's ID on the stack (overwriting the group/set
      // id, if one was given, otherwise getting pushed)
      S32 id = currentNewObject->getId();
      if (placeAtRoot)
            stack[_STK].setInt(id);
      else
            stack[++_STK].setInt(id);

      DISPATCH(); // break;
}

handle_OP_END_OBJECT:
{
      // If we're not to be placed at the root, make sure we clean up
      // our group reference.
      bool placeAtRoot = code[ip++];
      if (!placeAtRoot)
            POP_STK();
      DISPATCH(); //break;
}

handle_OP_FINISH_OBJECT:
{
      if (currentNewObject)
            currentNewObject->onPostAdd();

      AssertFatal( objectCreationStackIndex >= 0, "Object Stack is empty." );
      currentNewObject = objectCreationStack[--objectCreationStackIndex].newObject;
      failJump = objectCreationStack[objectCreationStackIndex].failJump;
      DISPATCH(); //break;
}


// ~~~~~~~~~~~~~~~~~~~~~~ JMP
handle_OP_JMPIFFNOT:
      if (stack[_STK--].getFloat())
      {
         ip++;
         DISPATCH();
      } else {

         ip = code[ip];
         DISPATCH();
      }

handle_OP_JMPIFNOT:
      if (stack[_STK--].getInt())
      {
        ip++;
        DISPATCH();
      } else {
        ip = code[ip];
        DISPATCH();
      }


handle_OP_JMPNOTSTRING:
      if (stack[_STK--].getBool())
      {
            ip++;
            DISPATCH(); // break;
      }
      ip = code[ip];
      DISPATCH(); //break;

handle_OP_JMPIFF:
      if (!stack[_STK--].getFloat())
      {
            ip++;
            DISPATCH(); //break;
      }
      ip = code[ip];
      DISPATCH(); //break;



handle_OP_JMPIF:
      if (!stack[_STK--].getFloat())
      {
            ip++;
            DISPATCH();
      }
      ip = code[ip];
      DISPATCH();

handle_OP_JMPIFNOT_NP:
      if (stack[_STK].getInt())
      {
            POP_STK(); //XXTH memfix attempt orig: _STK--;
            ip++;
            DISPATCH(); //break;
      }
      ip = code[ip];
      DISPATCH(); //break;

handle_OP_JMPIF_NP:
      if (!stack[_STK].getInt())
      {
            POP_STK(); //XXTH memfix attempt orig: _STK--;
            ip++;
            DISPATCH(); //break;
      }
      ip = code[ip];
      DISPATCH(); //break;

handle_OP_JMP:
      ip = code[ip];
      DISPATCH(); //break;

handle_OP_RETURN:
{
      returnValue = (stack[_STK]);
      POP_STK();

      // Clear iterator state.
      CLEAR_ITER_STATE();

      goto execFinished;
}

handle_OP_RETURN_VOID:

         CLEAR_ITER_STATE();

         returnValue.setEmptyString();
         goto execFinished;

handle_OP_RETURN_FLT:
      returnValue.setFloat(stack[_STK].getFloat());
      POP_STK();
      // Clear iterator state.
      CLEAR_ITER_STATE();

      goto execFinished;

handle_OP_RETURN_UINT:
      returnValue.setInt(stack[_STK].getInt());
      POP_STK();
      // Clear iterator state.
      CLEAR_ITER_STATE();

      goto execFinished;


// ~~~~~~~~~~~~~~~~~~~~~~~~ CMP
handle_OP_CMPEQ:
      doFloatMathOperation<FloatOperation::EQ>();
      DISPATCH();

handle_OP_CMPGR:
      doFloatMathOperation<FloatOperation::GR>();
      DISPATCH();

handle_OP_CMPGE:
      doFloatMathOperation<FloatOperation::GE>();
      DISPATCH();

handle_OP_CMPLT:
      doFloatMathOperation<FloatOperation::LT>();
      DISPATCH();

handle_OP_CMPLE:
      doFloatMathOperation<FloatOperation::LE>();
      DISPATCH();

handle_OP_CMPNE:
      doFloatMathOperation<FloatOperation::NE>();
      DISPATCH();

handle_OP_XOR:
      doIntOperation<IntegerOperation::Xor>();
      DISPATCH();

handle_OP_MOD: {
      S64 divisor = stack[_STK - 1].getInt();
      if (divisor != 0)
            stack[_STK - 1].setInt(stack[_STK].getInt() % divisor);
      else
            stack[_STK - 1].setInt(0);
      POP_STK();
      DISPATCH();
}

handle_OP_BITAND:
      doIntOperation<IntegerOperation::BitAnd>();
      DISPATCH();
handle_OP_BITOR:
      doIntOperation<IntegerOperation::BitOr>();
      DISPATCH();
handle_OP_NOT:
      stack[_STK].setBool(!stack[_STK].getInt());
      DISPATCH();
handle_OP_NOTF:
      stack[_STK].setInt(!stack[_STK].getFloat());
      DISPATCH();
handle_OP_ONESCOMPLEMENT:
      stack[_STK].setInt(~stack[_STK].getInt());
      DISPATCH();
// ~~~~~~~~~~~~~~~~~~~~~~~~
handle_OP_SHR:
      doIntOperation<IntegerOperation::RShift>();
      DISPATCH();

handle_OP_SHL:
      doIntOperation<IntegerOperation::LShift>();
      DISPATCH();

handle_OP_AND:
      doIntOperation<IntegerOperation::LogicalAnd>();
      DISPATCH();

handle_OP_OR:
      doIntOperation<IntegerOperation::LogicalOr>();
      DISPATCH();

// ~~~~~~~~~~~~~~~~~~~~~~~~

handle_OP_ADD:
      doFloatMathOperation<FloatOperation::Add>();
      DISPATCH();
handle_OP_SUB:
      doFloatMathOperation<FloatOperation::Sub>();
      DISPATCH();
handle_OP_MUL:
      doFloatMathOperation<FloatOperation::Mul>();
      DISPATCH();
handle_OP_DIV:
      doFloatMathOperation<FloatOperation::Div>();
      DISPATCH();
handle_OP_NEG:
      stack[_STK].setFloat(-stack[_STK].getFloat());
      DISPATCH();


handle_OP_INC: {
      reg = code[ip++];
      currentRegister = reg;

      ConsoleValue& stackRef = Script::gEvalState.currentRegisterArray->values[reg];
      if ( stackRef.type == ConsoleValueType::cvFloat) {
            // stackRef.setFastFloat(stackRef.getFastFloat() + 1.0);
            stackRef.f += 1.0f;
      } else {
            stackRef.setFastFloat(stackRef.getFloat() + 1.0f);
            // stackRef.setFloat(stackRef.getFloat() + 1.0f);
      }

      // Script::gEvalState.setLocalFloatVariable(reg, Script::gEvalState.getLocalFloatVariable(reg) + 1.0);
      DISPATCH();
}

handle_OP_DEC: { // 0.5a OP_DEC fast path
      reg = code[ip++];
      currentRegister = reg;

      ConsoleValue& stackRef = Script::gEvalState.currentRegisterArray->values[reg];
      if ( stackRef.type == ConsoleValueType::cvFloat) {
            // stackRef.setFastFloat(stackRef.getFastFloat() + 1.0);
            stackRef.f -= 1.0f;
      } else {
            stackRef.setFastFloat(stackRef.getFloat() - 1.0f);
            // stackRef.setFloat(stackRef.getFloat() - 1.0f);
      }
      // Script::gEvalState.setLocalFloatVariable(reg, Script::gEvalState.getLocalFloatVariable(reg) - 1.0);
      DISPATCH();
}

// ~~~~~~~~~~~~~~~~~ CURVAR
handle_OP_SETCURVAR:
      var = CodeToSTE(code, ip);
      ip += 2;

      // If a variable is set, then these must be NULL. It is necessary
      // to set this here so that the vector parser can appropriately
      // identify whether it's dealing with a vector.
      prevField = NULL;
      prevObject = NULL;
      curObject = NULL;

      // Used for local variable caching of what is active...when we
      // set a global, we aren't active
      currentRegister = -1;

      Script::gEvalState.setCurVarName(var);

      // In order to let docblocks work properly with variables, we have
      // clear the current docblock when we do an assign. This way it
      // won't inappropriately carry forward to following function decls.
      curFNDocBlock = NULL;
      curNSDocBlock = NULL;
      DISPATCH();

handle_OP_SETCURVAR_CREATE:
      var = CodeToSTE(code, ip);
      ip += 2;

      prevField = NULL;
      prevObject = NULL;
      curObject = NULL;

      currentRegister = -1;

      Script::gEvalState.setCurVarNameCreate(var);

      curFNDocBlock = NULL;
      curNSDocBlock = NULL;
      DISPATCH();

      handle_OP_SETCURVAR_ARRAY:
      var = StringTable->insert(stack[_STK].getString());

      // See OP_SETCURVAR
      prevField = NULL;
      prevObject = NULL;
      curObject = NULL;

      // Used for local variable caching of what is active...when we
      // set a global, we aren't active
      currentRegister = -1;

      Script::gEvalState.setCurVarName(var);

      // See OP_SETCURVAR for why we do this.
      curFNDocBlock = NULL;
      curNSDocBlock = NULL;
      DISPATCH();


handle_OP_SETCURVAR_ARRAY_CREATE:
      var = StringTable->insert(stack[_STK].getString());

      // See OP_SETCURVAR
      prevField = NULL;
      prevObject = NULL;
      curObject = NULL;

      currentRegister = -1;

      Script::gEvalState.setCurVarNameCreate(var);

      curFNDocBlock = NULL;
      curNSDocBlock = NULL;
      DISPATCH();

// ~~~~~~~~~~~~~~~~~ LOADVAR
handle_OP_LOADVAR_UINT:
      currentRegister = -1;
      stack[_STK + 1].setInt(Script::gEvalState.getIntVariable());
      PUSH_STK();
      DISPATCH();

handle_OP_LOADVAR_FLT:
      currentRegister = -1;
      stack[_STK + 1].setFloat(Script::gEvalState.getFloatVariable());
      PUSH_STK();
      DISPATCH();

handle_OP_LOADVAR_STR:
      currentRegister = -1;
      {
            // i check the type first!
            const Dictionary::Entry* varEntry = Script::gEvalState.currentVariable;
            bool fastPath = false;
            if (varEntry) {
                  static S32 valueType = 0;
                  valueType = varEntry->value.getType();
                  fastPath =  valueType == ConsoleValueType::cvFloat ||
                  valueType == ConsoleValueType::cvInteger;
            }
            if (fastPath)
            {
                  // Fastpath
                  stack[_STK + 1] = varEntry->value;
            }
            else
            {
                  // Slowpath: Fallback
                  stack[_STK + 1].setString(Script::gEvalState.getStringVariable());
            }
      }
      PUSH_STK();
      DISPATCH();

// ~~~~~~~~~~~~~~~~~ SAVEVAR
handle_OP_SAVEVAR_UINT:
      Script::gEvalState.setIntVariable(stack[_STK].getInt());
      DISPATCH();

handle_OP_SAVEVAR_FLT:
      Script::gEvalState.setFloatVariable(stack[_STK].getFloat());
      DISPATCH();

handle_OP_SAVEVAR_STR:
      if (stack[_STK].type == cvInteger) {
            Script::gEvalState.setIntVariable(stack[_STK].getInt());
            DISPATCH();
      }

      if (stack[_STK].type == cvFloat) {
            Script::gEvalState.setFloatVariable(stack[_STK].getFloat());
            DISPATCH();
      }
#ifdef ENABLE_CONSOLE_VECTOR
      if (stack[_STK].type == cvVector) {
            Script::gEvalState.setVectorVariable(stack[_STK].getVector());
            DISPATCH();
      }
#endif

      Script::gEvalState.setStringVariable(stack[_STK].getString());
      DISPATCH();


// ~~~~~~~~~~~~~~~~~~~~~~ LOCAL_VAR
handle_OP_LOAD_LOCAL_VAR_UINT:
      reg = code[ip++];
      currentRegister = reg;

      prevField = NULL;
      prevObject = NULL;
      curObject = NULL;

      stack[_STK + 1].setInt(Script::gEvalState.getLocalIntVariable(reg));
      PUSH_STK();
      DISPATCH();



handle_OP_LOAD_LOCAL_VAR_FLT:
         reg = code[ip++];
         currentRegister = reg;

         prevField = NULL;
         prevObject = NULL;
         curObject = NULL;

         stack[_STK + 1].setFloat(Script::gEvalState.getLocalFloatVariable(reg));
         PUSH_STK();
      DISPATCH();

handle_OP_LOAD_LOCAL_VAR_STR:
      reg = code[ip++];
      currentRegister = reg;

      prevField = NULL;
      prevObject = NULL;
      curObject = NULL;
      {
            const ConsoleValue& localVal = Script::gEvalState.currentRegisterArray->values[reg];
            S32 varType = localVal.getType();
            if (
                  varType == ConsoleValueType::cvFloat ||
#ifdef ENABLE_CONSOLE_VECTOR
                  varType == ConsoleValueType::cvVector ||
#endif
                  varType == ConsoleValueType::cvInteger
            )
            {
                  //fast fetch
                  stack[_STK + 1] = localVal;
            }
            else
            {
                  // fallback
                  // val = Script::gEvalState.getLocalStringVariable(reg);
                  stack[_STK + 1].setString(localVal.getString());
            }
      }
      PUSH_STK();
      DISPATCH();


handle_OP_SAVE_LOCAL_VAR_UINT: {
         reg = code[ip++];
         currentRegister = reg;

         prevField = NULL;
         prevObject = NULL;
         curObject = NULL;

         // 0.5a
         ConsoleValue& stackRef = Script::gEvalState.currentRegisterArray->values[reg];
         if ( stackRef.type == ConsoleValueType::cvInteger) {
               if (stack[_STK].type == ConsoleValueType::cvInteger)
                  stackRef.i = stack[_STK].i;
               else
                  stackRef.i = stack[_STK].getInt();
         } else {
               stackRef.setInt(stack[_STK].getInt());
         }


         // Script::gEvalState.setLocalIntVariable(reg, stack[_STK].getInt());
         DISPATCH();
}

handle_OP_SAVE_LOCAL_VAR_FLT: {
          reg = code[ip++];
         currentRegister = reg;

         prevField = NULL;
         prevObject = NULL;
         curObject = NULL;

         // 0.5a
         ConsoleValue& stackRef = Script::gEvalState.currentRegisterArray->values[reg];
         if ( stackRef.type == ConsoleValueType::cvFloat) {
               if (stack[_STK].type == ConsoleValueType::cvFloat)
                     stackRef.f = stack[_STK].f;
               else
                     stackRef.f = stack[_STK].getFloat();
         } else {
               stackRef.setFloat(stack[_STK].getFloat());
         }

         // Script::gEvalState.setLocalFloatVariable(reg, stack[_STK].getFloat());

         DISPATCH();
}

handle_OP_SAVE_LOCAL_VAR_STR:
         reg = code[ip++];
         currentRegister = reg;

         prevField = NULL;
         prevObject = NULL;
         curObject = NULL;

         // ElfScript 0.4c rocket change !
         if (stack[_STK].type == cvInteger) {
            Script::gEvalState.setLocalIntVariable(reg, stack[_STK].getInt());
            DISPATCH();
         }

         if (stack[_STK].type == cvFloat) {
               Script::gEvalState.setLocalFloatVariable(reg, stack[_STK].getFloat());
               DISPATCH();
         }
#ifdef ENABLE_CONSOLE_VECTOR
         if (stack[_STK].type == cvVector) {
             Script::gEvalState.setLocalVectorVariable(reg, stack[_STK].getVector());
             DISPATCH();
         }
#endif
         // orig slowmo =>
         val = stack[_STK].getString();
         Script::gEvalState.setLocalStringVariable(reg, val, (S32)dStrlen(val));
         DISPATCH();


// ~~~~~~~~~~~~~~~~~ SETCUROBJECT
handle_OP_SETCUROBJECT:
      prevObject = curObject;
      curObject = Sim::findObject(stack[_STK]);
      DISPATCH();

handle_OP_SETCUROBJECT_NEW:
      curObject = currentNewObject;
      DISPATCH();

handle_OP_SETCUROBJECT_INTERNAL:
      ++ip; // To skip the recurse flag if the object wasnt found
      if (curObject)
      {
            SimSet* set = dynamic_cast<SimSet*>(curObject);
            if (set)
            {
                  StringTableEntry intName = StringTable->insert(stack[_STK].getString());
                  bool recurse = code[ip - 1];
                  SimObject* obj = set->findObjectByInternalName(intName, recurse);
                  stack[_STK].setInt(obj ? obj->getId() : 0);
            }
            else
            {
                  Con::errorf(ConsoleLogEntry::Script, "%s: Attempt to use -> on non-set %s of class %s.", getFileLine(ip - 2), curObject->getName(), curObject->getClassName());
                  stack[_STK].setInt(0);
            }
      }
      else
      {
            Con::errorf(ConsoleLogEntry::Script, "%s: Attempt to use ->, but the group object wasn't found.", getFileLine(ip - 2));
            stack[_STK].setInt(0);
      }
      DISPATCH();
// ~~~~~~~~~~~~~~~~~ SETCURFIELD
handle_OP_SETCURFIELD:
      // Save the previous field for parsing vector fields.
      prevField = curField;
      dStrcpy(prevFieldArray, curFieldArray, 256);
      curField = CodeToSTE(code, ip);
      curFieldArray[0] = 0;
      ip += 2;
      DISPATCH();

handle_OP_SETCURFIELD_ARRAY:
      dStrcpy(curFieldArray, stack[_STK].getString(), 256);
      DISPATCH();

handle_OP_SETCURFIELD_TYPE:
      if(curObject)
            curObject->setDataFieldType(code[ip], curField, curFieldArray);
      ip++;
      DISPATCH();;
// ~~~~~~~~~~~~~~~~~ FIELD
handle_OP_LOADFIELD_UINT:
            if (curObject)
            {
                  stack[_STK + 1].cleanupData();
                  stack[_STK + 1].type = cvInteger; //HardCore!
                  curObject->stackDataField(curField, curFieldArray, &stack[_STK + 1]);

            }
            else
            {
                  stack[_STK + 1].cleanupData();
                  stack[_STK + 1].type = cvInteger; //HardCore!
                  stackFieldComponent(prevObject, prevField, prevFieldArray, curField, &stack[_STK + 1],currentRegister);

                  // char buff[FieldBufferSizeString];
                  // memset(buff, 0, sizeof(buff));
                  // getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff, currentRegister);
                  // stack[_STK + 1].setString(buff);
            }
            PUSH_STK();
            DISPATCH();

handle_OP_LOADFIELD_FLT:
            if (curObject)
            {
                  stack[_STK + 1].cleanupData();
                  stack[_STK + 1].type = cvFloat; //HardCore!
                  curObject->stackDataField(curField, curFieldArray, &stack[_STK + 1]);

            }
            else
            {
                  stack[_STK + 1].cleanupData();
                  stack[_STK + 1].type = cvFloat; //HardCore!
                  stackFieldComponent(prevObject, prevField, prevFieldArray, curField, &stack[_STK + 1],currentRegister);

                  // char buff[FieldBufferSizeString];
                  // memset(buff, 0, sizeof(buff));
                  // getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff, currentRegister);
                  // stack[_STK + 1].setString(buff);
            }
            PUSH_STK();
            DISPATCH();

handle_OP_LOADFIELD_STR:
         if (curObject)
         {
            stack[_STK + 1].cleanupData();
            stack[_STK + 1].type = cvString; // :(
            curObject->stackDataField(curField, curFieldArray, &stack[_STK + 1]);

         }
         else
         {
            // stack[_STK + 1].cleanupData();
            // stack[_STK + 1].type = cvString;
            stackFieldComponent(prevObject, prevField, prevFieldArray, curField, &stack[_STK + 1],currentRegister);

            // The field is not being retrieved from an object. Maybe it's
            // a special accessor?
            // char buff[FieldBufferSizeString];
            // memset(buff, 0, sizeof(buff));
            // getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff, currentRegister);
            // stack[_STK + 1].setString(buff);
         }
         PUSH_STK();
         DISPATCH();


handle_OP_SAVEFIELD_UINT:
handle_OP_SAVEFIELD_FLT:
handle_OP_SAVEFIELD_FASTPATH:
      if (curObject) {
            curObject->pushDataField(curField, curFieldArray, &stack[_STK]);
      } else {
            // The field is not being set on an object. Maybe it's a special accessor?
            pushFieldComponent(prevObject, prevField, prevFieldArray, curField, &stack[_STK], currentRegister);
            // setFieldComponent(prevObject, prevField, prevFieldArray, curField, currentRegister);
            prevObject = NULL;
      }
      DISPATCH();

// replaced by fastpath
handle_OP_SAVEFIELD_STR:
      if (curObject) {
            curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
      } else {
            // The field is not being set on an object. Maybe it's a special accessor?
            pushFieldComponent(prevObject, prevField, prevFieldArray, curField, &stack[_STK], currentRegister);
            // setFieldComponent(prevObject, prevField, prevFieldArray, curField, currentRegister);
            prevObject = NULL;
      }
DISPATCH();

// ~~~~~~~~~~~~~~~~~ STACK
handle_OP_POP_STK:
      POP_STK();
      DISPATCH();

// ~~~~~~~~~~~~~~~~~ IMMED

handle_OP_LOADIMMED_UINT:
         // 0.5a << NOT this is slower !
         // if (stack[_STK + 1].type == ConsoleValueType::cvInteger)
         //    stack[_STK + 1].i = code[ip++];
         // else
         //    stack[_STK + 1].setInt(code[ip++]);

         stack[_STK + 1].setInt(code[ip++]);

         PUSH_STK();
      DISPATCH();

handle_OP_LOADIMMED_FLT:
         // 0.5a << NOT this is slower !
//          if (stack[_STK + 1].type == ConsoleValueType::cvFloat)
//                stack[_STK + 1].f = curFloatTable[code[ip++]];
//          else
//             stack[_STK + 1].setFloat(curFloatTable[code[ip++]]);
//
         stack[_STK + 1].setFloat(curFloatTable[code[ip++]]);

         PUSH_STK();
      DISPATCH();

handle_OP_TAG_TO_STR:
      code[ip - 1] = OP_LOADIMMED_STR;
      // it's possible the string has already been converted
      Con::warnf("Tagged string not supported in ElfScript or FIXME (%s:%d)", __FILE__, __LINE__);
      // if (U8(curStringTable[code[ip]]) != StringTagPrefixByte)
      // {
      //    U32 id = GameAddTaggedString(curStringTable + code[ip]);
      //    dSprintf(curStringTable + code[ip] + 1, 7, "%d", id);
      //    *(curStringTable + code[ip]) = StringTagPrefixByte;
      // }
      //NOTE:  TORQUE_CASE_FALLTHROUGH;
      goto handle_OP_LOADIMMED_STR;

handle_OP_LOADIMMED_STR:
            stack[_STK + 1].setString(curStringTable + code[ip++]);
            _STK ++;
            DISPATCH();

handle_OP_DOCBLOCK_STR:
{
      // If the first word of the doc is '\class' or '@class', then this
      // is a namespace doc block, otherwise it is a function doc block.
      const char* docblock = curStringTable + code[ip++];

      const char* sansClass = dStrstr(docblock, "@class");
      if (!sansClass)
            sansClass = dStrstr(docblock, "\\class");

      if (sansClass)
      {
            // Don't save the class declaration. Scan past the 'class'
            // keyword and up to the first whitespace.
            sansClass += 7;
            S32 index = 0;
            while ((*sansClass != ' ') && (*sansClass != '\n') && *sansClass && (index < (nsDocLength - 1)))
            {
                  nsDocBlockClass[index++] = *sansClass;
                  sansClass++;
            }
            nsDocBlockClass[index] = '\0';

            curNSDocBlock = sansClass + 1;
      }
      else
            curFNDocBlock = docblock;

      DISPATCH();
}

handle_OP_LOADIMMED_IDENT:
      stack[_STK + 1].setStringTableEntry(CodeToSTE(code, ip));
      PUSH_STK();
      ip += 2;
      DISPATCH();

// ~~~~~~~~~~~~~~~~~ CALLFUNC
handle_OP_CALLFUNC:
{
      // This routingId is set when we query the object as to whether
      // it handles this method.  It is set to an enum from the table
      // above indicating whether it handles it on a component it owns
      // or just on the object.
      fnName = CodeToSTE(code, ip);
      fnNamespace = CodeToSTE(code, ip + 2);
      U32 callType = code[ip + 4];

      //if this is called from inside a function, append the ip and codeptr
      if (!Script::gEvalState.stack.empty())
      {
            Script::gEvalState.getCurrentFrame().module = this;
            Script::gEvalState.getCurrentFrame().ip = ip - 1;
      }

      ip += 5;
      gCallStack.argvc(fnName, callArgc, &callArgv);

      if (callType == FuncCallExprNode::FunctionCall)
      {
            // Note: This works even if the function was in a package. Reason being is when
            // activatePackage() is called, it swaps the namespaceEntry into the global namespace
            // (and reverts it when deactivatePackage is called). Method or Static related ones work
            // as expected, as the namespace is resolved on the fly.
            nsEntry = Namespace::global()->lookup(fnName);
            if (!nsEntry)
            {
                  Con::warnf(ConsoleLogEntry::General,
                              "%s: Unable to find function %s",
                              getFileLine(ip - 4), fnName);

                  gCallStack.popFrame();
                  stack[_STK + 1].setEmptyString();
                  PUSH_STK();
                  DISPATCH();
            }
      }
      else if (callType == FuncCallExprNode::StaticCall)
      {
            // Try to look it up.
            ns = Namespace::find(fnNamespace);
            nsEntry = ns->lookup(fnName);
            if (!nsEntry)
            {
                  Con::warnf(ConsoleLogEntry::General,
                              "%s: Unable to find function %s%s%s",
                              getFileLine(ip - 4), fnNamespace ? fnNamespace : "",
                              fnNamespace ? "::" : "", fnName);

                  gCallStack.popFrame();
                  stack[_STK + 1].setEmptyString();
                  PUSH_STK();
                  DISPATCH();
            }
      }
      else if (callType == FuncCallExprNode::MethodCall)
      {
            ConsoleValue& simObjectLookupValue = callArgv[1];
            thisObject = getThisObject(simObjectLookupValue);

            if (thisObject == NULL)
            {
                  Con::warnf(
                        ConsoleLogEntry::General,
                        "%s: Unable to find object: '%s' attempting to call function '%s'",
                        getFileLine(ip - 6),
                              simObjectLookupValue.getString(),
                              fnName
                  );

                  gCallStack.popFrame();
                  stack[_STK + 1].setEmptyString();
                  PUSH_STK();
                  DISPATCH();
            }

            ns = thisObject->getNamespace();
            if (ns)
                  nsEntry = ns->lookup(fnName);
            else
                  nsEntry = NULL;
      }
      else // it's a ParentCall
      {
            ConsoleValue& simObjectLookupValue = callArgv[1];
            thisObject = getThisObject(simObjectLookupValue);

            if (thisObject == NULL)
            {
                  Con::warnf(
                        ConsoleLogEntry::General,
                        "%s: Unable to find object: '%s' attempting to call function '%s'",
                        getFileLine(ip - 6),
                              simObjectLookupValue.getString(),
                              fnName
                  );

                  gCallStack.popFrame();
                  stack[_STK + 1].setEmptyString();
                  PUSH_STK();
                  DISPATCH();
            }

            if (thisNamespace)
            {
                  ns = thisNamespace->mParent;
                  if (ns)
                        nsEntry = ns->lookup(fnName);
                  else
                        nsEntry = NULL;
            }
            else
            {
                  ns = NULL;
                  nsEntry = NULL;
            }
      }

      if (!nsEntry || noCalls)
      {
            if (!noCalls)
            {
                  Con::warnf(ConsoleLogEntry::General, "%s: Unknown command %s.", getFileLine(ip - 4), fnName);
                  if (callType == FuncCallExprNode::MethodCall)
                  {
                        Con::warnf(ConsoleLogEntry::General, "  Object %s(%d) %s",
                                    thisObject->getName() ? thisObject->getName() : "",
                                    thisObject->getId(), Con::getNamespaceList(ns));
                  }
            }
            gCallStack.popFrame();
            stack[_STK + 1].setEmptyString();
            PUSH_STK();
            DISPATCH();
      }
      if (nsEntry->mType == Namespace::Entry::ConsoleFunctionType)
      {
            if (nsEntry->mFunctionOffset)
            {
                  ConsoleValue returnFromFn = nsEntry->mModule->exec(nsEntry->mFunctionOffset, fnName, nsEntry->mNamespace, callArgc, callArgv, false, nsEntry->mPackage).value;
                  stack[_STK + 1] = (returnFromFn);
            }
            else // no body
                  stack[_STK + 1].setEmptyString();
            PUSH_STK();

            gCallStack.popFrame();
      }
      else
      {
            if ((nsEntry->mMinArgs && S32(callArgc) < nsEntry->mMinArgs) || (nsEntry->mMaxArgs && S32(callArgc) > nsEntry->mMaxArgs))
            {
                  const char* nsName = ns ? ns->mName : "";
                  Con::warnf(ConsoleLogEntry::Script, "%s: %s::%s - wrong number of arguments. got %d, expected %d to %d", getFileLine(ip - 4), nsName, fnName, S32(callArgc), nsEntry->mMinArgs, nsEntry->mMaxArgs);
                  // ElfScript:
                  Con::warnf(ConsoleLogEntry::Script, "%s: usage: %s%s", getFileLine(ip - 4), nsEntry->mFunctionName,  nsEntry->getArgumentsString().c_str());
                  if (strlen(nsEntry->mUsage)>0) Con::warnf(ConsoleLogEntry::Script, "%s: docu: %s", getFileLine(ip - 4), nsEntry->mUsage);
                  gCallStack.popFrame();
                  stack[_STK + 1].setEmptyString();
                  PUSH_STK();
            }
            else
            {
                  switch (nsEntry->mType)
                  {

#ifdef ENABLE_CONSOLE_VECTOR_CALLBACK
                        case Namespace::Entry::VectorCallbackType:
                        {
                              ConsoleVector result = nsEntry->cb.mVectorCallbackFunc(thisObject, callArgc, callArgv);
                              gCallStack.popFrame();
                              stack[_STK + 1].setVector(result);
                              PUSH_STK();
                              break;
                        }
#endif

                        case Namespace::Entry::StringCallbackType:
                        {
                              const char* result = nsEntry->cb.mStringCallbackFunc(thisObject, callArgc, callArgv);
                              gCallStack.popFrame();
                              stack[_STK + 1].setString(result);
                              PUSH_STK();
                              break;
                        }
                        case Namespace::Entry::IntCallbackType:
                        {
                              S64 result = nsEntry->cb.mIntCallbackFunc(thisObject, callArgc, callArgv);
                              gCallStack.popFrame();

                              if (code[ip] == OP_POP_STK)
                              {
                                    ip++;
                                    break;
                              }

                              stack[_STK + 1].setInt(result);
                              PUSH_STK();
                              break;
                        }
                        case Namespace::Entry::FloatCallbackType:
                        {
                              F64 result = nsEntry->cb.mFloatCallbackFunc(thisObject, callArgc, callArgv);
                              gCallStack.popFrame();

                              if (code[ip] == OP_POP_STK)
                              {
                                    ip++;
                                    break;
                              }

                              stack[_STK + 1].setFloat(result);
                              PUSH_STK();
                              break;
                        }
                        case Namespace::Entry::VoidCallbackType:
                        {
                              nsEntry->cb.mVoidCallbackFunc(thisObject, callArgc, callArgv);
                              gCallStack.popFrame();

                              if (code[ip] == OP_POP_STK)
                              {
                                    ip++;
                                    break;
                              }

                              #ifdef TORQUE_DEBUG //ElfScript on debug only but then always :P
                                    Con::warnf(ConsoleLogEntry::General, "%s: Call to %s in %s uses result of void function call.", getFileLine(ip - 4), fnName, functionName);
                              // if (Con::getBoolVariable("$Con::warnVoidAssignment", true))
                              // {
                              //       Con::warnf(ConsoleLogEntry::General, "%s: Call to %s in %s uses result of void function call.", getFileLine(ip - 4), fnName, functionName);
                              // }
                              #endif
                              stack[_STK + 1].setEmptyString();
                              PUSH_STK();

                              break;
                        }
                        case Namespace::Entry::BoolCallbackType:
                        {
                              bool result = nsEntry->cb.mBoolCallbackFunc(thisObject, callArgc, callArgv);
                              gCallStack.popFrame();

                              if (code[ip] == OP_POP_STK)
                              {
                                    ip++;
                                    break;
                              }

                              stack[_STK + 1].setBool(result);
                              PUSH_STK();

                              break;
                        }
                  } // switch (nsEntry->mType)
            }
      }
      DISPATCH();
} //OP_CALLFUNC

// ~~~~~~~~~~~~~~~~~ STR
handle_OP_ADVANCE_STR_APPENDCHAR:
{
      char buff[2];
      buff[0] = (char)code[ip++];
      buff[1] = '\0';

      S32 len;
      const char* concat = tsconcat(stack[_STK].getString(), buff, len);

      stack[_STK].setStringRef(concat, len);
      DISPATCH();
}

handle_OP_REWIND_STR:
      // TORQUE_CASE_FALLTHROUGH;
handle_OP_TERMINATE_REWIND_STR:
{
      S32 len;
      const char* concat = tsconcat(stack[_STK - 1].getString(), stack[_STK].getString(), len);

      stack[_STK - 1].setStringRef(concat, len);
      POP_STK();
      DISPATCH();
}

handle_OP_COMPARE_STR:
      stack[_STK - 1].setBool(!dStricmp(stack[_STK].getString(), stack[_STK - 1].getString()));
      POP_STK();
      DISPATCH();
// ~~~~~~~~~~~~~~~~~ STACK
handle_OP_PUSH:
      gCallStack.push((stack[_STK--]));
      DISPATCH();

handle_OP_PUSH_FRAME:
      gCallStack.pushFrame(code[ip++]);
      DISPATCH();


// ~~~~~~~~~~~~~~~~~ ASSERT/BREAK
handle_OP_ASSERT:
{
      if (!stack[_STK--].getBool())
      {
            const char* message = curStringTable + code[ip];

            U32 breakLine, inst;
            findBreakLine(ip - 1, breakLine, inst);

            if (PlatformAssert::processAssert(PlatformAssert::Fatal,
                  name ? name : "eval",
                  breakLine,
                  message))
            {
                  // FIXME ?
                  // if (TelDebugger && TelDebugger->isConnected() && breakLine > 0)
                  // {
                  //    TelDebugger->breakProcess();
                  // }
                  // else
                  Platform::debugBreak();
            }
      }

      ip++;
      DISPATCH();
}

handle_OP_BREAK:
{
      //append the ip and codeptr before managing the breakpoint!
      AssertFatal(!Script::gEvalState.stack.empty(), "Empty eval stack on break!");
      Script::gEvalState.getCurrentFrame().module = this;
      Script::gEvalState.getCurrentFrame().ip = ip - 1;

      U32 breakLine;
      U32 curOpCode = code[ip]; //XXTH we dont have that here
      findBreakLine(ip - 1, breakLine, curOpCode);
      if (!breakLine)
            DISPATCH_OPCODE(curOpCode); // goto breakContinue;
      //FIXME? TelDebugger->executionStopped(this, breakLine);

      DISPATCH_OPCODE(curOpCode); //goto breakContinue;
}

// ~~~~~~~~~~~~~~~~~ ITER (foreach)
handle_OP_ITER_BEGIN:
{
      U32 mode = code[ip]; ip++; // i emmit the mode now

      bool isGlobal = code[ip];

      U32 failIp = code[ip + (isGlobal ? 3 : 2)];

      IterStackRecord& iter = iterStack[_ITER];
      iter.mIsGlobalVariable = isGlobal;

      iter.mMode = mode;

      if (isGlobal)
      {
            StringTableEntry varName = CodeToSTE(code, ip + 1);
            iter.mVar.mVariable = Con::gGlobalVars.add(varName);
      }
      else
      {
            iter.mVar.mRegister = code[ip + 1];
      }


      switch (iter.mMode) {
            case 1: // string
            {
                  iter.mData.mStr.mString = stack[_STK].getString();
                  iter.mData.mStr.mIndex = 0;
            }
            break;


            case 102: // in range
                  TORQUE_CASE_FALLTHROUGH;
            case 2: // Range a..b
            {
                  iter.mData.mRange.mEnd   = stack[_STK].getInt();
                  POP_STK(); //pop the param
                  iter.mData.mRange.mStart = stack[_STK].getInt();

                  if (iter.mData.mRange.mStart > iter.mData.mRange.mEnd) iter.mData.mRange.mInc = -1;
                  else iter.mData.mRange.mInc = 1;
                  if ( iter.mMode == 102 ) {
                        iter.mData.mRange.mStop = iter.mData.mRange.mEnd;
                        iter.mMode = 2;
                  } else {
                        iter.mData.mRange.mStop = iter.mData.mRange.mEnd + iter.mData.mRange.mInc;

                  }
            }
            break;

            case 103: // in range start..stop + step
                  TORQUE_CASE_FALLTHROUGH;
            case  3: // first..last + step
            {
                  iter.mData.mRange.mInc   = stack[_STK].getInt();
                  POP_STK();
                  iter.mData.mRange.mEnd   = stack[_STK].getInt();
                  POP_STK();
                  iter.mData.mRange.mStart = stack[_STK].getInt();

                  // validate correct step
                  int start = iter.mData.mRange.mStart;
                  int end   = iter.mData.mRange.mEnd;
                  int inc   = iter.mData.mRange.mInc;

                  if ((inc == 0) || (start < end && inc < 0) || (start > end && inc > 0)) {
                        Con::errorf("Runtime Error: Foreach invalid step supplied! %d .. %d step: %d",
                                    iter.mData.mRange.mStart, iter.mData.mRange.mEnd
                                    , iter.mData.mRange.mInc);

                        ip = failIp;
                        POP_STK();
                        DISPATCH();
                  }


                  if ( iter.mMode == 103 ) {
                        iter.mData.mRange.mStop = end;
                  } else {
                        if (inc > 0) iter.mData.mRange.mStop = end + 1;
                        else iter.mData.mRange.mStop = end - 1;
                  }

                  iter.mMode = 2; // overwrite to mode 2 .. same calulation only with variable inrement
            }
            break;

            case 104: //for i in range 10 only one parameter . does 0..9
            {
                  iter.mData.mRange.mEnd   = stack[_STK].getInt();
                  iter.mData.mRange.mStart = 0;

                  if (iter.mData.mRange.mStart > iter.mData.mRange.mEnd) iter.mData.mRange.mInc = -1;
                  else iter.mData.mRange.mInc = 1;
                  iter.mData.mRange.mStop = iter.mData.mRange.mEnd;
                  iter.mMode = 2; // overwrite to mode 2 .. same calulation only with variable inrement
            }
            break;

            default: //0/default => SimObject
            {
                  // Look up the object.

                  SimSet* set;
                  if (!Sim::findObject(stack[_STK].getString(), set))
                  {
                        Con::errorf(ConsoleLogEntry::General, "No SimSet object '%s'", stack[_STK].getString());
                        Con::errorf(ConsoleLogEntry::General, "Did you mean to use 'foreach$' instead of 'foreach'?");
                        ip = failIp;
                        // Pop the iterated value
                        POP_STK();
                        DISPATCH(); // continue;
                  }

                  // Set up.

                  iter.mData.mObj.mSet = set;
                  iter.mData.mObj.mIndex = 0;

            }
            break;
      }


      _ITER++;
      iterDepth++;

      ip += isGlobal ? 4 : 3;
      DISPATCH();
}


handle_OP_ITER:
{
      U32 breakIp = code[ip];
      IterStackRecord& iter = iterStack[_ITER - 1];

      switch (iter.mMode) {
            case 1: // String
            {
                  const char* str = iter.mData.mStr.mString;

                  U32 startIndex = iter.mData.mStr.mIndex;
                  U32 endIndex = startIndex;

                  // Break if at end.

                  if (!str[startIndex])
                  {
                        ip = breakIp;
                        DISPATCH(); // continue;
                  }

                  // Find right end of current component.

                  if (!dIsspace(str[endIndex])) {
                        while (str[endIndex] && !dIsspace(str[endIndex])) {
                              ++endIndex;
                        }
                        // do ++endIndex;
                        // while (str[endIndex] && !dIsspace(str[endIndex]));
                  }


                  // Extract component.

                  if (endIndex != startIndex)
                  {
                        char savedChar = str[endIndex];
                        const_cast<char*>(str)[endIndex] = '\0'; // We are on the string stack so this is okay.

                        if (iter.mIsGlobalVariable)
                              iter.mVar.mVariable->setStringValue(&str[startIndex]);
                        else
                              Script::gEvalState.setLocalStringVariable(iter.mVar.mRegister, &str[startIndex], endIndex - startIndex);

                        const_cast<char*>(str)[endIndex] = savedChar;
                  }
                  else
                  {
                        if (iter.mIsGlobalVariable)
                              iter.mVar.mVariable->setStringValue("");
                        else
                              Script::gEvalState.setLocalStringVariable(iter.mVar.mRegister, "", 0);
                  }

                  // Skip separator.
                  if (str[endIndex] != '\0')
                        ++endIndex;

                  iter.mData.mStr.mIndex = endIndex;

            } //string end
            break;

            case 2: // i in ....
            {
                  S32 needle = iter.mData.mRange.mStart;
                  bool contiueITER = true;
                  S32 step = iter.mData.mRange.mInc;

                  if (step > 0) {
                        contiueITER = (needle < iter.mData.mRange.mStop);
                  } else {
                        contiueITER = (needle > iter.mData.mRange.mStop);
                  }

                  if (!contiueITER) {
                        ip = breakIp;
                        DISPATCH();
                  }


                  if (iter.mIsGlobalVariable)
                        iter.mVar.mVariable->setIntValue(needle);
                  else {
                        // faster ?
                        ConsoleValue& stackRef = Script::gEvalState.currentRegisterArray->values[iter.mVar.mRegister];
                        if ( stackRef.type == ConsoleValueType::cvInteger) {
                              stackRef.i = needle;
                        } else {
                              stackRef.setFastInt(needle);
                        }

                        // default:
                        // Script::gEvalState.setLocalIntVariable(iter.mVar.mRegister, needle);


                  }


                  iter.mData.mRange.mStart += step;


            } //RANGE
            break;

            default: //SimSet 0 or any other
            {
                  U32 index = iter.mData.mObj.mIndex;
                  SimSet* set = iter.mData.mObj.mSet;

                  if (index >= set->size())
                  {
                        ip = breakIp;
                        DISPATCH(); // continue;
                  }

                  SimObjectId id = set->at(index)->getId();

                  if (iter.mIsGlobalVariable)
                        iter.mVar.mVariable->setIntValue(id);
                  else
                        Script::gEvalState.setLocalIntVariable(iter.mVar.mRegister, id);

                  iter.mData.mObj.mIndex = index + 1;
            }//SIMSET
            break;

      }

      ++ip;
      DISPATCH();
}

handle_OP_ITER_END:
{
      POP_ITER();
      DISPATCH();;
}

// ~~~~~~~~~~~~~~~~~ VECTOR_STRING
#ifdef ENABLE_CONSOLE_VECTOR
// PoD !! :D if count < 4 we get into vector mode :)
handle_OP_BUILD_VECTOR_STRING: {
      // read the count
      U32 count = code[ip++];

      const U32 MAX_ELEMENTS = 16;
      const char* stringValues[MAX_ELEMENTS];
      if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;
      bool matchVectorFields = count <= CONSOLE_VALUE_VECTOR_FIELD_COUNT;
      ConsoleVector cv = {0};
      // get values from stack
      for (S32 i = count - 1; i >= 0; i--) {
            if (matchVectorFields) cv.points[i] = static_cast<F32> (stack[_STK].getFloat());
            else stringValues[i] = stack[_STK].getString();
            POP_STK();
      }

      static char buffer[256];
      if (!matchVectorFields) {
            // i have to translate it to a string again :(
            S32 offset = 0;
            buffer[0] = '\0';

            for (U32 i = 0; i < count; i++) {
                  offset += dSprintf(buffer + offset
                  , sizeof(buffer) - offset
                  , (i == 0) ? "%s" : " %s", stringValues[i]);
            }
      }

      PUSH_STK();

      // after setString!!
      if (matchVectorFields) {
            stack[_STK].type = ConsoleValueType::cvVector;
            // Con::debugf("Set value type to ConsoleValueType::cvVector");
            // copy  to stack
            dMemcpy(stack[_STK].v.points, cv.points, sizeof(ConsoleVector::points));
      } else {
            stack[_STK].setString(buffer);
      }

      DISPATCH();
}
#else // #ifdef ENABLE_CONSOLE_VECTOR
handle_OP_BUILD_VECTOR_STRING: {
      // read the count
      U32 count = code[ip++];

      const U32 MAX_ELEMENTS = 16;
      const char* stringValues[MAX_ELEMENTS];

      if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;

      // get values from stack
      for (S32 i = count - 1; i >= 0; i--) {
            stringValues[i] = stack[_STK].getString();
            POP_STK();
      }

      // i have to translate it to a string again :(
      char buffer[256];
      S32 offset = 0;
      buffer[0] = '\0';

      for (U32 i = 0; i < count; i++) {
            offset += dSprintf(buffer + offset
            , sizeof(buffer) - offset
            , (i == 0) ? "%s" : " %s", stringValues[i]);
      }

      PUSH_STK();
      stack[_STK].setString(buffer);

      DISPATCH();
}
#endif // #ifdef ENABLE_CONSOLE_VECTOR
// ~~~~~~~~~~~~~~~~~ SAVEFIELD_FASTPATH
// NOTE placed under handle_OP_SAVEFIELD_FLT:

// ~~~~~~~~~~~~~~~~~ EXPERIMENTAL UNIT
#ifdef ELFSCRIPT_INT_HACK
handle_OP_CMPLT_UINT:
      doIntOperation<IntegerOperation::LT>();
      DISPATCH();
handle_OP_CMPGR_UINT:
      doIntOperation<IntegerOperation::GT>();
      DISPATCH();
handle_OP_CMPLE_UINT:
      doIntOperation<IntegerOperation::LE>();
      DISPATCH();
handle_OP_CMPGE_UINT:
      doIntOperation<IntegerOperation::GE>();
      DISPATCH();
handle_OP_CMPEQ_UINT:
      doIntOperation<IntegerOperation::EQ>();
      DISPATCH();
handle_OP_CMPNE_UINT:
      doIntOperation<IntegerOperation::NE>();
      DISPATCH();

handle_OP_INC_UINT:
      reg = code[ip++];
      currentRegister = reg;
      Script::gEvalState.setLocalIntVariable(reg, Script::gEvalState.getLocalIntVariable(reg) + 1.0);
      DISPATCH();

#endif

// ~~~~~~~~~~~~~~~~~ INVALID
handle_OP_INVALID:
      AssertISV(false, "Invalid OPCode Processed!");
      goto execFinished;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~ F A L L  B A C K ~~~~~~~~~
// handle_FALLBACK_SWITCH:
// {
//    // U32 instruction = code[ip++];
//    U32 instruction = code[ip -1];
//  // to For or not to for that is the question: for (;;) {
//    breakContinue:
//       switch (instruction)
//       {
//       case OP_FUNC_DECL:
//       {
//          //NOTE XXTH we have noCalls but we want to load the functions!
//             // NOTE rolled back cause memory leak!!
//          //orig: if (!noCalls)
//          {
//             fnName = CodeToSTE(code, ip);
//             fnNamespace = CodeToSTE(code, ip + 2);
//             fnPackage = CodeToSTE(code, ip + 4);
//             bool hasBody = (code[ip + 6] & 0x01) != 0;
//
//             Namespace::unlinkPackages();
//             if (fnNamespace == NULL && fnPackage == NULL)
//                ns = Namespace::global();
//             else
//                ns = Namespace::find(fnNamespace, fnPackage);
//
//             ns->addFunction(fnName, this, hasBody ? ip : 0);
//
//             if (curNSDocBlock)
//             {
//                if (fnNamespace == StringTable->lookup(nsDocBlockClass))
//                {
//                   char* usageStr = dStrdup(curNSDocBlock);
//                   usageStr[dStrlen(usageStr)] = '\0';
//                   ns->mUsage = usageStr;
//                   ns->mCleanUpUsage = true;
//                   curNSDocBlock = NULL;
//                }
//             }
//
//             const U32 fnArgc = code[ip + 8];
//
//             Namespace::Entry* temp = ns->lookup(fnName);
//             temp->mArgFlags.setSize(fnArgc);
//             temp->mDefaultOffsets.setSize(fnArgc);
//
//             // Arg flags: ip + 10 + fnArgc
//             // Codelet IPs: ip + 10 + 2*fnArgc
//             const U32 flagBase = ip + 10 + fnArgc;
//             const U32 offsetBase = ip + 10 + 2 * fnArgc;
//
//             for (U32 fa = 0; fa < fnArgc; ++fa)
//             {
//                temp->mArgFlags[fa] = code[flagBase + fa];
//                temp->mDefaultOffsets[fa] = code[offsetBase + fa];
//             }
//
//             // No stack pops: mDefaultValues is gone.
//
//             Namespace::relinkPackages();
//             curFNDocBlock = NULL;
//          }
//
//          // Jump past header + body + codelets.  endIp is at code[ip + 7].
//          ip = code[ip + 7];
//          break;
//       }
//
//       case OP_DEFAULT_END:
//       {
//          returnValue = stack[_STK];
//          POP_STK();
//
//          while (iterDepth > 0)
//          {
//             iterStack[--_ITER].mIsStringIter = false;
//             --iterDepth;
//             POP_STK();
//          }
//
//          goto execFinished;
//       }
//
//       case OP_CREATE_OBJECT:
//       {
//          // Read some useful info.
//          objParent = CodeToSTE(code, ip);
//          // bool isDataBlock = code[ip + 2];
//          bool isInternal = code[ip + 3];
//          bool isSingleton = code[ip + 4];
//          U32  lineNumber = code[ip + 5];
//          failJump = code[ip + 6];
//
//          // If we don't allow calls, we certainly don't allow creating objects!
//          // Moved this to after failJump is set. Engine was crashing when
//          // noCalls = true and an object was being created at the beginning of
//          // a file. ADL.
//          if (noCalls)
//          {
//             ip = failJump;
//             break;
//          }
//
//          // Push the old info to the stack
//          //Assert( objectCreationStackIndex < objectCreationStackSize );
//          objectCreationStack[objectCreationStackIndex].newObject = currentNewObject;
//          objectCreationStack[objectCreationStackIndex++].failJump = failJump;
//
//          // Get the constructor information off the stack.
//          gCallStack.argvc(NULL, callArgc, &callArgv);
//          AssertFatal(callArgc - 3 >= 0, avar("Call Arg needs at least 3, only has %d", callArgc));
//          const char* objectName = callArgv[2].getString();
//
//          // Con::printf("Creating object...");
//
//          // objectName = argv[1]...
//          currentNewObject = NULL;
//
//          // Are we creating a datablock? If so, deal with case where we override
//          // an old one.
//    /*      if (isDataBlock)
//          {
//             // Con::printf("  - is a datablock");
//
//             // Find the old one if any.
//             SimObject* db = Sim::getDataBlockGroup()->findObject(objectName);
//
//             // Make sure we're not changing types on ourselves...
//             if (db && dStricmp(db->getClassName(), callArgv[1].getString()))
//             {
//                Con::errorf(ConsoleLogEntry::General, "Cannot re-declare data block %s with a different class.", objectName);
//                ip = failJump;
//                gCallStack.popFrame();
//                break;
//             }
//
//             // If there was one, set the currentNewObject and move on.
//             if (db)
//                currentNewObject = db;
//          }
//          else */if (!isInternal)
//          {
//             AbstractClassRep* rep = AbstractClassRep::findClassRep(objectName);
//             if (rep != NULL)
//             {
//                Con::errorf(ConsoleLogEntry::General, "%s: Cannot name object [%s] the same name as a script class.",
//                   getFileLine(ip), objectName);
//                ip = failJump;
//                gCallStack.popFrame();
//                break;
//             }
//
//             SimObject* obj = Sim::findObject((const char*)objectName);
//             if (obj)
//             {
//                if (isSingleton)
//                {
//                   // Make sure we're not trying to change types
//                   if (dStricmp(obj->getClassName(), callArgv[1].getString()) != 0)
//                   {
//                      Con::errorf(ConsoleLogEntry::General, "%s: Cannot re-declare object [%s] with a different class [%s] - was [%s].",
//                         getFileLine(ip), objectName, callArgv[1].getString(), obj->getClassName());
//                      ip = failJump;
//                      gCallStack.popFrame();
//                      break;
//                   }
//
//                   // We're creating a singleton, so use the found object instead of creating a new object.
//                   currentNewObject = obj;
//                   Con::warnf("%s: Singleton Object was already created with name %s. Using existing object.",
//                      getFileLine(ip), objectName);
//                }
//             }
//          }
//
//          gCallStack.popFrame();
//
//          if (!currentNewObject)
//          {
//             // Well, looks like we have to create a new object.
//             ConsoleObject* object = ConsoleObject::create(callArgv[1].getString());
//
//             // Deal with failure!
//             if (!object)
//             {
//                Con::errorf(ConsoleLogEntry::General, "%s: Unable to instantiate non-conobject class %s.", getFileLine(ip - 1), callArgv[1].getString());
//                ip = failJump;
//                break;
//             }
//
//             // Do special datablock init if appropros
//             // if (isDataBlock)
//             // {
//             //    SimDataBlock* dataBlock = dynamic_cast<SimDataBlock*>(object);
//             //    if (dataBlock)
//             //    {
//             //       dataBlock->assignId();
//             //    }
//             //    else
//             //    {
//             //       // They tried to make a non-datablock with a datablock keyword!
//             //       Con::errorf(ConsoleLogEntry::General, "%s: Unable to instantiate non-datablock class %s.", getFileLine(ip - 1), callArgv[1].getString());
//             //
//             //       // Clean up...
//             //       delete object;
//             //       currentNewObject = NULL;
//             //       ip = failJump;
//             //       break;
//             //    }
//             // }
//
//             // Finally, set currentNewObject to point to the new one.
//             currentNewObject = dynamic_cast<SimObject*>(object);
//
//             // Deal with the case of a non-SimObject.
//             if (!currentNewObject)
//             {
//                Con::errorf(ConsoleLogEntry::General, "%s: Unable to instantiate non-SimObject class %s.", getFileLine(ip - 1), callArgv[1].getString());
//                delete object;
//                ip = failJump;
//                break;
//             }
//
//             // Set the declaration line
//             currentNewObject->setDeclarationLine(lineNumber);
//
//             // Set the file that this object was created in
//             currentNewObject->setFilename(this->name);
//
//             // Does it have a parent object? (ie, the copy constructor : syntax, not inheriance)
//             if (*objParent)
//             {
//                // Find it!
//                SimObject* parent;
//                if (Sim::findObject(objParent, parent))
//                {
//                   // Con::printf(" - Parent object found: %s", parent->getClassName());
//
//                   currentNewObject->setCopySource(parent);
//                   currentNewObject->assignFieldsFrom(parent);
//
//                   // copy any substitution statements
//                   // SimDataBlock* parent_db = dynamic_cast<SimDataBlock*>(parent);
//                   // if (parent_db)
//                   // {
//                   //    SimDataBlock* currentNewObject_db = dynamic_cast<SimDataBlock*>(currentNewObject);
//                   //    if (currentNewObject_db)
//                   //       currentNewObject_db->copySubstitutionsFrom(parent_db);
//                   // }
//                }
//                else
//                {
//                   if (Con::gObjectCopyFailures == -1)
//                      Con::errorf(ConsoleLogEntry::General, "%s: Unable to find parent object %s for %s.", getFileLine(ip - 1), objParent, callArgv[1].getString());
//                   ++Con::gObjectCopyFailures;
//
//                   delete object;
//                   currentNewObject = NULL;
//                   ip = failJump;
//                   break;
//                }
//             }
//
//             // If a name was passed, assign it.
//             if (objectName[0])
//             {
//                if (!isInternal)
//                   currentNewObject->assignName(objectName);
//                else
//                   currentNewObject->setInternalName(objectName);
//
//                // Set the original name
//                currentNewObject->setOriginalName( objectName );
//             }
//
//             // Do the constructor parameters.
//             if (!currentNewObject->processArguments(callArgc - 3, callArgv + 3))
//             {
//                delete currentNewObject;
//                currentNewObject = NULL;
//                ip = failJump;
//                break;
//             }
//
//             // If it's not a datablock, allow people to modify bits of it.
//             // if (!isDataBlock)
//             // {
//             //    currentNewObject->setModStaticFields(true);
//             //    currentNewObject->setModDynamicFields(true);
//             // }
//          }
//          else
//          {
//             currentNewObject->reloadReset(); // AFX (reload-reset)
//
//             // Does it have a parent object? (ie, the copy constructor : syntax, not inheriance)
//             if (*objParent)
//             {
//                // Find it!
//                SimObject* parent;
//                if (Sim::findObject(objParent, parent))
//                {
//                   // Con::printf(" - Parent object found: %s", parent->getClassName());
//
//                   // temporarily block name change
//                   SimObject::preventNameChanging = true;
//                   currentNewObject->setCopySource(parent);
//                   currentNewObject->assignFieldsFrom(parent);
//                   // restore name changing
//                   SimObject::preventNameChanging = false;
//
//                   // copy any substitution statements
//                   // SimDataBlock* parent_db = dynamic_cast<SimDataBlock*>(parent);
//                   // if (parent_db)
//                   // {
//                   //    SimDataBlock* currentNewObject_db = dynamic_cast<SimDataBlock*>(currentNewObject);
//                   //    if (currentNewObject_db)
//                   //       currentNewObject_db->copySubstitutionsFrom(parent_db);
//                   // }
//                }
//                else
//                {
//                   Con::errorf(ConsoleLogEntry::General, "%d: Unable to find parent object %s for %s.", lineNumber, objParent, callArgv[1].getString());
//                }
//             }
//          }
//
//          // Advance the IP past the create info...
//          ip += 7;
//          break;
//       }
//
//       case OP_ADD_OBJECT:
//       {
//          // See OP_SETCURVAR for why we do this.
//          curFNDocBlock = NULL;
//          curNSDocBlock = NULL;
//
//          // Do we place this object at the root?
//          bool placeAtRoot = code[ip++];
//
//          // Con::printf("Adding object %s", currentNewObject->getName());
//
//          // Make sure it wasn't already added, then add it.
//          if (currentNewObject == NULL)
//          {
//             break;
//          }
//
//          bool isMessage = dynamic_cast<Message*>(currentNewObject) != NULL;
//
//          if (currentNewObject->isProperlyAdded() == false)
//          {
//             bool ret = false;
//             if (isMessage)
//             {
//                SimObjectId id = Message::getNextMessageID();
//                if (id != 0xffffffff)
//                   ret = currentNewObject->registerObject(id);
//                else
//                   Con::errorf("%s: No more object IDs available for messages", getFileLine(ip));
//             }
//             else
//                ret = currentNewObject->registerObject();
//
//             if (!ret)
//             {
//                // This error is usually caused by failing to call Parent::initPersistFields in the class' initPersistFields().
//                Con::warnf(ConsoleLogEntry::General, "%s: Register object failed for object %s of class %s.", getFileLine(ip - 2), currentNewObject->getName(), currentNewObject->getClassName());
//                ++Con::gObjectCopyFailures;
//                delete currentNewObject;
//                currentNewObject = NULL;
//                ip = failJump;
//                break;
//             }
//          }
//
//          // Are we dealing with a datablock?
//          // SimDataBlock* dataBlock = dynamic_cast<SimDataBlock*>(currentNewObject);
//          // String errorStr;
//          //
//          // // If so, preload it.
//          // if (dataBlock && !dataBlock->preload(true, errorStr))
//          // {
//          //    Con::errorf(ConsoleLogEntry::General, "%s: preload failed for %s: %s.", getFileLine(ip - 2),
//          //       currentNewObject->getName(), errorStr.c_str());
//          //    ++Con::gObjectCopyFailures;
//          //    dataBlock->deleteObject();
//          //    currentNewObject = NULL;
//          //    ip = failJump;
//          //    break;
//          // }
//
//          // What group will we be added to, if any?
//          U32 groupAddId = (U32)stack[_STK].getInt();
//          SimGroup* grp = NULL;
//          SimSet* set = NULL;
//
//          if (!placeAtRoot || !currentNewObject->getGroup())
//          {
//             if (!isMessage)
//             {
//                if (!placeAtRoot)
//                {
//                   // Otherwise just add to the requested group or set.
//                   if (!Sim::findObject(groupAddId, grp))
//                      Sim::findObject(groupAddId, set);
//                }
//
//                if (placeAtRoot)
//                {
//                   // Deal with the instantGroup if we're being put at the root or we're adding to a component.
//                   if (Con::gInstantGroup.isEmpty() || !Sim::findObject(Con::gInstantGroup, grp))
//                      grp = Sim::getRootGroup();
//                }
//             }
//
//             // If we didn't get a group, then make sure we have a pointer to
//             // the rootgroup.
//             if (!grp)
//                grp = Sim::getRootGroup();
//
//             // add to the parent group
//             grp->addObject(currentNewObject);
//
//             // If for some reason the add failed, add the object to the
//             // root group so it won't leak.
//             if (currentNewObject->getGroup() == NULL)
//                Sim::getRootGroup()->addObject(currentNewObject);
//
//             // add to any set we might be in
//             if (set)
//                set->addObject(currentNewObject);
//          }
//
//          // store the new object's ID on the stack (overwriting the group/set
//          // id, if one was given, otherwise getting pushed)
//          S32 id = currentNewObject->getId();
//          if (placeAtRoot)
//             stack[_STK].setInt(id);
//          else
//             stack[++_STK].setInt(id);
//
//          break;
//       }
//
//       case OP_END_OBJECT:
//       {
//          // If we're not to be placed at the root, make sure we clean up
//          // our group reference.
//          bool placeAtRoot = code[ip++];
//          if (!placeAtRoot)
//             POP_STK();
//          break;
//       }
//
//       case OP_FINISH_OBJECT:
//       {
//          if (currentNewObject)
//             currentNewObject->onPostAdd();
//
//          AssertFatal( objectCreationStackIndex >= 0, "Object Stack is empty." );
//          // Restore the object info from the stack [7/9/2007 Black]
//          currentNewObject = objectCreationStack[--objectCreationStackIndex].newObject;
//          failJump = objectCreationStack[objectCreationStackIndex].failJump;
//          break;
//       }
//
//       case OP_JMPIFFNOT:
//          if (stack[_STK--].getFloat())
//          {
//             ip++;
//             break;
//          }
//          ip = code[ip];
//          break;
//       case OP_JMPIFNOT:
//          if (stack[_STK--].getInt())
//          {
//             ip++;
//             break;
//          }
//
//          ip = code[ip];
//          break;
//       case OP_JMPNOTSTRING:
//          if (stack[_STK--].getBool())
//          {
//             ip++;
//             break;
//          }
//          ip = code[ip];
//          break;
//       case OP_JMPIFF:
//          if (!stack[_STK--].getFloat())
//          {
//             ip++;
//             break;
//          }
//          ip = code[ip];
//          break;
//       case OP_JMPIF:
//          if (!stack[_STK--].getFloat())
//          {
//             ip++;
//             break;
//          }
//          ip = code[ip];
//          break;
//       case OP_JMPIFNOT_NP:
//          if (stack[_STK].getInt())
//          {
//             POP_STK();
//             ip++;
//             break;
//          }
//          ip = code[ip];
//          break;
//       case OP_JMPIF_NP:
//          if (!stack[_STK].getInt())
//          {
//             POP_STK();
//             ip++;
//             break;
//          }
//          ip = code[ip];
//          break;
//       case OP_JMP:
//          ip = code[ip];
//          break;
//
//       case OP_RETURN_VOID:
//       {
//          if (iterDepth > 0)
//          {
//             // Clear iterator state.
//             while (iterDepth > 0)
//             {
//                iterStack[--_ITER].mIsStringIter = false;
//                --iterDepth;
//
//                POP_STK();     // this is a pop from foreach()
//             }
//          }
//
//          returnValue.setEmptyString();
//
//          goto execFinished;
//       }
//
//       case OP_RETURN:
//       {
//          returnValue = (stack[_STK]);
//          POP_STK();
//
//          // Clear iterator state.
//          while (iterDepth > 0)
//          {
//             iterStack[--_ITER].mIsStringIter = false;
//             --iterDepth;
//
//             POP_STK();
//          }
//
//          goto execFinished;
//       }
//       case OP_RETURN_FLT:
//          returnValue.setFloat(stack[_STK].getFloat());
//          POP_STK();
//
//          // Clear iterator state.
//          while (iterDepth > 0)
//          {
//             iterStack[--_ITER].mIsStringIter = false;
//             --iterDepth;
//
//             POP_STK();
//          }
//
//          goto execFinished;
//
//       case OP_RETURN_UINT:
//          returnValue.setInt(stack[_STK].getInt());
//          POP_STK();
//
//          // Clear iterator state.
//          while (iterDepth > 0)
//          {
//             iterStack[--_ITER].mIsStringIter = false;
//             --iterDepth;
//
//             POP_STK();
//          }
//
//          goto execFinished;
//
//       case OP_CMPEQ:
//          doFloatMathOperation<FloatOperation::EQ>();
//          break;
//
//       case OP_CMPGR:
//          doFloatMathOperation<FloatOperation::GR>();
//          break;
//
//       case OP_CMPGE:
//          doFloatMathOperation<FloatOperation::GE>();
//          break;
//
//       case OP_CMPLT:
//          doFloatMathOperation<FloatOperation::LT>();
//          break;
//
//       case OP_CMPLE:
//          doFloatMathOperation<FloatOperation::LE>();
//          break;
//
//       case OP_CMPNE:
//          doFloatMathOperation<FloatOperation::NE>();
//          break;
//
//       case OP_XOR:
//          doIntOperation<IntegerOperation::Xor>();
//          break;
//
//       case OP_BITAND:
//          doIntOperation<IntegerOperation::BitAnd>();
//          break;
//
//       case OP_BITOR:
//          doIntOperation<IntegerOperation::BitOr>();
//          break;
//
//       case OP_NOT:
//          stack[_STK].setBool(!stack[_STK].getInt());
//          break;
//
//       case OP_NOTF:
//          stack[_STK].setInt(!stack[_STK].getFloat());
//          break;
//
//       case OP_ONESCOMPLEMENT:
//          stack[_STK].setInt(~stack[_STK].getInt());
//          break;
//
//       case OP_SHR:
//          doIntOperation<IntegerOperation::RShift>();
//          break;
//
//       case OP_SHL:
//          doIntOperation<IntegerOperation::LShift>();
//          break;
//
//       case OP_AND:
//          doIntOperation<IntegerOperation::LogicalAnd>();
//          break;
//
//       case OP_OR:
//          doIntOperation<IntegerOperation::LogicalOr>();
//          break;
//
//       case OP_ADD:
//          doFloatMathOperation<FloatOperation::Add>();
//          break;
//
//       case OP_SUB:
//          doFloatMathOperation<FloatOperation::Sub>();
//          break;
//
//       case OP_MUL:
//          doFloatMathOperation<FloatOperation::Mul>();
//          break;
//
//       case OP_DIV:
//          doFloatMathOperation<FloatOperation::Div>();
//          break;
//
//       case OP_MOD:
//       {
//          S64 divisor = stack[_STK - 1].getInt();
//          if (divisor != 0)
//             stack[_STK - 1].setInt(stack[_STK].getInt() % divisor);
//          else
//             stack[_STK - 1].setInt(0);
//          POP_STK();
//          break;
//       }
//
//       case OP_NEG:
//          stack[_STK].setFloat(-stack[_STK].getFloat());
//          break;
//
//       case OP_INC:
//          reg = code[ip++];
//          currentRegister = reg;
//          Script::gEvalState.setLocalFloatVariable(reg, Script::gEvalState.getLocalFloatVariable(reg) + 1.0);
//          break;
//
// #ifdef ELFSCRIPT_INT_HACK
//       case OP_INC_UINT: // ElfScript
//          reg = code[ip++];
//          currentRegister = reg;
//          Script::gEvalState.setLocalIntVariable(reg, Script::gEvalState.getLocalIntVariable(reg) + 1);
//          break;
// #endif
//       case OP_SETCURVAR:
//          var = CodeToSTE(code, ip);
//          ip += 2;
//
//          // If a variable is set, then these must be NULL. It is necessary
//          // to set this here so that the vector parser can appropriately
//          // identify whether it's dealing with a vector.
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          // Used for local variable caching of what is active...when we
//          // set a global, we aren't active
//          currentRegister = -1;
//
//          Script::gEvalState.setCurVarName(var);
//
//          // In order to let docblocks work properly with variables, we have
//          // clear the current docblock when we do an assign. This way it
//          // won't inappropriately carry forward to following function decls.
//          curFNDocBlock = NULL;
//          curNSDocBlock = NULL;
//          break;
//
//       case OP_SETCURVAR_CREATE:
//          var = CodeToSTE(code, ip);
//          ip += 2;
//
//          // See OP_SETCURVAR
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          // Used for local variable caching of what is active...when we
//          // set a global, we aren't active
//          currentRegister = -1;
//
//          Script::gEvalState.setCurVarNameCreate(var);
//
//          // See OP_SETCURVAR for why we do this.
//          curFNDocBlock = NULL;
//          curNSDocBlock = NULL;
//          break;
//
//       case OP_SETCURVAR_ARRAY:
//          var = StringTable->insert(stack[_STK].getString());
//
//          // See OP_SETCURVAR
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          // Used for local variable caching of what is active...when we
//          // set a global, we aren't active
//          currentRegister = -1;
//
//          Script::gEvalState.setCurVarName(var);
//
//          // See OP_SETCURVAR for why we do this.
//          curFNDocBlock = NULL;
//          curNSDocBlock = NULL;
//          break;
//
//       case OP_SETCURVAR_ARRAY_CREATE:
//          var = StringTable->insert(stack[_STK].getString());
//
//          // See OP_SETCURVAR
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          // Used for local variable caching of what is active...when we
//          // set a global, we aren't active
//          currentRegister = -1;
//
//          Script::gEvalState.setCurVarNameCreate(var);
//
//          // See OP_SETCURVAR for why we do this.
//          curFNDocBlock = NULL;
//          curNSDocBlock = NULL;
//          break;
//
//       case OP_LOADVAR_UINT:
//          currentRegister = -1;
//          stack[_STK + 1].setInt(Script::gEvalState.getIntVariable());
//          _STK++;
//          break;
//
//       case OP_LOADVAR_FLT:
//          currentRegister = -1;
//          stack[_STK + 1].setFloat(Script::gEvalState.getFloatVariable());
//          _STK++;
//          break;
//
//
//       // ElfScript Optimization
//       case OP_LOADVAR_STR:
//       currentRegister = -1;
//       {
//             // i check the type first!
//             const Dictionary::Entry* varEntry = Script::gEvalState.currentVariable;
//
//             bool fastPath = false;
//             if (varEntry) {
//                   static S32 valueType = 0;
//                   valueType = varEntry->value.getType();
//                   fastPath =  valueType == ConsoleValueType::cvFloat ||
//                               valueType == ConsoleValueType::cvInteger;
//             }
//             if (fastPath)
//             {
//                   // Fastpath
//                   stack[_STK + 1] = varEntry->value;
//             }
//             else
//             {
//                   // Slowpath: Fallback
//                   stack[_STK + 1].setString(Script::gEvalState.getStringVariable());
//             }
//       }
//       _STK++;
//       break;
//
//
//       // orig:
//       // case OP_LOADVAR_STR:
//       //    currentRegister = -1;
//       //    stack[_STK + 1].setString(Script::gEvalState.getStringVariable());
//       //    _STK++;
//       //    break;
//
//       case OP_SAVEVAR_UINT:
//          Script::gEvalState.setIntVariable(stack[_STK].getInt());
//          break;
//
//       case OP_SAVEVAR_FLT:
//          Script::gEvalState.setFloatVariable(stack[_STK].getFloat());
//          break;
//
//       case OP_SAVEVAR_STR:
//             // ElfScript 0.4c rocket change !
//             // XXTH inlining drives me crazy here -- using kdevelop
//             // i go for speed not for most beautiful code :P
//             if (stack[_STK].type == cvInteger) {
//                   Script::gEvalState.setIntVariable(stack[_STK].getInt());
//                   break;
//             }
//
//             if (stack[_STK].type == cvFloat) {
//                   Script::gEvalState.setFloatVariable(stack[_STK].getFloat());
//                   break;
//             }
//
//          Script::gEvalState.setStringVariable(stack[_STK].getString());
//          break;
//
//       case OP_LOAD_LOCAL_VAR_UINT:
//          reg = code[ip++];
//          currentRegister = reg;
//
//          // See OP_SETCURVAR
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          stack[_STK + 1].setInt(Script::gEvalState.getLocalIntVariable(reg));
//          _STK++;
//          break;
//
//       case OP_LOAD_LOCAL_VAR_FLT:
//          reg = code[ip++];
//          currentRegister = reg;
//
//          // See OP_SETCURVAR
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          stack[_STK + 1].setFloat(Script::gEvalState.getLocalFloatVariable(reg));
//          _STK++;
//          break;
//
//          // ElfScript Optimization:
//       case OP_LOAD_LOCAL_VAR_STR:
//             reg = code[ip++];
//             currentRegister = reg;
//
//             // See OP_SETCURVAR
//             prevField = NULL;
//             prevObject = NULL;
//             curObject = NULL;
//             {
//                   const ConsoleValue& localVal = Script::gEvalState.currentRegisterArray->values[reg];
//                   if (localVal.getType() == ConsoleValueType::cvFloat ||
//                         localVal.getType() == ConsoleValueType::cvInteger)
//                   {
//                         //fast fetch
//                         stack[_STK + 1] = localVal;
//                   }
//                   else
//                   {
//                         // fallback
//                         val = Script::gEvalState.getLocalStringVariable(reg);
//                         stack[_STK + 1].setString(val);
//                   }
//             }
//             _STK++;
//             break;
//
//       // orig:
//       // case OP_LOAD_LOCAL_VAR_STR:
//       //    reg = code[ip++];
//       //    currentRegister = reg;
//       //
//       //    // See OP_SETCURVAR
//       //    prevField = NULL;
//       //    prevObject = NULL;
//       //    curObject = NULL;
//       //
//       //    val = Script::gEvalState.getLocalStringVariable(reg);
//       //    stack[_STK + 1].setString(val);
//       //    _STK++;
//       //    break;
//
//
//
//
//       case OP_SAVE_LOCAL_VAR_UINT:
//          reg = code[ip++];
//          currentRegister = reg;
//
//          // See OP_SETCURVAR
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          Script::gEvalState.setLocalIntVariable(reg, stack[_STK].getInt());
//          break;
//
//       case OP_SAVE_LOCAL_VAR_FLT:
//          reg = code[ip++];
//          currentRegister = reg;
//
//          // See OP_SETCURVAR
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          Script::gEvalState.setLocalFloatVariable(reg, stack[_STK].getFloat());
//          break;
//
//       case OP_SAVE_LOCAL_VAR_STR:
//          reg = code[ip++];
//          val = stack[_STK].getString();
//          currentRegister = reg;
//
//          // See OP_SETCURVAR
//          prevField = NULL;
//          prevObject = NULL;
//          curObject = NULL;
//
//          Script::gEvalState.setLocalStringVariable(reg, val, (S32)dStrlen(val));
//          break;
//
//       case OP_SETCUROBJECT:
//             //ElfScript XXTH found the holy grail for ?!
//             prevObject = curObject;
//             curObject = Sim::findObject(stack[_STK]);
//             break;
//
//
//             // orig lame duck:
//
//             // // Save the previous object for parsing vector fields.
//             // prevObject = curObject;
//             // val = stack[_STK].getString();
//             //
//             // // Sim::findObject will sometimes find valid objects from
//             // // multi-component strings. This makes sure that doesn't
//             // // happen.
//             // for (const char* check = val; *check; check++)
//             // {
//             //    if (*check == ' ')
//             //    {
//             //       val = "";
//             //       break;
//             //    }
//             // }
//             // curObject = Sim::findObject(val);
//             // break;
//
//       case OP_SETCUROBJECT_INTERNAL:
//          ++ip; // To skip the recurse flag if the object wasnt found
//          if (curObject)
//          {
//             SimSet* set = dynamic_cast<SimSet*>(curObject);
//             if (set)
//             {
//                StringTableEntry intName = StringTable->insert(stack[_STK].getString());
//                bool recurse = code[ip - 1];
//                SimObject* obj = set->findObjectByInternalName(intName, recurse);
//                stack[_STK].setInt(obj ? obj->getId() : 0);
//             }
//             else
//             {
//                Con::errorf(ConsoleLogEntry::Script, "%s: Attempt to use -> on non-set %s of class %s.", getFileLine(ip - 2), curObject->getName(), curObject->getClassName());
//                stack[_STK].setInt(0);
//             }
//          }
//          else
//          {
//             Con::errorf(ConsoleLogEntry::Script, "%s: Attempt to use ->, but the group object wasn't found.", getFileLine(ip - 2));
//             stack[_STK].setInt(0);
//          }
//          break;
//
//       case OP_SETCUROBJECT_NEW:
//          curObject = currentNewObject;
//          break;
//
//       case OP_SETCURFIELD:
//          // Save the previous field for parsing vector fields.
//          prevField = curField;
//          dStrcpy(prevFieldArray, curFieldArray, 256);
//          curField = CodeToSTE(code, ip);
//          curFieldArray[0] = 0;
//          ip += 2;
//          break;
//
//       case OP_SETCURFIELD_ARRAY:
//          dStrcpy(curFieldArray, stack[_STK].getString(), 256);
//          break;
//
//       case OP_SETCURFIELD_TYPE:
//          if(curObject)
//             curObject->setDataFieldType(code[ip], curField, curFieldArray);
//          ip++;
//          break;
//
// // #ifdef ELFSCRIPT_FASTPATH_FLD
// //       //XXTH FastPath HACK:
// //       case OP_LOADFIELD_UINT:
// //             if (curObject)
// //             {
// //                   bool fastPath = false;
// //                   const AbstractClassRep::Field *fld = curObject->findField(curField);
// //
// //                   if (fld)
// //                   {
// //                         const char* array = (const char*) curFieldArray;
// //                         S32 array1 = PARSE_ARRAY_INDEX(array);
// //
// //                         // Fastpath safety check for unmanaged, standard C++ fields
// //                         if (array1 == 0 && fld->writeDataFn == &defaultProtectedWriteFn
// //                               && fld->setDataFn == &defaultProtectedSetFn)
// //                         {
// //                               F64 val = 0.0;
// //                               if (curObject->getDataField(fld, val))
// //                               {
// //                                     // Convert the F64 from our fastpath directly to an integer on the stack
// //                                     // Note: Adjust .setInt() to your stack's actual integer/uint method if needed
// //                                     stack[_STK + 1].setInt((S64)val);
// //                                     fastPath = true;
// //                               }
// //                         }
// //                   }
// //
// //                   if (!fastPath)
// //                   {
// //                         // Fallback for dynamic fields or fields with custom C++ logic
// //                         stack[_STK + 1].setInt(dAtoi(curObject->getDataField(curField, curFieldArray)));
// //                   }
// //             }
// //             else
// //             {
// //                   // The field is not being retrieved from an object. Maybe it's
// //                   // a special accessor?
// //                   char buff[FieldBufferSizeNumeric];
// //                   memset(buff, 0, sizeof(buff));
// //                   getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff, currentRegister);
// //                   stack[_STK + 1].setInt(dAtoi(buff));
// //             }
// //             _STK++;
// //             break;
// // #else
// //       case OP_LOADFIELD_UINT:
// //          if (curObject)
// //             stack[_STK + 1].setInt(dAtol(curObject->getDataField(curField, curFieldArray)));
// //          else
// //          {
// //             // The field is not being retrieved from an object. Maybe it's
// //             // a special accessor?
// //             char buff[FieldBufferSizeNumeric];
// //             memset(buff, 0, sizeof(buff));
// //             getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff, currentRegister);
// //             stack[_STK + 1].setInt(dAtol(buff));
// //          }
// //          _STK++;
// //          break;
// // #endif //#ifdef ELFSCRIPT_FASTPATH_FLD
// //
// // #ifdef ELFSCRIPT_FASTPATH_FLD
// //          //XXTH Fastpath HACK
// //       case OP_LOADFIELD_FLT:
// //             if (curObject)
// //             {
// //                   bool fastPath = false;
// //                   const AbstractClassRep::Field *fld = curObject->findField(curField);
// //
// //                   if (fld)
// //                   {
// //                         const char* array = (const char*) curFieldArray;
// //                         S32 array1 = PARSE_ARRAY_INDEX(array);
// //
// //                         // Fastpath safety check for unmanaged, standard C++ fields
// //                         if (array1 == 0 && fld->writeDataFn == &defaultProtectedWriteFn
// //                               && fld->setDataFn == &defaultProtectedSetFn)
// //                         {
// //                               F64 val = 0.0;
// //                               if (curObject->getDataField(fld, val))
// //                               {
// //                                     stack[_STK + 1].setFloat(val);
// //                                     fastPath = true;
// //                               }
// //                         }
// //                   }
// //
// //                   if (!fastPath)
// //                   {
// //                         // Fallback for dynamic fields or fields with custom C++ logic
// //                         stack[_STK + 1].setFloat(dAtod(curObject->getDataField(curField, curFieldArray)));
// //                   }
// //             }
// //             else
// //             {
// //                   // The field is not being retrieved from an object. Maybe it's
// //                   // a special accessor?
// //                   char buff[FieldBufferSizeNumeric];
// //                   memset(buff, 0, sizeof(buff));
// //                   getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff, currentRegister);
// //                   stack[_STK + 1].setFloat(dAtod(buff));
// //             }
// //             _STK++;
// //             break;
// // #else //#ifdef ELFSCRIPT_FASTPATH_FLD
// //       case OP_LOADFIELD_FLT:
// //          if (curObject)
// //             stack[_STK + 1].setFloat(dAtod(curObject->getDataField(curField, curFieldArray)));
// //          else
// //          {
// //             // The field is not being retrieved from an object. Maybe it's
// //             // a special accessor?
// //             char buff[FieldBufferSizeNumeric];
// //             memset(buff, 0, sizeof(buff));
// //             getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff, currentRegister);
// //             stack[_STK + 1].setFloat(dAtod(buff));
// //          }
// //          _STK++;
// //          break;
// // #endif
//
//       case OP_LOADFIELD_STR:
//          if (curObject)
//          {
//             curObject->stackDataField(curField, curFieldArray, &stack[_STK + 1]);
//
//             // orig:
//             // val = curObject->getDataField(curField, curFieldArray);
//             // stack[_STK + 1].setString(val);
//          }
//          else
//          {
//             // The field is not being retrieved from an object. Maybe it's
//             // a special accessor?
//             char buff[FieldBufferSizeString];
//             memset(buff, 0, sizeof(buff));
//             getFieldComponent(prevObject, prevField, prevFieldArray, curField, buff, currentRegister);
//             stack[_STK + 1].setString(buff);
//          }
//          _STK++;
//          break;
//
// // #ifdef ELFSCRIPT_FASTPATH_FLD
// //       //XXTH fastPath :
// //       case OP_SAVEFIELD_UINT:
// //             if (curObject)
// //             {
// //                   bool fastPath = false;
// //                   const AbstractClassRep::Field *fld = curObject->findField(curField);
// //
// //                   if (fld)
// //                   {
// //                         const char* array = (const char*) curFieldArray;
// //                         S32 array1 = PARSE_ARRAY_INDEX(array);
// //
// //                         if (array1 == 0 && fld->writeDataFn == &defaultProtectedWriteFn
// //                               && fld->setDataFn == &defaultProtectedSetFn
// //                               && fld->flag == 0
// //                         ) {
// //                               fastPath = curObject->setDataField(fld, (F64)stack[_STK].getInt());
// //                         }
// //                   }
// //
// //                   if (!fastPath)
// //                   {
// //                         curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
// //                   }
// //             }
// //             else
// //             {
// //                   // The field is not being set on an object. Maybe it's a special accessor?
// //                   setFieldComponent(prevObject, prevField, prevFieldArray, curField, currentRegister);
// //                   prevObject = NULL;
// //             }
// //             break;
// //
// //       case OP_SAVEFIELD_FLT:
// //             if (curObject) {
// //                   //XXTH Fastpath:
// //                   bool fastPath  = false;
// //                   const AbstractClassRep::Field *fld = curObject->findField(curField);
// //                   if (fld) {
// //                         const char* array = (const char*) curFieldArray;
// //                         S32 array1 = PARSE_ARRAY_INDEX(array);
// //
// //                         if (array1 == 0 && fld->writeDataFn == &defaultProtectedWriteFn
// //                               && fld->setDataFn == &defaultProtectedSetFn
// //                               && fld->flag == 0
// //                         ) {
// //                               fastPath = curObject->setDataField(fld,stack[_STK].getFloat() );
// //                         }
// //
// //                   }
// //                   if (!fastPath) {
// //                         curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
// //                   }
// //
// //             } else {
// //                   // The field is not being set on an object. Maybe it's a special accessor?
// //                   setFieldComponent(prevObject, prevField, prevFieldArray, curField, currentRegister);
// //                   prevObject = NULL;
// //             }
// //             break;
// // #else //#ifdef ELFSCRIPT_FASTPATH_FLD
// //       case OP_SAVEFIELD_UINT:
// //          if (curObject)
// //             curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
// //          else
// //          {
// //             // The field is not being set on an object. Maybe it's a special accessor?
// //             setFieldComponent(prevObject, prevField, prevFieldArray, curField, currentRegister);
// //             prevObject = NULL;
// //          }
// //          break;
// //
// //       case OP_SAVEFIELD_FLT:
// //             if (curObject) {
// //               curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
// //             } else {
// //                   // The field is not being set on an object. Maybe it's a special accessor?
// //                   setFieldComponent(prevObject, prevField, prevFieldArray, curField, currentRegister);
// //                   prevObject = NULL;
// //             }
// //             break;
// // #endif //#ifdef ELFSCRIPT_FASTPATH_FLD
//
//       // ElfScript we try to get the fieldtype!!!
//       case OP_SAVEFIELD_FASTPATH:
//
//             if (curObject) {
//                   //XXTH Fastpath:
//                   bool fastPath  = false;
//                   const AbstractClassRep::Field *fld = curObject->findField(curField);
//
//                   if (fld && (
//                         fld->type == TypeF32
//                         || fld->type == TypeS32
//                         || fld->type == TypeBool
//                         || fld->type == TypeU32
//                         || fld->type == TypeS64
//                         || fld->type == TypeU64
//                         || fld->type == TypeF64
//                         || fld->type == TypeS8
//                         || fld->type == TypeU8
//                         || fld->type == TypeS16
//                   ))
//                   {
//                         const char* array = (const char*) curFieldArray;
//                         S32 array1 = PARSE_ARRAY_INDEX(array);
//
//                         if (array1 == 0 && fld->writeDataFn == &defaultProtectedWriteFn
//                               && fld->setDataFn == &defaultProtectedSetFn
//                               && fld->flag == 0
//                         ) {
//                               if (fld->type == TypeF32 || fld->type == TypeF64)
//                                     fastPath = curObject->setDataField(fld,stack[_STK].getFloat() );
//                               else
//                                     fastPath = curObject->setDataField(fld,stack[_STK].getInt() );
//                         }
//
//                   }
//
// #ifdef ENABLE_CONSOLE_VECTOR  // TEST WHERE WHICH INFOS WE CAN GET from fld for struct fast path (EngineTypeKind, EngineStructTypeInfo)
// else if (fld && fld->type != TypeString && fld->type != TypeName){
//
//       if ( stack[_STK].type == cvVector) {
//             Con::warnf("We got a  stack[_STK].type = cvVector !!! values are: %g,%g,%g,%g ", stack[_STK].v[0], stack[_STK].v[1], stack[_STK].v[2], stack[_STK].v[3]);
//       }
//
//       // lot's of 20 which is DefineUnmappedConsoleType( TypeString, const char * ) // plain UTF-8 strings are not supported in new interop
//       ConsoleBaseType* conType = ConsoleBaseType::getType( fld->type );
//
//       if (conType) {
//             const EngineTypeInfo* typeInfo =  conType->getTypeInfo();
//
//             Con::printf("%-16s :: type %2u, %20s, %s, TypeKind: %d (struct:%d)",
//                         curField,
//                         fld->type, stack[_STK].getString()
//                         ,  conType->getTypeName()
//                         , typeInfo ? typeInfo->getTypeKind() : -1 ,  typeInfo ? typeInfo->isStruct() : -1
//             );
//       }
// }
// #endif
//
//
//                   if (!fastPath) {
//                         curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
//                   }
//
//             } else {
//                   // The field is not being set on an object. Maybe it's a special accessor?
//                   setFieldComponent(prevObject, prevField, prevFieldArray, curField, currentRegister);
//                   prevObject = NULL;
//             }
//             break;
//
//       break;
//
//       // ----------------------- ELFSCRIPT ---------------------------------
// #ifdef ELFSCRIPT_INT_HACK
//       case OP_CMPLT_UINT:
//             doIntOperation<IntegerOperation::LT>();
//             break;
//       case OP_CMPGR_UINT:
//             doIntOperation<IntegerOperation::GT>();
//             break;
//       case OP_CMPLE_UINT:
//             doIntOperation<IntegerOperation::LE>();
//             break;
//       case OP_CMPGE_UINT:
//             doIntOperation<IntegerOperation::GE>();
//             break;
//       case OP_CMPEQ_UINT:
//             doIntOperation<IntegerOperation::EQ>();
//             break;
//       case OP_CMPNE_UINT:
//             doIntOperation<IntegerOperation::NE>();
//             break;
// #endif
//       // ----------------------- ELFSCRIPT ---------------------------------
//
//
//       case OP_SAVEFIELD_STR:
//          if (curObject)
//             curObject->setDataField(curField, curFieldArray, stack[_STK].getString());
//          else
//          {
//             // The field is not being set on an object. Maybe it's a special accessor?
//             setFieldComponent(prevObject, prevField, prevFieldArray, curField, currentRegister);
//             prevObject = NULL;
//          }
//          break;
//
//       case OP_POP_STK:
//          POP_STK();
//          break;
//
//       case OP_LOADIMMED_UINT:
//          stack[_STK + 1].setInt(code[ip++]);
//          _STK++;
//          break;
//
//       case OP_LOADIMMED_FLT:
//          stack[_STK + 1].setFloat(curFloatTable[code[ip++]]);
//          _STK++;
//          break;
//
//       case OP_TAG_TO_STR:
//          code[ip - 1] = OP_LOADIMMED_STR;
//          // it's possible the string has already been converted
//          Con::errorf("Tagged string not supported in ElfScript or FIXME (%s:%d)", __FILE__, __LINE__);
//          // if (U8(curStringTable[code[ip]]) != StringTagPrefixByte)
//          // {
//          //    U32 id = GameAddTaggedString(curStringTable + code[ip]);
//          //    dSprintf(curStringTable + code[ip] + 1, 7, "%d", id);
//          //    *(curStringTable + code[ip]) = StringTagPrefixByte;
//          // }
//          TORQUE_CASE_FALLTHROUGH;
//
//       case OP_LOADIMMED_STR:
//          stack[_STK + 1].setString(curStringTable + code[ip++]);
//          _STK ++;
//          break;
//
//       case OP_DOCBLOCK_STR:
//       {
//          // If the first word of the doc is '\class' or '@class', then this
//          // is a namespace doc block, otherwise it is a function doc block.
//          const char* docblock = curStringTable + code[ip++];
//
//          const char* sansClass = dStrstr(docblock, "@class");
//          if (!sansClass)
//             sansClass = dStrstr(docblock, "\\class");
//
//          if (sansClass)
//          {
//             // Don't save the class declaration. Scan past the 'class'
//             // keyword and up to the first whitespace.
//             sansClass += 7;
//             S32 index = 0;
//             while ((*sansClass != ' ') && (*sansClass != '\n') && *sansClass && (index < (nsDocLength - 1)))
//             {
//                nsDocBlockClass[index++] = *sansClass;
//                sansClass++;
//             }
//             nsDocBlockClass[index] = '\0';
//
//             curNSDocBlock = sansClass + 1;
//          }
//          else
//             curFNDocBlock = docblock;
//       }
//
//       break;
//
//       case OP_LOADIMMED_IDENT:
//          stack[_STK + 1].setStringTableEntry(CodeToSTE(code, ip));
//          _STK++;
//          ip += 2;
//          break;
//
//       case OP_CALLFUNC:
//       {
//          // This routingId is set when we query the object as to whether
//          // it handles this method.  It is set to an enum from the table
//          // above indicating whether it handles it on a component it owns
//          // or just on the object.
//          fnName = CodeToSTE(code, ip);
//          fnNamespace = CodeToSTE(code, ip + 2);
//          U32 callType = code[ip + 4];
//
//          //if this is called from inside a function, append the ip and codeptr
//          if (!Script::gEvalState.stack.empty())
//          {
//             Script::gEvalState.getCurrentFrame().module = this;
//             Script::gEvalState.getCurrentFrame().ip = ip - 1;
//          }
//
//          ip += 5;
//          gCallStack.argvc(fnName, callArgc, &callArgv);
//
//          if (callType == FuncCallExprNode::FunctionCall)
//          {
//             // Note: This works even if the function was in a package. Reason being is when
//             // activatePackage() is called, it swaps the namespaceEntry into the global namespace
//             // (and reverts it when deactivatePackage is called). Method or Static related ones work
//             // as expected, as the namespace is resolved on the fly.
//             nsEntry = Namespace::global()->lookup(fnName);
//             if (!nsEntry)
//             {
//                Con::warnf(ConsoleLogEntry::General,
//                   "%s: Unable to find function %s",
//                   getFileLine(ip - 4), fnName);
//
//                gCallStack.popFrame();
//                stack[_STK + 1].setEmptyString();
//                _STK++;
//                break;
//             }
//          }
//          else if (callType == FuncCallExprNode::StaticCall)
//          {
//             // Try to look it up.
//             ns = Namespace::find(fnNamespace);
//             nsEntry = ns->lookup(fnName);
//             if (!nsEntry)
//             {
//                Con::warnf(ConsoleLogEntry::General,
//                   "%s: Unable to find function %s%s%s",
//                   getFileLine(ip - 4), fnNamespace ? fnNamespace : "",
//                   fnNamespace ? "::" : "", fnName);
//
//                gCallStack.popFrame();
//                stack[_STK + 1].setEmptyString();
//                _STK++;
//                break;
//             }
//          }
//          else if (callType == FuncCallExprNode::MethodCall)
//          {
//             ConsoleValue& simObjectLookupValue = callArgv[1];
//             thisObject = getThisObject(simObjectLookupValue);
//
//             if (thisObject == NULL)
//             {
//                Con::warnf(
//                   ConsoleLogEntry::General,
//                   "%s: Unable to find object: '%s' attempting to call function '%s'",
//                   getFileLine(ip - 6),
//                   simObjectLookupValue.getString(),
//                   fnName
//                );
//
//                gCallStack.popFrame();
//                stack[_STK + 1].setEmptyString();
//                _STK++;
//                break;
//             }
//
//             ns = thisObject->getNamespace();
//             if (ns)
//                nsEntry = ns->lookup(fnName);
//             else
//                nsEntry = NULL;
//          }
//          else // it's a ParentCall
//          {
//             ConsoleValue& simObjectLookupValue = callArgv[1];
//             thisObject = getThisObject(simObjectLookupValue);
//
//             if (thisObject == NULL)
//             {
//                Con::warnf(
//                   ConsoleLogEntry::General,
//                   "%s: Unable to find object: '%s' attempting to call function '%s'",
//                   getFileLine(ip - 6),
//                   simObjectLookupValue.getString(),
//                   fnName
//                );
//
//                gCallStack.popFrame();
//                stack[_STK + 1].setEmptyString();
//                _STK++;
//                break;
//             }
//
//             if (thisNamespace)
//             {
//                ns = thisNamespace->mParent;
//                if (ns)
//                   nsEntry = ns->lookup(fnName);
//                else
//                   nsEntry = NULL;
//             }
//             else
//             {
//                ns = NULL;
//                nsEntry = NULL;
//             }
//          }
//
//          if (!nsEntry || noCalls)
//          {
//             if (!noCalls)
//             {
//                Con::warnf(ConsoleLogEntry::General, "%s: Unknown command %s.", getFileLine(ip - 4), fnName);
//                if (callType == FuncCallExprNode::MethodCall)
//                {
//                   Con::warnf(ConsoleLogEntry::General, "  Object %s(%d) %s",
//                      thisObject->getName() ? thisObject->getName() : "",
//                      thisObject->getId(), Con::getNamespaceList(ns));
//                }
//             }
//             gCallStack.popFrame();
//             stack[_STK + 1].setEmptyString();
//             _STK++;
//             break;
//          }
//          if (nsEntry->mType == Namespace::Entry::ConsoleFunctionType)
//          {
//             if (nsEntry->mFunctionOffset)
//             {
//                ConsoleValue returnFromFn = nsEntry->mModule->exec(nsEntry->mFunctionOffset, fnName, nsEntry->mNamespace, callArgc, callArgv, false, nsEntry->mPackage).value;
//                stack[_STK + 1] = (returnFromFn);
//             }
//             else // no body
//                stack[_STK + 1].setEmptyString();
//             _STK++;
//
//             gCallStack.popFrame();
//          }
//          else
//          {
//             if ((nsEntry->mMinArgs && S32(callArgc) < nsEntry->mMinArgs) || (nsEntry->mMaxArgs && S32(callArgc) > nsEntry->mMaxArgs))
//             {
//                const char* nsName = ns ? ns->mName : "";
//                Con::warnf(ConsoleLogEntry::Script, "%s: %s::%s - wrong number of arguments. got %d, expected %d to %d", getFileLine(ip - 4), nsName, fnName, S32(callArgc), nsEntry->mMinArgs, nsEntry->mMaxArgs);
//                // ElfScript:
//                Con::warnf(ConsoleLogEntry::Script, "%s: usage: %s%s", getFileLine(ip - 4), nsEntry->mFunctionName,  nsEntry->getArgumentsString().c_str());
//                if (strlen(nsEntry->mUsage)>0) Con::warnf(ConsoleLogEntry::Script, "%s: docu: %s", getFileLine(ip - 4), nsEntry->mUsage);
//                gCallStack.popFrame();
//                stack[_STK + 1].setEmptyString();
//                _STK++;
//             }
//             else
//             {
//                switch (nsEntry->mType)
//                {
//                case Namespace::Entry::StringCallbackType:
//                {
//                   const char* result = nsEntry->cb.mStringCallbackFunc(thisObject, callArgc, callArgv);
//                   gCallStack.popFrame();
//                   stack[_STK + 1].setString(result);
//                   _STK++;
//                   break;
//                }
//                case Namespace::Entry::IntCallbackType:
//                {
//                   S64 result = nsEntry->cb.mIntCallbackFunc(thisObject, callArgc, callArgv);
//                   gCallStack.popFrame();
//
//                   if (code[ip] == OP_POP_STK)
//                   {
//                      ip++;
//                      break;
//                   }
//
//                   stack[_STK + 1].setInt(result);
//                   _STK++;
//                   break;
//                }
//                case Namespace::Entry::FloatCallbackType:
//                {
//                   F64 result = nsEntry->cb.mFloatCallbackFunc(thisObject, callArgc, callArgv);
//                   gCallStack.popFrame();
//
//                   if (code[ip] == OP_POP_STK)
//                   {
//                      ip++;
//                      break;
//                   }
//
//                   stack[_STK + 1].setFloat(result);
//                   _STK++;
//                   break;
//                }
//                case Namespace::Entry::VoidCallbackType:
//                {
//                   nsEntry->cb.mVoidCallbackFunc(thisObject, callArgc, callArgv);
//                   gCallStack.popFrame();
//
//                   if (code[ip] == OP_POP_STK)
//                   {
//                      ip++;
//                      break;
//                   }
//
//                   if (Con::getBoolVariable("$Con::warnVoidAssignment", true))
//                   {
//                      Con::warnf(ConsoleLogEntry::General, "%s: Call to %s in %s uses result of void function call.", getFileLine(ip - 4), fnName, functionName);
//                   }
//
//                   stack[_STK + 1].setEmptyString();
//                   _STK++;
//
//                   break;
//                }
//                case Namespace::Entry::BoolCallbackType:
//                {
//                   bool result = nsEntry->cb.mBoolCallbackFunc(thisObject, callArgc, callArgv);
//                   gCallStack.popFrame();
//
//                   if (code[ip] == OP_POP_STK)
//                   {
//                      ip++;
//                      break;
//                   }
//
//                   stack[_STK + 1].setBool(result);
//                   _STK++;
//
//                   break;
//                }
//                } // switch (nsEntry->mType)
//             }
//          }
//          break;
//       } //OP_CALLFUNC
//
//       // ===========================================================================================
// // PoD !! :D only kosmetic max 16 elements
// case OP_BUILD_VECTOR_STRING: {
//
//       // read the count
//       U32 count = code[ip++];
//
//       const U32 MAX_ELEMENTS = 16;
//       const char* stringValues[MAX_ELEMENTS];
//
//       if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;
//
// #ifdef ENABLE_CONSOLE_VECTOR //XXTH TEST
//       bool matchVectorFields = count <= CONSOLE_VALUE_VECTOR_FIELD_COUNT;
//       F64   v[CONSOLE_VALUE_VECTOR_FIELD_COUNT] = {};
// #endif
//       // get values from stack
//       for (S32 i = count - 1; i >= 0; i--) {
// #ifdef ENABLE_CONSOLE_VECTOR //XXTH TEST
//             if (matchVectorFields) v[i] = stack[_STK].getFloat();
// #endif
//
//             stringValues[i] = stack[_STK].getString();
//             _STK--;
//       }
//
//       // i have to translate it to a string again :(
//       char buffer[1024];
//       int offset = 0;
//       buffer[0] = '\0';
//
//       for (U32 i = 0; i < count; i++) {
//             // offset += dSprintf(buffer + offset
//             // , sizeof(buffer) - offset
//             // , (i == 0) ? "%s" : " %s", stringValues[i]);
//             S32 remaining = sizeof(buffer) - offset;
//             if (remaining <= 1) break;
//
//             offset += dSprintf(buffer + offset, remaining, (i == 0) ? "%s" : " %s", stringValues[i]);
//
//       }
//
//       _STK++;
//       stack[_STK].setString(buffer);
//
// //       // read the count
// //       U32 count = code[ip++];
// //
// //       const U32 MAX_ELEMENTS = 16;
// //       const char* stringValues[MAX_ELEMENTS];
// //
// //       if (count > MAX_ELEMENTS) count = MAX_ELEMENTS;
// //
// // #ifdef ENABLE_CONSOLE_VECTOR //XXTH TEST
// //       bool matchVectorFields = count <= CONSOLE_VALUE_VECTOR_FIELD_COUNT;
// //       F64   v[CONSOLE_VALUE_VECTOR_FIELD_COUNT] = {};
// // #endif
// //       // get values from stack
// //       for (S32 i = count - 1; i >= 0; i--) {
// // #ifdef ENABLE_CONSOLE_VECTOR //XXTH TEST
// //             if (matchVectorFields) v[i] = stack[_STK].getFloat();
// // #endif
// //
// //             stringValues[i] = stack[_STK].getString();
// //             _STK--;
// //       }
// //
// //       // i have to translate it to a string again :(
// //       char buffer[256];
// //       int offset = 0;
// //       buffer[0] = '\0';
// //
// //       for (U32 i = 0; i < count; i++) {
// //             offset += dSprintf(buffer + offset
// //             , sizeof(buffer) - offset
// //             , (i == 0) ? "%s" : " %s", stringValues[i]);
// //       }
// //
// //       _STK++;
// //       stack[_STK].setString(buffer);
//
// #ifdef ENABLE_CONSOLE_VECTOR //XXTH TEST
//       // after setString!!
//       if (matchVectorFields) {
//             // Con::warnf("stack %d to cvVector (%s)", _STK, buffer);
//             // this break:
//             // static void thunk( S32 argc, ConsoleValue *argv, FunctionType fn, const _EngineFunctionDefaultArguments< void(ArgTs...) >& defaultArgs)
//             // {
//             //       Helper::dispatchHelper(argc, argv, fn, defaultArgs, SeqType());
//             // }
//             // not sure why because i return the string which is filled above
//             // but i only added a small part where  type is used so why knows .....
//
//
//             stack[_STK].type = cvVector;
//             // copy all to 0.f old values
//             for( S32 i = 0; i < CONSOLE_VALUE_VECTOR_FIELD_COUNT; i++ ) {
//                    stack[_STK].v[i] = v[i];
//             }
//       }
// #endif
//
//
//       break;
// }
//
//       // ===========================================================================================
//       case OP_ADVANCE_STR_APPENDCHAR:
//       {
//          char buff[2];
//          buff[0] = (char)code[ip++];
//          buff[1] = '\0';
//
//          S32 len;
//          const char* concat = tsconcat(stack[_STK].getString(), buff, len);
//
//          stack[_STK].setStringRef(concat, len);
//          break;
//       }
//
//       case OP_REWIND_STR:
//          TORQUE_CASE_FALLTHROUGH;
//       case OP_TERMINATE_REWIND_STR:
//       {
//          S32 len;
//          const char* concat = tsconcat(stack[_STK - 1].getString(), stack[_STK].getString(), len);
//
//          stack[_STK - 1].setStringRef(concat, len);
//          POP_STK();
//          break;
//       }
//
//       case OP_COMPARE_STR:
//          stack[_STK - 1].setBool(!dStricmp(stack[_STK].getString(), stack[_STK - 1].getString()));
//          POP_STK();
//          break;
//
//       case OP_PUSH:
//          gCallStack.push((stack[_STK--]));
//          break;
//
//       case OP_PUSH_FRAME:
//          gCallStack.pushFrame(code[ip++]);
//          break;
//
//       case OP_ASSERT:
//       {
//          if (!stack[_STK--].getBool())
//          {
//             const char* message = curStringTable + code[ip];
//
//             U32 breakLine, inst;
//             findBreakLine(ip - 1, breakLine, inst);
//
//             if (PlatformAssert::processAssert(PlatformAssert::Fatal,
//                name ? name : "eval",
//                breakLine,
//                message))
//             {
//                // if (TelDebugger && TelDebugger->isConnected() && breakLine > 0)
//                // {
//                //    TelDebugger->breakProcess();
//                // }
//                // else
//                   Platform::debugBreak();
//             }
//          }
//
//          ip++;
//          break;
//       }
//
//       case OP_BREAK:
//       {
//          //append the ip and codeptr before managing the breakpoint!
//          AssertFatal(!Script::gEvalState.stack.empty(), "Empty eval stack on break!");
//          Script::gEvalState.getCurrentFrame().module = this;
//          Script::gEvalState.getCurrentFrame().ip = ip - 1;
//
//          U32 breakLine;
//          findBreakLine(ip - 1, breakLine, instruction);
//          if (!breakLine)
//             goto breakContinue;
//          // TelDebugger->executionStopped(this, breakLine);
//
//          goto breakContinue;
//       }
//
//       case OP_ITER_BEGIN_STR:
//       {
//          iterStack[_ITER].mIsStringIter = true;
//          TORQUE_CASE_FALLTHROUGH;
//       }
//
//       case OP_ITER_BEGIN:
//       {
//          bool isGlobal = code[ip];
//
//          U32 failIp = code[ip + (isGlobal ? 3 : 2)];
//
//          IterStackRecord& iter = iterStack[_ITER];
//          iter.mIsGlobalVariable = isGlobal;
//
//          if (isGlobal)
//          {
//             StringTableEntry varName = CodeToSTE(code, ip + 1);
//             iter.mVar.mVariable = Con::gGlobalVars.add(varName);
//          }
//          else
//          {
//             iter.mVar.mRegister = code[ip + 1];
//          }
//
//          if (iter.mIsStringIter)
//          {
//             iter.mData.mStr.mString = stack[_STK].getString();
//             iter.mData.mStr.mIndex = 0;
//          }
//          else
//          {
//             // Look up the object.
//
//             SimSet* set;
//             if (!Sim::findObject(stack[_STK].getString(), set))
//             {
//                Con::errorf(ConsoleLogEntry::General, "No SimSet object '%s'", stack[_STK].getString());
//                Con::errorf(ConsoleLogEntry::General, "Did you mean to use 'foreach$' instead of 'foreach'?");
//                ip = failIp;
//                // Pop the iterated value
//                POP_STK();
//                //  XXTH continue;
//                DISPATCH();
//             }
//
//             // Set up.
//
//             iter.mData.mObj.mSet = set;
//             iter.mData.mObj.mIndex = 0;
//          }
//
//          _ITER++;
//          iterDepth++;
//
//          ip += isGlobal ? 4 : 3;
//          break;
//       }
//
//       case OP_ITER:
//       {
//          U32 breakIp = code[ip];
//          IterStackRecord& iter = iterStack[_ITER - 1];
//
//          if (iter.mIsStringIter)
//          {
//             const char* str = iter.mData.mStr.mString;
//
//             U32 startIndex = iter.mData.mStr.mIndex;
//             U32 endIndex = startIndex;
//
//             // Break if at end.
//
//             if (!str[startIndex])
//             {
//                ip = breakIp;
//                //  XXTH continue;
//                DISPATCH();
//             }
//
//             // Find right end of current component.
//
//             if (!dIsspace(str[endIndex]))
//                do ++endIndex;
//             while (str[endIndex] && !dIsspace(str[endIndex]));
//
//             // Extract component.
//
//             if (endIndex != startIndex)
//             {
//                char savedChar = str[endIndex];
//                const_cast<char*>(str)[endIndex] = '\0'; // We are on the string stack so this is okay.
//
//                if (iter.mIsGlobalVariable)
//                   iter.mVar.mVariable->setStringValue(&str[startIndex]);
//                else
//                   Script::gEvalState.setLocalStringVariable(iter.mVar.mRegister, &str[startIndex], endIndex - startIndex);
//
//                const_cast<char*>(str)[endIndex] = savedChar;
//             }
//             else
//             {
//                if (iter.mIsGlobalVariable)
//                   iter.mVar.mVariable->setStringValue("");
//                else
//                   Script::gEvalState.setLocalStringVariable(iter.mVar.mRegister, "", 0);
//             }
//
//             // Skip separator.
//             if (str[endIndex] != '\0')
//                ++endIndex;
//
//             iter.mData.mStr.mIndex = endIndex;
//          }
//          else
//          {
//             U32 index = iter.mData.mObj.mIndex;
//             SimSet* set = iter.mData.mObj.mSet;
//
//             if (index >= set->size())
//             {
//                ip = breakIp;
//                //XXTH continue;
//                DISPATCH();
//             }
//
//             SimObjectId id = set->at(index)->getId();
//
//             if (iter.mIsGlobalVariable)
//                iter.mVar.mVariable->setIntValue(id);
//             else
//                Script::gEvalState.setLocalIntVariable(iter.mVar.mRegister, id);
//
//             iter.mData.mObj.mIndex = index + 1;
//          }
//
//          ++ip;
//          break;
//       }
//
//       case OP_ITER_END:
//       {
//          --_ITER;
//          --iterDepth;
//
//          POP_STK();
//
//          iterStack[_ITER].mIsStringIter = false;
//          break;
//       }
//
//       case OP_INVALID:
//          TORQUE_CASE_FALLTHROUGH;
//       default:
//          // error!
//          AssertISV(false, "Invalid OPCode Processed!");
//          goto execFinished;
//       } // ~~~~~~~~~~~~~~~~~~ END OF THE SWITCH ~~~~~~~~~~~~~~~~~~
//
//       DISPATCH();
//
//    // } //welcome back for loop
// } //  handle_FALLBACK_SWITCH:
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // !!!!!!!!!!!!!! THE MONSTER LOOP ENDS HERE !!!!!!!!!!!!!!
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================
   // ==========================================================================



execFinished:

   // if (telDebuggerOn && setFrame < 0)
   //    TelDebugger->popStackFrame();

   if (popFrame)
   {
      Script::gEvalState.popFrame();
   }

   if (argv)
   {
      if (Con::gTraceOn)
      {
         traceBuffer[0] = 0;
         dStrcat(traceBuffer, "Leaving ", TRACE_BUFFER_SIZE);

         if (packageName)
         {
            dStrcat(traceBuffer, "[", TRACE_BUFFER_SIZE);
            dStrcat(traceBuffer, packageName, TRACE_BUFFER_SIZE);
            dStrcat(traceBuffer, "]", TRACE_BUFFER_SIZE);
         }
         if (thisNamespace && thisNamespace->mName)
         {
            dSprintf(traceBuffer + (U32)dStrlen(traceBuffer), sizeof(traceBuffer) - (U32)dStrlen(traceBuffer),
               "%s::%s() - return %s", thisNamespace->mName, thisFunctionName, returnValue.getString());
         }
         else
         {
            dSprintf(traceBuffer + (U32)dStrlen(traceBuffer), sizeof(traceBuffer) - (U32)dStrlen(traceBuffer),
               "%s() - return %s", thisFunctionName, returnValue.getString());
         }
         Con::printf("%s", traceBuffer);
      }
   }
   else
   {
      if (!isCodelet)
      {
         delete[] const_cast<char*>(globalStrings);
         delete[] globalFloats;
         globalStrings = NULL;
         globalFloats = NULL;
      }
   }

   if (Con::getCurrentScriptModuleName())
   {
      Con::gCurrentFile = Con::getCurrentScriptModuleName();
      Con::gCurrentRoot = Con::getModNameFromPath(Con::getCurrentScriptModulePath());
   }

   decRefCount();

#ifdef TORQUE_DEBUG
   AssertFatal(!(_STK > stackStart), "String stack not popped enough in script exec");
   AssertFatal(!(_STK < stackStart), "String stack popped too much in script exec");
#endif

   //XXTH HARDCORE CLEANUP! FIXME try to find out MaxStackDepth could be
   // the macro does it job and did reduce the mem / sec from ~5MB to 1.5MB
   // but this does nothing
   // for (U32 i = _STK + 1; i < MaxStackSize; i++)
   // {
   //       stack[i].cleanupData();
   // }

   // XXTH maybe this: NOTE this must be done in MainLoop
   //
   // ConsoleValue::resetConversionBuffer();
   //<<<<<<<<< XXTH

   return Con::EvalResult((returnValue));
}

//------------------------------------------------------------
