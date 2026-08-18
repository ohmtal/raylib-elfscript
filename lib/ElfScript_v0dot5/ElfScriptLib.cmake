
FIXME need a torqueConfig replacement first !!!!

include( ${CMAKE_CURRENT_LIST_DIR}/ElfScript.cmake)

add_library(ElfScript ${ELFSCRIPT_SRC})
target_include_directories(ElfScript PUBLIC ${CMAKE_CURRENT_LIST_DIR})

# Windows - winVolume :: need to set on all builds
if(MSVC)
    target_compile_options(ElfScript PRIVATE "/Zc:wchar_t-")
    target_compile_definitions(ElfScript PRIVATE
        NOMINMAX
        UNICODE
        _UNICODE
    )
endif()

