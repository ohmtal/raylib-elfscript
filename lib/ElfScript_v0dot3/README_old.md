# ElfScript

![ElfScript Logo](./res/logo256.png)

Cutdown TorqueScript to minimum attempt.

**Current Goals**: Get StringTable and StringFunction working 

**Final Goal:** DefineEngineFunction and DefineEngineMethod (console/engineAPI.h)
Commands like exec (file) or mSin (math) should be optional and added as 
"plugin".

## NOTE: this are the new includes for copy/paste

str.h becomes:

    #include "core/strings/String.h"
    #include "core/strings/stringTable.h"

## NOTE: some fake/stub/wrapper definitions in platfrom/platform.h!

Finally:

    - [ ] types.[COMPILER].h really needed ? 
    - [ ] Add the NameSpace **elf** when running. 
    - [ ] think about the directories core/string (stringtable/str) core/util ..
    - [ ] update MIT Headers with SPX version 

## Step by Step

1.) Platform **DONE** 

    platform/types.h 
    platfrom/platformMemory.h /cpp
    plattform/platform.h and stub
    platform/platformAssert.h stub

2.) Core start **DONE**

    frameAllocator
    datachunker
    
3.) String, StringFunctions and StringTable  **DONE**

    stringtable
    stringfunctions

4.) Vector **DONE** 

    core/util
    tVector.cpp
    tVector.h
    tVectorSpecializations.h 
   
5.) core/string part II

    core/util/hashFunction.*
    core/string/findMatch.*
    core/strings/stringUnit.*
    core/strings/unicode.h.*
   
6.) str.h /  core/util/tDictionary.*

    core/elfWrapper ***** replace engineAPI inlude in str.cpp *******
    core/util/autoPtr.h
    core/util/tDictionary.*
    core/util/str.* **** renamed to core/strings/String.* ******
    core/stringTable => core/strings/stringTable.h
   
7.) insert torqueScript and see what happen ...
    
    Now it's getting tricky ... 
    
    I guess i have to put in the complete console folder and
    then start removing instead of tring to insert only things 
    i verified. 
    
    console/consoleInternal.h
        - Dictionary
        - ConsoleValueFrame
        - ConsoleValue
        - Namespace
        - ConsoleValueFrame* currentRegisterArray;
          
    console/module.h:
        - Con::Module
        
    console/runtime.h
        - Con::EvalResult
        
    consoleInternal.h uses SimObject:
        - SimObject ConsoleValue execute(S32 argc, ConsoleValue* argv, SimObject* thisObj);

---

    
## console/torquescript missing includes:


```
astAlloc.cpp:#include "console/console.h"
astAlloc.cpp:#include "compiler.h"
astAlloc.cpp:#include "console/consoleInternal.h"

astNodes.cpp:#include "console/console.h"
astNodes.cpp:#include "console/simBase.h"

cmdgram.cpp:#include "console/console.h"
cmdgram.cpp:#include "console/consoleInternal.h"

CMDgram.y:#include "console/console.h"
CMDgram.y:#include "console/consoleInternal.h"

CMDscan.cpp:#include "console/console.h"
CMDscan.cpp:#include "console/dynamicTypes.h"

CMDscan.l:#include "console/console.h"
CMDscan.l:#include "console/dynamicTypes.h"

codeBlock.cpp:#include "console/console.h"
codeBlock.cpp:#include "core/stream/fileStream.h"

codeBlock.h:#include "console/runtime.h"

compiledEval.cpp:#include "console/consoleInternal.h"
compiledEval.cpp:#include "console/simBase.h"
compiledEval.cpp:#include "console/stringStack.h"
compiledEval.cpp:#include "util/messaging/message.h"
compiledEval.cpp:#include "console/returnBuffer.h"
compiledEval.cpp:#include "console/consoleValueStack.h"

compiler.cpp:#include "console/console.h"
compiler.cpp:#include "console/simBase.h"
evalState.h:#include "console/consoleInternal.h"

runtime.cpp:#include "console/script.h"
runtime.cpp:#include "console/runtime.h"
runtime.cpp:#include "core/volume.h"
runtime.cpp:#include "core/stream/fileStream.h"
runtime.cpp:#include "core/util/timeClass.h"

runtime.h:#include "console/runtime.h"
```
