//-----------------------------------------------------------------------------
// Copyright (c) 2025-2026 korkscript contributors.
// See AUTHORS file and git repository for contributor information.
// Copyright (c) 2026 Thomas Hühn (XXTH)
//
// SPDX-License-Identifier: MIT
//-----------------------------------------------------------------------------
// NOTE: some of the functions are only inplemented but not tested!!!
//-----------------------------------------------------------------------------
#include "raylib.h"
#include "console/console.h"

extern bool gShutDownRequest;

StringTableEntry osGetTemporaryDirectory(){
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return StringTable->insert("");
}

namespace Platform
{


   //---------------------------------------------------------------------------
   bool isFile(const char *pFilePath) {
      if (!pFilePath) {
         return false;
      }
      return FileExists(pFilePath);
   }
   //---------------------------------------------------------------------------
   bool isDirectory(const char *pDirPath)
   {
     return DirectoryExists(pDirPath);
   }
   //---------------------------------------------------------------------------
   U64 getTime( void )
   {
      return (U64)GetTime();  //double: Get elapsed time in seconds since InitWindow()
   }
   //---------------------------------------------------------------------------
   U64 getRealMilliseconds( void )
   {
      return (U64)(GetTime() * 1000.f);  //double: Get elapsed time in seconds since InitWindow()
   }
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
   StringTableEntry getExecutablePath()
   {
     return StringTable->insert(GetApplicationDirectory());
   }

   //---------------------------------------------------------------------------
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
   //---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
//TODO: ... lot of ... just in time :P ...
//---------------------------------------------------------------------------
void init()
{
   Con::warnf("%s not implemented", __func__);
}

void process()
{
   Con::warnf("%s not implemented", __func__);
}

void shutdown()
{
  // NOTE: silent
  // Con::warnf("%s not implemented", __func__);
}



void restartInstance()
{
   Con::warnf("%s not implemented", __func__);
}


U64 getVirtualMilliseconds( void )
{
   Con::warnf("%s not implemented", __func__);
   return 0;
}


void advanceTime(U32 delta)
{
   Con::warnf("%s not implemented", __func__);
}

void getLocalTime(LocalTime &)
{
   Con::warnf("%s not implemented", __func__);
}
String localTimeToString(Platform::LocalTime const&) {
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return "";
}

S32 compareFileTimes(const FileTime &a, const FileTime &b)
{
   Con::warnf("%s not implemented", __func__);
   return 0;
}

/// Math.
float getRandom()
{
   Con::warnf("%s not implemented", __func__);
   return 3;
}

void outputDebugString(const char *string)
{
   Con::warnf("%s not implemented", __func__);
}
void outputDebugString(const char *string, ...) {
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);

}

StringTableEntry getExecutableName()
{
   Con::warnf("%s not implemented", __func__);
   return StringTable->EmptyString();
}



bool dumpPath(const char *in_pBasePath, Vector<FileInfo>& out_rFileVector, S32 recurseDepth )
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

bool dumpDirectories( const char *path, Vector<StringTableEntry> &directoryVector, S32 depth, bool noBasePath )
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

bool hasSubDirectory( const char *pPath )
{
   Con::warnf("%s not implemented", __func__);
   return false;
}

bool getFileTimes(const char *filePath, FileTime *createTime, FileTime *modifyTime)
{
   Con::warnf("%s not implemented", __func__);
   return false;
}


S32  getFileSize(const char *pFilePath)
{
   Con::warnf("%s not implemented", __func__);
   return 0;

}

//---------------------------------------------------------------------------
bool isSubDirectory(const char *pParent, const char *pDir)
{
   Con::warnf("%s not implemented", __func__);
   return false;
}

bool createPath(const char *path)
{
   Con::warnf("%s not implemented", __func__);
   return false;
}

bool fileDelete(const char *name)
{
   Con::warnf("%s not implemented", __func__);
   return false;
}

bool fileRename(const char *oldName, const char *newName)
{
   Con::warnf("%s not implemented", __func__);
   return false;
}

bool fileTouch(const char *name)
{
   Con::warnf("%s not implemented", __func__);
   return false;
}

bool pathCopy(const char *fromName, const char *toName, bool nooverwrite)
{
   Con::warnf("%s not implemented", __func__);
   return false;
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
