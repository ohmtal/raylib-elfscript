//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#pragma once

// ----------------------------------------------------------------------------
// enable #define in torque script
// removed now default #define ELFSCRIPT_PREPROCESSOR

// fast path for int and float fields
//remove is now default #define ELFSCRIPT_FASTPATH_FLD

// fast path test for struct << i do test this in CrazyElf
// #define ENABLE_CONSOLE_VECTOR

// added Integer operation, which should give a huge speed up but ended in a slower test!
// also only tested with a for loop $foo++ still used float ...
// i should live with it or add typed variables and modified the monster to keep type safety
// Good idea but is slower !!!!! #define ELFSCRIPT_INT_HACK

// When set you need to write your own exec engine function
// #define ELFSCRIPT_EXEC_OVERWRITE

// Autodelete objects on shutdown - this can slowdown delete on many objects
// #define ELFSCRIPT_GARBAGECOLLECTION





// ----------------------------------------------------------------------------
#define TORQUE_SCRIPT_EXTENSION   "elf"
#define TORQUE_APP_NAME            "ElfTestBed"
#define TORQUE_APP_VERSION         1000
#define TORQUE_APP_VERSION_STRING  "26.06.24.0"
#define TORQUE_DISABLE_MEMORY_MANAGER
/* #undef TORQUE_DISABLE_VIRTUAL_MOUNT_SYSTEM */
/* #undef TORQUE_DISABLE_FIND_ROOT_WITHIN_ZIP */
/* #undef TORQUE_ZIP_DISK_LAYOUT */
/* #undef TORQUE_LOWER_ZIPCASE */
#define TORQUE_NO_DSO_GENERATION
/* #undef TORQUE_ENABLE_PROFILER */



// TORQUE_DEBUG is now set dynamically and not here anymore
// #define TORQUE_DEBUG
/* #undef TORQUE_SHIPPING */
/* #undef TORQUE_DEBUG_NET */
/* #undef TORQUE_DEBUG_NET_MOVES */
//#define MAXPACKETSIZE 1500
//#define TORQUE_DEBUG_GUARD
//#define TORQUE_ENABLE_THREAD_STATICS
//#define TORQUE_ENABLE_THREAD_STATIC_METRICS
//#define FRAMEALLOCATOR_DEBUG_GUARD

/// This #define is used by the FrameAllocator to set the size of the frame.
///
/// It was previously set to 3MB but I've increased it to 32MB due to the
/// FrameAllocator being used as temporary storage for bitmaps in the D3D9
/// texture manager.
#define TORQUE_FRAME_SIZE     32 << 20

