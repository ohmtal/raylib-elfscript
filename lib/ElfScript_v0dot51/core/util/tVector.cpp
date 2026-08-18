//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
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
#include "core/util/tVector.h"

// #include "platform/profiler.h"


#ifdef TORQUE_DEBUG_GUARD

bool VectorResize(U32 *aSize, U32 *aCount, void **arrayPtr, U32 newCount, U32 elemSize,
                  const char* fileName,
                  const U32   lineNum)
{
   PROFILE_SCOPE( VectorResize );

   if (newCount > 0) 
   {
      U32 blocks = newCount / VectorBlockSize;
      if (newCount % VectorBlockSize)
         blocks++;
      S32 mem_size = blocks * VectorBlockSize * elemSize;

      const char* pUseFileName = fileName != NULL ? fileName : __FILE__;
      U32 useLineNum           = fileName != NULL ? lineNum  : __LINE__;

      if (*arrayPtr != NULL)
         *arrayPtr = dRealloc_r(*arrayPtr, mem_size, pUseFileName, useLineNum);
      else
         *arrayPtr = dMalloc_r(mem_size, pUseFileName, useLineNum);

      AssertFatal( *arrayPtr, "VectorResize - Allocation failed." );

      *aCount = newCount;
      *aSize = blocks * VectorBlockSize;
      return true;
   }

   if (*arrayPtr) 
   {
      dFree(*arrayPtr);
      *arrayPtr = 0;
   }

   *aSize  = 0;
   *aCount = 0;
   return true;
}

#else

//XXTH TEST: memleak hunting new Version checking newCount :
// ----- FIXME still leaking
// Direct leak of 256 byte(s) in 4 object(s) allocated from:
// #0 0x7f7665b2c161 in malloc (/usr/lib/libasan.so.8+0x12c161) (BuildId: ee5fbab73143ab257a66a33afe0f038a4af7a74e)
// #1 0x558c4087e925 in dMalloc_r(unsigned long, char const*, unsigned long) /opt/TorqueScript/TorqueScript/platform/platformMemory.cpp:69
// #2 0x558c4082fbc0 in VectorResize(unsigned int*, unsigned int*, void**, unsigned int, unsigned int) /opt/TorqueScript/TorqueScript/core/util/tVector.cpp:94
// #3 0x558c40659458 in Vector<unsigned int>::resize(unsigned int) /opt/TorqueScript/TorqueScript/core/util/tVector.h:757
// #4 0x558c407ae705 in Vector<unsigned int>::setSize(unsigned int) /opt/TorqueScript/TorqueScript/core/util/tVector.h:340
// #5 0x558c407df0de in CodeBlock::exec(unsigned int, char const*, Namespace*, unsigned int, ConsoleValue*, bool, char const*, int) /opt/TorqueScript/TorqueScript/console/torquescript/compiledEval.cpp:840
// ------
bool VectorResize(U32 *aSize, U32 *aCount, void **arrayPtr, U32 newCount, U32 elemSize)
{
   if (newCount > 0)
   {
      U32 blocks = newCount / VectorBlockSize;
      if (newCount % VectorBlockSize)
         blocks++;
      S32 mem_size = blocks * VectorBlockSize * elemSize;


      if (*arrayPtr)
      {
         void *temp = dRealloc(*arrayPtr, mem_size);
         if (!temp)
         {
            return false;
         }
         *arrayPtr = temp;
      }
      else
      {
         *arrayPtr = dMalloc(mem_size);
         if (!*arrayPtr)
         {
            return false;
         }
      }

      *aCount = newCount;
      *aSize = blocks * VectorBlockSize;
      return true;
   }

   if (*arrayPtr)
   {
      dFree(*arrayPtr);
      *arrayPtr = NULL;
   }

   *aSize = 0;
   *aCount = 0;
   return true;
}

// bool VectorResize(U32 *aSize, U32 *aCount, void **arrayPtr, U32 newCount, U32 elemSize)
// {
//    // PROFILE_SCOPE( VectorResize );
//
//    if (newCount > 0)
//    {
//       U32 blocks = newCount / VectorBlockSize;
//       if (newCount % VectorBlockSize)
//          blocks++;
//       S32 mem_size = blocks * VectorBlockSize * elemSize;
//       *arrayPtr = *arrayPtr ? dRealloc(*arrayPtr,mem_size) :
//          dMalloc(mem_size); //<< XXTH memleak
//
//       *aCount = newCount;
//       *aSize = blocks * VectorBlockSize;
//       return true;
//    }
//
//    if (*arrayPtr)
//    {
//       dFree(*arrayPtr);
//       *arrayPtr = 0;
//    }
//
//    *aSize = 0;
//    *aCount = 0;
//    return true;
// }

#endif
