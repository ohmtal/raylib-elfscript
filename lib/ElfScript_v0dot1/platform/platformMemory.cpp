//-----------------------------------------------------------------------------
// Copyright (c) 2012 GarageGames, LLC
// Copyright (c) 2026 XXTH
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#include "platform/platform.h"
#include <string.h>    // For memcpy, memmove, memset, memcmp
#include <stdlib.h>    // For malloc, free

#if !defined(_MSC_VER) && !defined(TORQUE_CPU_ARM64)
#include <immintrin.h> // For _mm_malloc, _mm_free (x86/x64 only)
#endif

void* dMemcpy(void *dst, const void *src, dsize_t size)
{
   return memcpy(dst,src,size);
}

//--------------------------------------
void* dMemmove(void *dst, const void *src, dsize_t size)
{
   return memmove(dst,src,size);
}

//--------------------------------------
void* dMemset(void *dst, S32 c, dsize_t size)
{
   return memset(dst,c,size);
}

//--------------------------------------
S32 dMemcmp(const void *ptr1, const void *ptr2, dsize_t len)
{
   return memcmp(ptr1, ptr2, len);
}

void* dRealMalloc(dsize_t s)
{
   return malloc(s);
}

void dRealFree(void* p)
{
   free(p);
}

// -------------------------------------------------------------------------------------------
// from PlatformMemory
// Don't manage our own memory
void* dMalloc_r(dsize_t in_size, const char* fileName, const dsize_t line)
{
   return malloc(in_size);
}

void dFree(void* in_pFree)
{
   free(in_pFree);
}

void* dRealloc_r(void* in_pResize, dsize_t in_size, const char* fileName, const dsize_t line)
{
   return realloc(in_pResize, in_size);
}

// -------------------------------------------------------------------------------------------
// void *dMalloc_aligned(dsize_t in_size, int alignment)
// {
// #if defined(_MSC_VER)
//     return _aligned_malloc(in_size, alignment);
// #elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
//     return aligned_alloc(alignment, in_size);
// #elif defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
//     void *ptr = NULL;
//     if (posix_memalign(&ptr, alignment, in_size) != 0) return NULL;
//     return ptr;
// #else
//     return _mm_malloc(in_size, alignment);
// #endif
// }
//
// void dFree_aligned(void* p)
// {
// #if defined(_MSC_VER)
//     _aligned_free(p);
// #elif (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || defined(_POSIX_C_SOURCE)
//     free(p);
// #else
//     _mm_free(p);
// #endif
// }


void *dMalloc_aligned(size_t in_size, int alignment)
{
    #if defined(_MSC_VER)
    return _aligned_malloc(in_size, alignment);
    #elif defined(__EMSCRIPTEN__) || defined(__ANDROID__)
    void *ptr = NULL;
    if (posix_memalign(&ptr, alignment, in_size) != 0) return NULL;
    return ptr;
    #elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
    return aligned_alloc(alignment, in_size);
    #elif defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112L
    void *ptr = NULL;
    if (posix_memalign(&ptr, alignment, in_size) != 0) return NULL;
    return ptr;
    #else
    #include <xmmintrin.h>
    return _mm_malloc(in_size, alignment);
    #endif
}

void dFree_aligned(void* p)
{
    #if defined(_MSC_VER)
    _aligned_free(p);
    #elif defined(__EMSCRIPTEN__) || defined(__ANDROID__) || \
    (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L) || \
    defined(_POSIX_C_SOURCE)
    free(p);
    #else
    _mm_free(p);
    #endif
}


