//-----------------------------------------------------------------------------
// FIXME this is only to get over linker errors ....
// FIXME scripts will not work until you fixed this
//-----------------------------------------------------------------------------


// ~~~ 1. add includes... ~~~
// #include <SDL3/SDL.h>
#include <console/console.h>
#include <string>
// #include <vector>
// #include <platform/platformProcess.h>



StringTableEntry osGetTemporaryDirectory(){
    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
    return StringTable->insert("");
}


namespace Platform
{
    String localTimeToString(Platform::LocalTime const&) {
          Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
          return "";
    }

    void outputDebugString(const char *string, ...) {
         Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);

    }
   const char* getClipboard() {
      Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
      return nullptr;
   }

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

   // StringTableEntry getMainDotCsDir() {
   //    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   //    return StringTable->insert("");
   // }

   // /// Set main.tscript directory. Used in runEntryScript()
   // void setMainDotCsDir(const char *dir) {
   //    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   // }

   void postQuitMessage(const S32 in_quitVal)
   {
      Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   }

//    bool isFullPath(const char* path)
// {
//     Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
//    return false;
// }
// char * makeFullPathName(const char* path, char* buffer, U32 size, const char* cwd)
// {
//     Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
//     static std::string foo = "";
//    return foo.data();
// }


    void debugBreak()
   {
      Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   }
   bool setClipboard(const char* text)
   {
      Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
      return false;
   }


   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   bool isFile(const char *pFilePath) {
      Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
      if (!pFilePath) {
         return false;
      }
      // SDL_PathInfo info;
      // // Returns true on success, false on failure (e.g., path doesn't exist)
      // if (SDL_GetPathInfo(pFilePath, &info)) {
      //    return (info.type == SDL_PATHTYPE_FILE);
      // }

      return false;
   }
   //---------------------------------------------------------------------------
   // U32 => U64!
   U64 getTime( void )
   {
      Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
      // SDL_Time nanoSeconds;
      // if (SDL_GetCurrentTime(&nanoSeconds)) {
      //    return (U64)(nanoSeconds / SDL_NS_PER_SECOND);
      // }
      // Con::warnf("%s failed!", __func__);
      return 0;
   }
   //---------------------------------------------------------------------------
   // U32 => U64!
   U64 getRealMilliseconds( void )
   {
      Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
      // SDL_Time nanoSeconds;
      // if (SDL_GetCurrentTime(&nanoSeconds)) {
      //    return (U64)(nanoSeconds / SDL_NS_PER_MS);
      // }
      // Con::warnf("%s failed!", __func__);
      return 0;
   }

   //---------------------------------------------------------------------------
   //---------------------------------------------------------------------------
   //TODO: ... lot of ... just in time :P ...
   //---------------------------------------------------------------------------
   void init()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

void process()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

void shutdown()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

#if defined(_WIN32) || defined(__WIN32__) || defined(MSC_VER)
#include <windows.h>
#define platform_sleep(ms) Sleep(ms)
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__)
#include <time.h>
void sleep(unsigned int ms) {
    struct timespec ts;
    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;
    nanosleep(&ts, NULL);
}
#else
#error "UNKNOWN OS"
#endif




void restartInstance()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

void postQuitMessage(const U32 in_quitVal)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

void forceShutdown(S32 returnValue)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

StringTableEntry getUserHomeDirectory()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return nullptr;
}

StringTableEntry getUserDataDirectory()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return nullptr;
}


// XXTH U64!
U64 getVirtualMilliseconds( void )
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return 0;
}


void advanceTime(U32 delta)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

void getLocalTime(LocalTime &)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

S32 compareFileTimes(const FileTime &a, const FileTime &b)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return 0;
}

/// Math.
float getRandom()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return 3;
}

void outputDebugString(const char *string)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
}

/// File IO.
// StringTableEntry getWorkingDirectory()
// {
//    Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
//
//    return nullptr;
//
// }
//
// bool setWorkingDirectory(StringTableEntry newDir)
// {
//     Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
//
//    (void)newDir;
//    return false;
//
// }

// StringTableEntry getCurrentDirectory()
// {
//    return getWorkingDirectory();
// }
//
// bool setCurrentDirectory(StringTableEntry newDir)
// {
//    return setWorkingDirectory(newDir);
// }

StringTableEntry getExecutableName()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
    return StringTable->insert("");
}

StringTableEntry getExecutablePath()
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
    return StringTable->insert("");
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
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}


bool getFileTimes(const char *filePath, FileTime *createTime, FileTime *modifyTime)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}


S32  getFileSize(const char *pFilePath)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return 0;

}

bool isDirectory(const char *pDirPath)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

bool isSubDirectory(const char *pParent, const char *pDir)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

bool createPath(const char *path)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

bool fileDelete(const char *name)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

bool fileRename(const char *oldName, const char *newName)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

bool fileTouch(const char *name)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

bool pathCopy(const char *fromName, const char *toName, bool nooverwrite)
{
   Con::warnf(" %s not implemented (%s:%d)", __func__, __FILE__, __LINE__);
   return false;
}

}
