# ElfScript

This is the enhanced Version of TorqueScript. 

- constants preprocessor
- field type fast path
- stability fixes
- memleak fixes.
- and more ....

I already worked on ElfScript bindings for: 

- Basic Demo for Testing Script only: [demo](./demo)
- ImGui and SDL3 bindings demo with BaseFlux: [BaseElf](../BaseElf)
- OhmFlux (ElfTest) [OhmFlux](https://github.com/ohmtal/OhmFlux)
- raylib-elfScript [raylib-elfScript](https://github.com/ohmtal/raylib-elfscript)
- ElfFlux raylib-elfScript with Objects [ElfFlux](https://github.com/ohmtal/ElfFlux)

## how to use 

Add this to your code (where assets the folder where my scripts live):

MyLogger example, where ***Log*** is my Log function:
```
    void MyLogger(U32 level, const char *consoleLine)
    {
        switch (level) {
            case 1: Log("[warn] %s",  consoleLine); break;
            case 2: Log("[error] %s",  consoleLine); break;
            default: Log("%s",  consoleLine); break;
        }
    }
```

When you startup (Init) add:
```
    #include "main/engineGlue.h"
    .....
    String workingDir = getGamePath().c_str();
    engineGlue::init(MyLogger, workingDir);

```

Load a Script example:
```
        std::string fileName = "assets/main.cs"; //fixme command line parameter for file

        if (!Con::executeFile(fileName.c_str(), false, false)) {
            return false;
        }
```

Execute inline code example:
```
    Con::evaluate( R"(
            function onDebugTest() {
                %res = getRandom(1);
                echo("should be" SPC %res);
                return %res ? "true" : "false";
            }
        )"
    );
    ConsoleValue result = Con::executef("onDebugTest");
    Con::printf("Test result is %d, as string: %s", result.getBool(), result.getString());
```



on the end of your program (Shutdown):
```
        engineGlue::shutDown(); //Before Deinitialize else crash!
        FluxMain::Deinitialize();
```

In your Mainloop:
```
        // advance Torque Time for schedule
        static U32 lastTick = 0;
        engineGlue::process(SDL_GetTicks() - lastTick);
        lastTick = SDL_GetTicks();

```


# Android

- posixVolume does not work with apk's. Possible solution: 
    - dont use ExecuteFile load the script with sdl for example 
    - you need to overwrite exec view inline script to use you own

My fix on OhmFlux:

Defined in my ElfFlux Namespace:

```
// NOTE: Android hackfest use this instead of Con::executeFile
bool executeFile(const char* fileName, bool noCalls , bool journalScript)  {
    if (!fileName) return false;

    // expand ./ 
    char scriptFilenameBuffer[1024];
    Con::expandScriptFilename(scriptFilenameBuffer, sizeof(scriptFilenameBuffer), fileName);

    std::string script = "";
    if (FluxFile::LoadTextFile(scriptFilenameBuffer, script)) {
        if (script.empty()) return false;
        // TODO? Con::EvalResult
        StringTableEntry _fileName = StringTable->insert((scriptFilenameBuffer));
        CodeBlock* newCodeBlock = new CodeBlock();
        newCodeBlock->compileExec(_fileName, script.c_str(), false,  -1);
        return true;
    }
    return false;
}
```

My include binding:
```
DefineEngineFunction(include,bool, (String fileName, bool nocalls),(true), "include(fileName)" "exec a file without calls" ){
    //ELFFLUX!!
    return ElfFlux::executeFile(fileName, true);
}

```

On Init I do:
```
    Con::evaluate( R"(
        function exec(%filename) {
            return include(%filename, false);
        }
    )"
    );
```
