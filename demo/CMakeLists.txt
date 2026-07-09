cmake_minimum_required(VERSION 3.24)
# -----------------------------------------------------------------------------
# Project settings:
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# -----------------------------------------------------------------------------

project(raylib-elfscript)
set(PROJECT_SRC
    src/main.cpp
    src/ConsoleGuiObject.cpp
)

set (ASSET_PATH ${CMAKE_CURRENT_LIST_DIR}/assets@assets)
# -----------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# -----------------------------------------------------------------------------
# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")


    add_link_options(
        # "-sOFFSCREEN_FRAMEBUFFER=1"
        "-sUSE_WEBGL2=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sSTACK_SIZE=524288"
        # for virtual filesystem
        # "-sFORCE_FILESYSTEM=1"
        # "-sEXPORTED_RUNTIME_METHODS=['FS', 'ccall']"
        # "-sEXIT_RUNTIME=1"
    )
endif()
# -----------------------------------------------------------------------------

# include(FetchContent)

# ------------- RayLib
# set(PLATFORM "SDL" CACHE STRING "raylib platform" FORCE)
set(RAYLIB_DIR "${CMAKE_CURRENT_LIST_DIR}/../lib/raylib" CACHE PATH "Path to RayLib 6.0")
message( STATUS "\n Set Raylib to: " ${RAYLIB_DIR} )

if(NOT EXISTS "${RAYLIB_DIR}/CMakeLists.txt")
  message(FATAL_ERROR
    "\n" ${RAYLIB_DIR}
    "\n ********** RayLib not found! *************"
  )
else()
  add_subdirectory("${RAYLIB_DIR}" "${CMAKE_BINARY_DIR}/raylib_build")
endif()

# ----------- Elf/TorqueScript
# first try to get the current source
set(ELFSCRIPT_PATH "/opt/ElfScript" CACHE PATH "Path to ElfScript")
set(ELF_MODULE ${ELFSCRIPT_PATH}/ElfScript)
set(ELF_CMAKE ${ELF_MODULE}/ElfScript.cmake)

# fallback to Version 0.1 if not found/configured
if(NOT EXISTS ${ELF_CMAKE})
  set(ELF_MODULE "${CMAKE_CURRENT_LIST_DIR}/../lib/ElfScript_v0dot1")
  set(ELF_CMAKE ${ELF_MODULE}/ElfScript.cmake)
endif()

# this should not happen ....
if(NOT EXISTS ${ELF_CMAKE})
    message(FATAL_ERROR
        "\n ElfScript path is not set! "
        "\n Please provide the path using: "
        "\n cmake -B build -DELFSCRIPT_PATH=/path/to/ElfScript"
    )
else()

  message( STATUS "\n Using ElfScript: " ${ELF_CMAKE} )
  include(${ELF_CMAKE})

  set (ELFSCRIPT_INCLUDES
   ${ELF_MODULE}
  )

  list(APPEND ELFSCRIPT_SRC ${ELF_MODULE}/addons/console/consoleDocExporter.cpp)

endif()

# ------------- rayLib-elfScript
set(RAYELF_DIR "${CMAKE_CURRENT_LIST_DIR}/../src" CACHE PATH "Path to RayLib-ElfScript")
message( STATUS "\n Ray-ElfScript directory is: " ${RAYELF_DIR} )
set(RAYELF_CMAKE "${RAYELF_DIR}/raylib-elfscript.cmake")
if(NOT EXISTS ${RAYELF_CMAKE})
  message(FATAL_ERROR
    "\n" ${RAYELF_DIR}
    "\n ********** RayLib-ElfScript not found! *************"
  )
else()
  message( STATUS "\n Include: " ${RAYELF_CMAKE} )
  include(${RAYELF_CMAKE})
endif()


# ------------- Main
add_executable(${PROJECT_NAME}
    ${PROJECT_SRC}
    ${ELFSCRIPT_SRC}
    ${RAYLIB_ELFSCRIPT_SRC}
    ${RAYELF_DIR}/defaultMain.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/
    ${ELFSCRIPT_INCLUDES}
    ${RAYELF_DIR}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)

# Web Configurations
if ("${PLATFORM}" STREQUAL "Web")


    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
    target_link_options(${PROJECT_NAME} PUBLIC -sUSE_GLFW=3 PUBLIC --preload-file ${ASSET_PATH} PRIVATE "-lidbfs.js")


    # ---- Add minshell
    set(TARGET_NAME ${PROJECT_NAME})
    set(CUSTOM_SHELL_FILE "${RAYLIB_DIR}/src/minshell.html")
    if(EXISTS "${CUSTOM_SHELL_FILE}")
        target_link_options(${TARGET_NAME} PRIVATE "--shell-file" "${CUSTOM_SHELL_FILE}")
        set_target_properties(${TARGET_NAME} PROPERTIES LINK_DEPENDS "${CUSTOM_SHELL_FILE}")
    endif()

endif()
