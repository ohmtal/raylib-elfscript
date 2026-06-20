# raylib-elfscript (WiP) 
 
Raylib binding of Elf(Torque)Script.

2026-06-20: A lot (80-90% excluding VR stuff) of bindings are implemented but not tested.  

## Setup: 

I usually have the TorqueScript Source in "/opt/TorqueScript" which is set as default in CMake. 
But you can also put it somewhere else and need to add the path to cmake like:

    git pull https://github.com/ohmtal/TorqueScript.git

and then

    cmake -S . -B build -DELFSCRIPT_PATH="/whereIHaveMySource/TorqueScript"
    cmake --build build
    ./raylib-elfscript

    
## First Script assets/main.cs

If you wonder why the the script file ends with .cs. This is not CSharp it's CScript (back from 1999).

![Basic Window](./docu/Screenshot_2026-06-16_02-47-32.png)

There are three functions called from the C Code to get it working:

    - function MainInit() { return true;}
    - function MainLoop() {}
    - function MainShutDown() {}
    
The Script is:

```
function MainInit() {
    // Initialization
    //--------------------------------------------------------------------------------------
    $screenWidth = 800;
    $screenHeight = 450;

    InitWindow($screenWidth, $screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    return true;
}

function MainShutDown() {
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
}

function MainUpdate()
{
    // Update
    //----------------------------------------------------------------------------------
    // TODO: Update your variables here
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground("20 60 20");

    DrawText("Congrats! You created your first window!", 190, 200, 20, "200 200 200 255");

    EndDrawing();
    //----------------------------------------------------------------------------------

    return 0;
}

```
    
