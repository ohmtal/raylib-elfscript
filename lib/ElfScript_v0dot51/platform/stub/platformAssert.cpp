//XXTH FIXME STUB!
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

#include <stdarg.h>

#include "platform/platformAssert.h"


//-------------------------------------- STATIC Declaration
PlatformAssert *PlatformAssert::platformAssert = NULL;

//--------------------------------------
PlatformAssert::PlatformAssert()
{
   processing = false;
   ignoreAll = false;
}

//--------------------------------------
PlatformAssert::~PlatformAssert()
{
}

//--------------------------------------
void PlatformAssert::create( PlatformAssert* newAssertClass )
{
   if (!platformAssert)
      platformAssert = newAssertClass ? newAssertClass : new PlatformAssert;
}


//--------------------------------------
void PlatformAssert::destroy()
{
   if (platformAssert)
      delete platformAssert;
   platformAssert = NULL;
}


//--------------------------------------
bool PlatformAssert::displayMessageBox(const char *title, const char *message, bool retry)
{
   return false; //NOTE STUB
}

static const char *typeName[] = { "Unknown", "Fatal-ISV", "Fatal", "Warning" };

//--------------------------------------

bool PlatformAssert::process(Type         assertType,
                             const char  *filename,
                             U32          lineNumber,
                             const char  *message)
{
    return false; //NOTE STUB
}

bool PlatformAssert::processingAssert()
{
   return platformAssert ? platformAssert->processing : false;
}

//--------------------------------------
bool PlatformAssert::processAssert(Type        assertType,
                                   const char  *filename,
                                   U32         lineNumber,
                                   const char  *message)
{
   return true;  //NOTE STUB
}

//--------------------------------------
