//-----------------------------------------------------------------------------
// Copyright (c) 2025-2026 korkscript contributors.
// See AUTHORS file and git repository for contributor information.
// Copyright (c) 2026 Thomas Hühn (XXTH)
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
#include "raylib.h"
#include "console/console.h"

extern bool gShutDownRequest;

namespace Platform
{
  //---------------------------------------------------------------------------
  void postQuitMessage(const S32 in_quitVal)
  {
    gShutDownRequest = true;
  }

  void forceShutdown(S32 returnValue)
  {
    gShutDownRequest = true;
  }
  //---------------------------------------------------------------------------
  // init / process / shutdown - called from engineGlue only
  void init() { }
  void process() { }
  void shutdown() { }
  //---------------------------------------------------------------------------
  bool isFile(const char *pFilePath) {
    if (!pFilePath) {
      return false;
    }
    return FileExists(pFilePath);
  }

  // ElfScript 0.6 obsolete
  bool isDirectory(const char *pDirPath)
  {
    return DirectoryExists(pDirPath);
  }

  StringTableEntry getExecutablePath()
  {
    return StringTable->insert(GetApplicationDirectory());
  }

  StringTableEntry getUserHomeDirectory()
  {
    char path[512] = { 0 };

    #if defined(_WIN32)
    const char* appData = getenv("USERPROFILE");
    if (appData) snprintf(path, sizeof(path), "%s", appData);

    #elif defined(__ANDROID__)
    snprintf(path, sizeof(path), "%s", GetAndroidAppDirectory());

    #elif defined(__EMSCRIPTEN__)
    snprintf(path, sizeof(path), "%s",  "/home/web_user");

    #elif defined(__unix__)
    const char* home = getenv("HOME");
    if (home) snprintf(path, sizeof(path), "%s", home);

    #elif defined(__APPLE__)
    const char* home = getenv("HOME");
    if (home) snprintf(path, sizeof(path), "%s", home);
    #endif

    return StringTable->insert(path);
  }

  // ElfScript 0.6 obsolete
  StringTableEntry getUserDataDirectory()
  {
    char path[512] = { 0 };

    #if defined(_WIN32)
    const char* appData = getenv("APPDATA");
    if (appData) snprintf(path, sizeof(path), "%s", appData);

    #elif defined(__ANDROID__)
    snprintf(path, sizeof(path), "%s", GetAndroidAppDirectory());

    #elif defined(__EMSCRIPTEN__)
    snprintf(path, sizeof(path), "%s",  "/home/web_user");

    #elif defined(__unix__)
    const char* home = getenv("HOME");
    if (home) snprintf(path, sizeof(path), "%s/.local/share", home);

    #elif defined(__APPLE__)
    const char* home = getenv("HOME");
    if (home) snprintf(path, sizeof(path), "%s/Library/Application Support", home);
    #endif

    return StringTable->insert(path);
  }
  //---------------------------------------------------------------------------
  U64 getTime( void )
  {
    return (U64)GetTime();  //double: Get elapsed time in seconds since InitWindow()
  }
  U64 getRealMilliseconds( void )
  {
    return (U64)(GetTime() * 1000.f);  //double: Get elapsed time in seconds since InitWindow()
  }

  //---------------------------------------------------------------------------
  bool setClipboard(const char* text)
  {
    SetClipboardText(text);
    return true;
  }

  const char* getClipboard() {
    return GetClipboardText();
  }
  //---------------------------------------------------------------------------
  void sleep(U32 ms)
  {
    WaitTime((F32)ms / 1000.f);
  }


  void getLocalTime(LocalTime &)
  {
    Con::warnf("%s not implemented", __func__);
  }

  /// Math.
  float getRandom()
  {
    return (float)GetRandomValue(0, 1000000) / 1000000.0f;
  }


  void debugBreak()
  {
    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
  }

  //
  void AlertOK(const char *windowTitle, const char *message) {
    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);

  }
  bool AlertOKCancel(const char *windowTitle, const char *message) {
    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
    return false;
  }
  bool AlertRetry(const char *windowTitle, const char *message) {
    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
    return false;
  }
  ALERT_ASSERT_RESULT AlertAssert(const char *windowTitle, const char *message)
  {
    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
    return ALERT_ASSERT_IGNORE;
  }

} //namespace
// ------------------------ ElfScript 0.6 removed but keept for compat ---------------------------
StringTableEntry osGetTemporaryDirectory(){ return StringTable->insert(""); }
namespace Platform
{
void restartInstance() { }
U64 getVirtualMilliseconds( void ) { return 0; }
void advanceTime(U32 delta) { }
String localTimeToString(Platform::LocalTime const&) { return ""; }
S32 compareFileTimes(const FileTime &a, const FileTime &b) { return 0; }
void outputDebugString(const char *string) { }
void outputDebugString(const char *string, ...) { }
StringTableEntry getExecutableName() { return StringTable->EmptyString(); }
bool dumpPath(const char *in_pBasePath, Vector<FileInfo>& out_rFileVector, S32 recurseDepth ) { return false; }
bool dumpDirectories( const char *path, Vector<StringTableEntry> &directoryVector, S32 depth, bool noBasePath ) { return false; }
bool hasSubDirectory( const char *pPath ) { return false; }
bool getFileTimes(const char *filePath, FileTime *createTime, FileTime *modifyTime) { return false; }
S32  getFileSize(const char *pFilePath) { return 0; }
bool isSubDirectory(const char *pParent, const char *pDir) { return false; }
bool createPath(const char *path) { return false; }
bool fileDelete(const char *name) { return false; }
bool fileRename(const char *oldName, const char *newName) { return false; }
bool fileTouch(const char *name) { return false; }
bool pathCopy(const char *fromName, const char *toName, bool nooverwrite) { return false; }
} //namespace
