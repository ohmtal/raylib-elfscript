cmake_minimum_required(VERSION 3.24)
# -----------------------------------------------------------------------------
# Project settings:
# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# -----------------------------------------------------------------------------

project(raylib-elfscript)
set(PROJECT_SRC
    src/main.cpp
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
        "-sUSE_WEBGL2=1"
        "-sALLOW_MEMORY_GROWTH=1"
        "-sSTACK_SIZE=524288"
        "-sASYNCIFY"
        "-sASYNCIFY_STACK_SIZE=65536"
    )
endif()
# -----------------------------------------------------------------------------

include(FetchContent)

# ----------- Elf/TorqueScript
set(ELFSCRIPT_PATH "/opt/ElfScript" CACHE PATH "Path to ElfScript")
set(ELF_MODULE ${ELFSCRIPT_PATH}/ElfScript)
set(ELF_CMAKE ${ELF_MODULE}/ElfScript.cmake)
set(RAYELF_CMAKE ${ELF_MODULE}/addons/raylib/raylib-elfscript.cmake)

if(NOT EXISTS ${ELF_CMAKE})
    set(BUILD_ELFSCRIPT OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        elfscript
        GIT_REPOSITORY https://github.com/ohmtal/ElfScript.git
        GIT_TAG        main
    )
    FetchContent_MakeAvailable(elfscript)

  set(ELF_MODULE "${elfscript_SOURCE_DIR}/ElfScript")
  message("ELF_MODULE PATH IS:" ${ELF_MODULE})
  set(ELF_CMAKE ${ELF_MODULE}/ElfScript.cmake)
  set(RAYELF_CMAKE ${ELF_MODULE}/addons/raylib/raylib-elfscript.cmake)

endif()

if(NOT EXISTS ${ELF_CMAKE})
    message(FATAL_ERROR
        "\n ElfScript path is not set or invalid: ${ELFSCRIPT_PATH} "
        "\n Please provide the path using: "
        "\n cmake -B build -DELFSCRIPT_PATH=/path/to/ElfScript"
    )
else()

 set(RAYLIB_FETCH ON)
 set(RAYELF_DEFAULTMAIN ON)
 set(RAYELF_DKCONSOLE ON)
 set(ELF_ENABLE_CONSOLE_VECTOR ON)
 set(ELF_ENABLE_SLIMOBJECT ON)
 set(ELF_ENABLE_FIELDCACHE ON)
 set(ELF_ENABLE_DOC_EXPORTER ON)
 set(ELF_FILE_EXTENSION "elf" CACHE STRING "ElfScript: File extension")
 set(ELF_APP_NAME "raylib-elfScript" CACHE STRING "ElfScript: App-Name used in scripts")
 set(ELF_APP_VERSION "800" CACHE STRING "ElfScript: App-Version used in scripts")
 set(ELF_APP_VERSION_STRING "Version 0.8" CACHE STRING "ElfScript: App-Version String used in scripts")


 include(${ELF_CMAKE})
 include(${RAYELF_CMAKE})

 set (ELFSCRIPT_INCLUDES
   ${ELF_MODULE}
   ${ELF_MODULE}/addons/raylib/
 )
endif()

# # first try to get the current source
# set(ELFSCRIPT_PATH "/opt/ElfScript" CACHE PATH "Path to ElfScript")
# set(ELF_MODULE ${ELFSCRIPT_PATH}/ElfScript)
# set(ELF_CMAKE ${ELF_MODULE}/ElfScript.cmake)
#
# # fallback to Version 0.3 if not found/configured
# if(NOT EXISTS ${ELF_CMAKE})
#   set(ELF_MODULE "${CMAKE_CURRENT_LIST_DIR}/../lib/ElfScript_v0dot51")
#   set(ELF_CMAKE ${ELF_MODULE}/ElfScript.cmake)
# endif()
#
# # this should not happen ....
# if(NOT EXISTS ${ELF_CMAKE})
#     message(FATAL_ERROR
#         "\n ElfScript path is not set! "
#         "\n Please provide the path using: "
#         "\n cmake -B build -DELFSCRIPT_PATH=/path/to/ElfScript"
#     )
# else()
#
#  set(ELF_APP_NAME "raylib-elfscript" CACHE STRING "ElfScript: App-Name used in scripts" FORCE)
#  set(ELF_APP_VERSION "500" CACHE STRING "ElfScript: App-Version used in scripts" FORCE)
#  set(ELF_APP_VERSION_STRING "Version 26.08" CACHE STRING "ElfScript: App-Version String used in scripts" FORCE)
#
#  # set(ELF_ENABLE_DOC_EXPORTER ON CACHE BOOL "ElfScript: Enable the Doc Exporter addon" FORCE)
#
#
#
#   message( STATUS "\n Using ElfScript: " ${ELF_CMAKE} )
#   include(${ELF_CMAKE})
#
#   set (ELFSCRIPT_INCLUDES
#    ${ELF_MODULE}
#   )
#
#   list(APPEND ELFSCRIPT_SRC ${ELF_MODULE}/addons/console/consoleDocExporter.cpp)
#
# endif()
#
# # ------------- rayLib-elfScript
# set(RAYELF_DIR "${CMAKE_CURRENT_LIST_DIR}/../src" CACHE PATH "Path to RayLib-ElfScript")
# message( STATUS "\n Ray-ElfScript directory is: " ${RAYELF_DIR} )
# set(RAYELF_CMAKE "${RAYELF_DIR}/raylib-elfscript.cmake")
# if(NOT EXISTS ${RAYELF_CMAKE})
#   message(FATAL_ERROR
#     "\n" ${RAYELF_DIR}
#     "\n ********** RayLib-ElfScript not found! *************"
#   )
# else()
#   message( STATUS "\n Include: " ${RAYELF_CMAKE} )
#
#   set(BUILD_EXAMPLES OFF CACHE BOOL "Build raylib examples" FORCE)
#   set(BUILD_GAMES    OFF CACHE BOOL "Build raylib games"    FORCE)
#   set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)
#
#   include(${RAYELF_CMAKE})
# endif()


# ------------- Main
add_executable(${PROJECT_NAME}
    ${PROJECT_SRC}
    ${ELFSCRIPT_SRC}
    ${RAYLIB_ELFSCRIPT_SRC}

)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/
    ${ELFSCRIPT_INCLUDES}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"

    # -- for windows:
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}"

)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)

# Windows - winVolume :: need to set on all builds
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/Zc:wchar_t-")
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        NOMINMAX
        UNICODE
        _UNICODE
    )
endif()


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
