# ElfScript Source Files definition

set(CONSOLE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/console/arrayObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/arrayObject.h
    ${CMAKE_CURRENT_LIST_DIR}/console/console.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleDoc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleDoc.h
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleFunctions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleFunctions.h
    ${CMAKE_CURRENT_LIST_DIR}/console/console.h
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleInternal.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleInternal.h
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleObject.h
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleParser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleParser.h
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleTypes.h
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleValueStack.h
    ${CMAKE_CURRENT_LIST_DIR}/console/dynamicTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/dynamicTypes.h
    ${CMAKE_CURRENT_LIST_DIR}/console/engineAPI.h
    ${CMAKE_CURRENT_LIST_DIR}/console/engineDoc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/engineExports.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/engineExports.h
    ${CMAKE_CURRENT_LIST_DIR}/console/engineFunctions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/engineFunctions.h
    ${CMAKE_CURRENT_LIST_DIR}/console/engineObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/engineObject.h
    ${CMAKE_CURRENT_LIST_DIR}/console/enginePrimitives.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/enginePrimitives.h
    ${CMAKE_CURRENT_LIST_DIR}/console/engineStructs.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/engineStructs.h
    ${CMAKE_CURRENT_LIST_DIR}/console/engineTypeInfo.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/engineTypeInfo.h
    ${CMAKE_CURRENT_LIST_DIR}/console/engineTypes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/engineTypes.h
    # ${CMAKE_CURRENT_LIST_DIR}/console/fileSystemFunctions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/fixedTuple.h
    ${CMAKE_CURRENT_LIST_DIR}/console/ICallMethod.h
    ${CMAKE_CURRENT_LIST_DIR}/console/module.h
    ${CMAKE_CURRENT_LIST_DIR}/console/propertyParsing.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/propertyParsing.h
    ${CMAKE_CURRENT_LIST_DIR}/console/returnBuffer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/returnBuffer.h
    ${CMAKE_CURRENT_LIST_DIR}/console/runtimeClassRep.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/runtimeClassRep.h
    ${CMAKE_CURRENT_LIST_DIR}/console/runtime.h
    ${CMAKE_CURRENT_LIST_DIR}/console/scriptFilename.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/scriptFilename.h
    ${CMAKE_CURRENT_LIST_DIR}/console/script.h
    ${CMAKE_CURRENT_LIST_DIR}/console/scriptObjects.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/scriptObjects.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simBase.h
    ${CMAKE_CURRENT_LIST_DIR}/console/sim.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/console/simDatablock.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/console/simDatablock.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simDictionary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simDictionary.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simEvents.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simEvents.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simFieldDictionary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simFieldDictionary.h
    ${CMAKE_CURRENT_LIST_DIR}/console/sim.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simManager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simObject.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simObjectList.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simObjectList.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simObjectRef.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simPersistID.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simPersistID.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simPersistSet.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simPersistSet.h
    ${CMAKE_CURRENT_LIST_DIR}/console/simSerialize.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simSet.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/simSet.h
    ${CMAKE_CURRENT_LIST_DIR}/console/stringStack.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/stringStack.h
    ${CMAKE_CURRENT_LIST_DIR}/console/typeValidators.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/typeValidators.h
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/astAlloc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/ast.h
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/astNodes.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/bison.simple
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/cmdgram.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/CMDgram.h
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/CMDgram.y
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/CMDscan.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/CMDscan.l
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/codeBlock.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/codeBlock.h
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/compiledEval.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/compiler.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/compiler.h
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/evalState.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/evalState.h
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/optimizer.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/parser.h
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/runtime.cpp
    ${CMAKE_CURRENT_LIST_DIR}/console/torquescript/runtime.h

    # XXTH my extras ...
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleExtras.h
    ${CMAKE_CURRENT_LIST_DIR}/console/consoleExtras.cpp

    # this is rock and roll!!
    ${CMAKE_CURRENT_LIST_DIR}/console/scriptPreprocessor.h
    ${CMAKE_CURRENT_LIST_DIR}/console/scriptPreprocessor.cpp
)

set(CORE_SRC
    ${CMAKE_CURRENT_LIST_DIR}/core/crc.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/bitVector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/iTickable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/virtualMountSystem.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/str.h
    ${CMAKE_CURRENT_LIST_DIR}/core/util/str.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/byteBuffer.cpp


    ${CMAKE_CURRENT_LIST_DIR}/core/util/hashFunction.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/tVector.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/tSignal.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/tDictionary.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/md5.cpp

    ${CMAKE_CURRENT_LIST_DIR}/core/util/refBase.cpp

    ${CMAKE_CURRENT_LIST_DIR}/core/frameAllocator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/timeClass.cpp

    ${CMAKE_CURRENT_LIST_DIR}/core/util/journal/journal.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/journal/process.cpp

    ${CMAKE_CURRENT_LIST_DIR}/core/util/path.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/util/uuid.cpp

    ${CMAKE_CURRENT_LIST_DIR}/core/idGenerator.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/volume.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/fileObject.cpp

    ${CMAKE_CURRENT_LIST_DIR}/core/stringTable.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/stringTable.h

    ${CMAKE_CURRENT_LIST_DIR}/core/stream/stream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/stream/fileStream.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/stream/streamObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/stream/fileStreamObject.cpp

    ${CMAKE_CURRENT_LIST_DIR}/core/strings/findMatch.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/findMatch.h
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringFunctions.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringFunctions.h
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringUnit.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/stringUnit.h
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/unicode.cpp
    ${CMAKE_CURRENT_LIST_DIR}/core/strings/unicode.h

    ${CMAKE_CURRENT_LIST_DIR}/core/util/messaging/message.cpp
)


set(PLATFORM_SRC
    ${CMAKE_CURRENT_LIST_DIR}/platform/platformFileIO.cpp
    ${CMAKE_CURRENT_LIST_DIR}/platform/platformAssert.cpp
    ${CMAKE_CURRENT_LIST_DIR}/platform/platformMemory.cpp
    ${CMAKE_CURRENT_LIST_DIR}/platform/platformVolume.cpp

)

set(POSIX_SRC
   ${CMAKE_CURRENT_LIST_DIR}/platform/posix/posixVolume.cpp

)
set(WIN_SRC
   ${CMAKE_CURRENT_LIST_DIR}/platform/win/winVolume.cpp
)


set(MATH_SRC
   ${CMAKE_CURRENT_LIST_DIR}/math/mConsoleFunctions.cpp
)


if(WIN32)
    list(APPEND PLATFORM_SRC ${WIN_SRC})
elseif(UNIX)
    list(APPEND PLATFORM_SRC ${POSIX_SRC})
endif()

set(ELFSCRIPT_SRC
    ${CMAKE_CURRENT_LIST_DIR}/main/engineGlue.cpp
    ${CONSOLE_SRC}
    ${CORE_SRC}
    ${PLATFORM_SRC}
    ${MATH_SRC}
)

