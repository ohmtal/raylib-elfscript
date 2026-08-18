
# core/strings

The String Class is very nice and i like it more than std::string. So i think about separating it.
Includes outside strings:

- #include "core/util/tVector.h"
    - #include "console/engineTypes.h"
    - #include "console/engineTypeInfo.h"
    - #include "platform/platform.h"
- #include "platform/platform.h"
- #include "platform/types.h"
- #include "platform/platformAssert.h"
    - ...
- #include "console/console.h"
    - MANY
- #include "core/frameAllocator.h"
    -  #include "platform/platform.h"
- #include "core/util/tDictionary.h"
    - #include "core/util/str.h"
    - #include "core/util/hashFunction.h"
    - #include "core/dataChunker.h"
- #include "core/util/hashFunction.h"
    - #include "platform/platform.h"
    - #include "platform/types.h"

**!!!! core/util/str.cpp !!!! << String::compare and all the other utils**
