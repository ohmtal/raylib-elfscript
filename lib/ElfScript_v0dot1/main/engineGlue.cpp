//------------------------------------------------------------------------------
#include "console/console.h"
#include "console/script.h"
#include "console/engineAPI.h"
#include <platform/platformVolume.h>
#include "engineGlue.h"
//--------------------------------------------------------------------------------------
namespace engineAPI
{
    bool gUseConsoleInterop = true;
    bool gIsInitialized = false;
}
namespace engineGlue
{
    // -----------------------------------------------------------------------------
    void DefaultLogger(U32 level, const char *consoleLine)
    {
        switch (level) {
            case 1: dPrintf("[warn] %s\n",  consoleLine); break;
            case 2: dPrintf("[error] %s\n",  consoleLine); break;
            default: dPrintf("%s\n",  consoleLine); break;
        }
    }
    // -----------------------------------------------------------------------------
    void init( ConsumerCallback LogFunc, String workingDirectory )
    {
        // Asserts should be created FIRST
        PlatformAssert::create();
        // ManagedSingleton< ThreadManager >::createSingleton();
        FrameAllocator::init(TORQUE_FRAME_SIZE);      // See comments in torqueConfig.h
        _StringTable::create();
        Con::init();


        Platform::FS::InstallFileSystems(); // install all drives for now until we have everything using the volume stuff
        //NOT Platform::FS::MountDefaults();

        if (!workingDirectory || workingDirectory.isEmpty()) {
            workingDirectory = Platform::getExecutablePath();
        }

        // sanity again:
        if ( workingDirectory && !workingDirectory.isEmpty()) {
            // must have a traling slash for setCwD
            if (!workingDirectory.endsWith("/")) {
                workingDirectory += "/";
            }
            const char* dir = workingDirectory.c_str();
            Platform::FS::SetCwd(dir);
            Platform::setMainDotCsDir(dir);
            // NOTE does Torque::FS::SetCwd
            // Platform::setCurrentDirectory(workingDirectory);
        }



        //FIXME nount config directory if needed  !!



        //XXTH directoy stuff is a  mess:
        /*
            - in platformFileIO: void Platform::setMainDotCsDir(const char *dir)
            - in volume setCWD
            - in (my)PlatformProcess:
                - setWorkingDirectory
                - setCurrentDirectory

                which is all stripped on ExecuteFile
                and the mounted direcotries are used in platformFileIO
                no idea how to get rid of the mess.


            1.) MountDefaults:
                - getExecutableName
            2.) Additional mounts could be
                - config path << NOTE there is not platform call at all !!!
            3.) setCWD to the directory we want to load the content:
                - default assets
                    - so it would be main.cs / sound/mysound.ogg .....
            USELESS ? :
                - setMainDotCsDir / getMainDotCsDir
                    platform/platformFileIO.cpp:      cwd = Con::isCurrentScriptToolScript() ? Platform::getMainDotCsDir() : Platform::getCurrentDirectory();
                    platform/platformFileIO.cpp:      dSprintf( buffer, sizeof( buffer ), "%s/", Platform::getMainDotCsDir() );
                    platform/platformFileIO.cpp:      dSprintf( buffer, sizeof( buffer ), "%s/%s/", Platform::getMainDotCsDir(), to );
                    platform/platformFileIO.cpp:      dSprintf( buffer2, sizeof( buffer2 ), "%s/%s", Platform::getMainDotCsDir(), path );
                    platform/platformFileIO.cpp:   StringTableEntry str = tryStripBasePath(path, Platform::getMainDotCsDir());
                    platform/stub/platformProcess.cpp:   // StringTableEntry getMainDotCsDir() {
                    platform/platform.h:   StringTableEntry getMainDotCsDir();
                    platform/platform.h.ORIG:   StringTableEntry getMainDotCsDir();
                    main/engineGlue.cpp:        Platform::setCurrentDirectory( Platform::getMainDotCsDir() );
                    core/util/zip/test/zipTest.h:   Platform::makeFullPathName(ZIPTEST_WORKING_DIR, dir, sizeof(dir), Platform::getMainDotCsDir());
                    console/console.cpp:   const StringTableEntry exePath = Platform::getMainDotCsDir();
                    console/console.cpp:      const StringTableEntry exePath = Platform::getMainDotCsDir();
                    console/scriptFilename.cpp:      { Platform::getMainDotCsDir(), "" },
                    console/torquescript/codeBlock.cpp:   const StringTableEntry exePath = Platform::getMainDotCsDir();
                    console/torquescript/codeBlock.cpp:      const StringTableEntry exePath = Platform::getMainDotCsDir();
                    console/fileSystemFunctions.cpp:DefineEngineFunction( getMainDotCsDir, String, (),,
                    console/fileSystemFunctions.cpp:   return Platform::getMainDotCsDir();

                - setCurrentDirectory / getCurrentDirectory
                    platform/platformFileIO.cpp:      path = Platform::getCurrentDirectory();
                    platform/platformFileIO.cpp:      cwd = Con::isCurrentScriptToolScript() ? Platform::getMainDotCsDir() : Platform::getCurrentDirectory();
                    platform/platformFileIO.cpp:   str = tryStripBasePath(path, Platform::getCurrentDirectory());
                    platform/stub/platformProcess.cpp:StringTableEntry getCurrentDirectory()
                    platform/platform.h:   StringTableEntry getCurrentDirectory();
                    platform/platform.h.ORIG:   StringTableEntry getCurrentDirectory();
                    main/engineGlue.cpp:                    platform/platformFileIO.cpp:      cwd = Con::isCurrentScriptToolScript() ? Platform::getMainDotCsDir() : Platform::getCurrentDirectory();
                    console/console.cpp:   StringTableEntry workingDirectory = pWorkingDirectoryHint != NULL ? pWorkingDirectoryHint : Platform::getCurrentDirectory();
                    console/scriptFilename.cpp:      { Platform::getCurrentDirectory(), "" },
                    console/consoleFunctions.cpp:      addr = String::ToString("file://%s/%s", Platform::getCurrentDirectory(), address);
                    console/torquescript/codeBlock.cpp:   const StringTableEntry cwd = Platform::getCurrentDirectory();
                    console/torquescript/codeBlock.cpp:      const StringTableEntry cwd = Platform::getCurrentDirectory();
                    console/fileSystemFunctions.cpp:   return Platform::getCurrentDirectory();
                    console/fileSystemFunctions.cpp:DefineEngineFunction( getCurrentDirectory, String, (),,
                    console/fileSystemFunctions.cpp:   return Platform::getCurrentDirectory();

                - setWorkingDirectory / getWorkingDirectory
                    platform/stub/platformProcess.cpp:StringTableEntry getWorkingDirectory()
                    platform/stub/platformProcess.cpp:   return getWorkingDirectory();
                    console/fileSystemFunctions.cpp:   //dSprintf(fullpath, 511, "%s/%s", Platform::getWorkingDirectory(), path);
                    console/fileSystemFunctions.cpp:DefineEngineFunction(getWorkingDirectory, String, (),,
                    console/fileSystemFunctions.cpp:   "@see getWorkingDirectory()"

           NOTE: also if i set all the pathes i have to set main.cs with path 'assets/main.cs


        */

        Platform::init();    // platform specific initialization
        // Set engineAPI initialized to true
        engineAPI::gIsInitialized = true;
        Sim::init();

        if (!LogFunc) {
            Con::addConsumer(mLogger);
        } else {
            Con::addConsumer(LogFunc);
            mLogger = LogFunc;
        }


        Con::printf("APP: %s %s (%d)", TORQUE_APP_NAME, TORQUE_APP_VERSION_STRING, TORQUE_APP_VERSION);
        Con::printf("Current script directory: %s ",Torque::FS::GetCwd().getFullPath().c_str() );



    }
    // -----------------------------------------------------------------------------
    // SimTime U32 ms since last Loop
    void process(SimTime delta) {
        Sim::advanceTime(delta);
        ConsoleValue::resetConversionBuffer();
    }
    // -----------------------------------------------------------------------------
    void shutDown() {
        Sim::shutdown();

        Platform::shutdown();

        Con::shutdown();

        _StringTable::destroy();
        FrameAllocator::destroy();
        // asserts should be destroyed LAST
        PlatformAssert::destroy();

        Con::removeConsumer(mLogger);
        engineAPI::gIsInitialized = false;

    }
} //engineGlue
