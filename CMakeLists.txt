cmake_minimum_required(VERSION 3.24)
# -----------------------------------------------------------------------------
# Project settings:

project(raylib-elfscript)
set(PROJECT_SRC
    src/main.cpp
    src/interface/defaultMain.cpp
    src/interface/platformProcess.cpp
    src/interface/ConsoleTypes.cpp
    src/interface/elfBase.cpp
    src/interface/elfCore.cpp
    src/interface/elfEnum.cpp
    src/interface/elfResource.cpp
    src/interface/elfTextures.cpp
    src/interface/elfText.cpp
    src/interface/elfImageResource.cpp
    src/interface/elfCamera.cpp
    src/interface/elfShapes.cpp
    src/interface/elfModels.cpp
    src/interface/elfAudio.cpp
    src/interface/elfShader.cpp
    src/interface/elfFile.cpp
    src/interface/elfBatchRender.cpp
    src/interface/elfLights.cpp

    src/gui/Gui.cpp
    src/gui/ConsoleGuiObject.cpp

    src/objects/starfield.cpp

    lib/ohmflux/grid/basicgrid.cpp
    src/objects/Grid.cpp

)



set (ASSET_PATH ${CMAKE_CURRENT_LIST_DIR}/assets@assets)
# -----------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
# -----------------------------------------------------------------------------




# -----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent)

# ------------- RayLib
# set(PLATFORM "SDL" CACHE STRING "raylib platform" FORCE)
set(RAYLIB_DIR "${CMAKE_CURRENT_LIST_DIR}/lib/raylib" CACHE PATH "Path to RayLib")
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
set(ELFSCRIPT_PATH "/opt/ElfScript" CACHE PATH "Path to ElfScript")
set(ELF_MODULE ${ELFSCRIPT_PATH}/ElfScript)
set(ELF_CMAKE ${ELF_MODULE}/ElfScript.cmake)
# set(ELF_MODULE ${ELFSCRIPT_PATH}/TorqueScript)
# set(ELF_CMAKE ${ELF_MODULE}/TorqueScript.cmake)

if(NOT EXISTS ${ELF_CMAKE})
    message(FATAL_ERROR
        "\n TorqueScript path is not set! "
        "\n Please provide the path using: "
        "\n cmake -B build -DELFSCRIPT_PATH=/path/to/ElfScript"
    )
else()
 #  defines TORQUESCRIPT_SRC
 include(${ELF_CMAKE})

  set (ELFSCRIPT_INCLUDES
   ${ELF_MODULE}
  )


  if(WIN32)

  elseif(UNIX)
      list(APPEND ELFSCRIPT_SRC ${ELF_MODULE}/addons/shellConsole/POSIXConsole.cpp)
  endif()

endif()


# ------------- Main
add_executable(${PROJECT_NAME}
    ${PROJECT_SRC}
    # ${TORQUESCRIPT_SRC}
    ${ELFSCRIPT_SRC}


)

target_include_directories(${PROJECT_NAME} PRIVATE
    # ${CMAKE_CURRENT_LIST_DIR}/
    ${CMAKE_CURRENT_LIST_DIR}/src/
    ${CMAKE_CURRENT_LIST_DIR}/lib/
    ${ELFSCRIPT_INCLUDES}
)


target_compile_definitions(${PROJECT_NAME} PUBLIC IMGUI_DEFINE_MATH_OPERATORS)



set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
)


# Web Configurations
# WEB Example compile (arch)
	# cmake -S . -B web_debug \
	# 	-DCMAKE_TOOLCHAIN_FILE=/usr/lib/emscripten/cmake/Modules/Platform/Emscripten.cmake \
	# 	-DCMAKE_BUILD_TYPE=Debug \
	# 	-DPLATFORM=Web
	# cmake --build build_webdebug -j 4
# Web Run: (bash)
#  source /etc/profile.d/emscripten.sh
#  emrun raylib-elfscript.html
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
