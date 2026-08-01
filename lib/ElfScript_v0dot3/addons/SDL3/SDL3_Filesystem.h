//-----------------------------------------------------------------------------
// Copyright (c) 2026 Thomas Hühn (XXTH)
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
/*
 *
 * [X] = implemented and tested
 * [_] = implemented untested
 * [~] = not implemented and not planed to
 *
[X] SDL_GetError NOTE defined here !!! can be cause problems when it's also defined somewhere else
        so i added ifndef SDL_FILESYSTEM_NO_GET_ERROR
[X] SDL_GetPathInfo + SDL_FileExists
[X] SDL_CopyFile
[X] SDL_CreateDirectory
[X] SDL_GetBasePath
[X] SDL_GetCurrentDirectory
[X] SDL_GetPrefPath
[X] SDL_GetUserFolder
[X] SDL_RemovePath
[X] SDL_RenamePath
[X] SDL_GlobDirectory
----
[~] SDL_EnumerateDirectory NOTE not implemented useing SDL_GlobDirectory should work fine
*/
//-----------------------------------------------------------------------------
#pragma once
namespace ElfSDL3 {
    void RegisterFileSystemConstants();
} //namespace
