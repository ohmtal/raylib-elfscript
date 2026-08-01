# ElfScript ripped down TorqueScript
# NOTE: for using String and Vector only:

set(elf_platform
    ${CMAKE_CURRENT_LIST_DIR}/platform/platform.h
    ${CMAKE_CURRENT_LIST_DIR}/platform/platformMemory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/platform/platformMemory.h
    ${CMAKE_CURRENT_LIST_DIR}/platform/types.h
    # FIXME ${CMAKE_CURRENT_LIST_DIR}/platform/platformAssert.cpp
    ${CMAKE_CURRENT_LIST_DIR}/platform/stub/platformAssert.cpp
    ${CMAKE_CURRENT_LIST_DIR}/platform/platformAssert.h
    ${CMAKE_CURRENT_LIST_DIR}/platform/typetraits.h
)
set(elf_core
    ${CMAKE_CURRENT_LIST_DIR}/core/dataChunker.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/dataChunker.h
    ${CMAKE_CURRENT_LIST_DIR}/core/frameAllocator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/frameAllocator.h
    # ----- string table
    # was /core/stringTable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringTable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringTable.h
    # ----- strings
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringFunctions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringFunctions.h

    # ----- Vector
    ${CMAKE_CURRENT_LIST_DIR}/core/util/tVector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/tVector.h
    ${CMAKE_CURRENT_LIST_DIR}/core/util/tVectorSpecializations.h

    # --- more utils for unicode
    ${CMAKE_CURRENT_LIST_DIR}/core/util/tDictionary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/tDictionary.h
    ${CMAKE_CURRENT_LIST_DIR}/core/util/hashFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/hashFunction.h

    # core/strings part II
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/findMatch.h
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/findMatch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringUnit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringUnit.h
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/unicode.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/unicode.h

    # str / unicode fix
    ${CMAKE_CURRENT_LIST_DIR}/core/elfWrapper.h
    ${CMAKE_CURRENT_LIST_DIR}/core/elfWrapper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/autoPtr.h
    # was util/str.h ...
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/String.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/String.h

)


set(ELFSCRIPT_SRC
    ${elf_platform}
    ${elf_core}
)
