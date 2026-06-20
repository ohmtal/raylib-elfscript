// Main Script

$MODULES="Eyes DeltaTime";

function Main::init(%this) {
    SetConfigFlags(%this.flags );

    InitWindow(%this.screenWidth, %this.screenHeight,  "raylib-elfScript Demo Loader");
    SetTargetFPS(%this.currentFps);

    // Image/Icon Test
    // LoadImage return a Image identifier (imageId)
    %this.iconImg = LoadImage("assets/texture/raylib_32x32.png");
    SetWindowIcon(%this.iconImg);
    // IconImg can be unloaded now, but i keep it for later testing texture.
    // It's unloaded when programm ends automaticly
    //  UnloadImage(%this.iconImg);

    // SetExitKey(0); // i want to use escape to unload module and display a module list
    %this.loadModule();
}

function Main::loadModule(%this, %setNewModuleIndex) {
    if (%setNewModuleIndex !$= "" ) {
        %this.moduleIndex = %setNewModuleIndex;
    }
    %cnt = getWordCount($MODULES);
    if (%this.moduleIndex >= %cnt)  %this.moduleIndex = 0;
    if (%this.moduleIndex < 0 ) %this.moduleIndex = %cnt - 1;

    %this.moduleName = getword($MODULES, %this.moduleIndex);

    if (!exec("assets/modules/" @ %this.moduleName @ ".cs")) {
        error("Failed to load module" SPC %this.moduleName);
    }

    if (isObject(%this.module)) {
        %this.module.delete();
    }
    %cmd = %this.getId() @ ".module = Create" @ %this.moduleName @ "();";
    echo("loadModule command is:" SPC %cmd);
    eval(%cmd);
    echo("loadModule success:" SPC isObject(%this.module));
    if (isObject(%this.module)) {
        %this.module.init();
    }
}

function Main::loop(%this) {
    if (isObject(%this.module)){
        %this.module.update();
    }
    if ( IsKeyDown($KEY_LEFT_CONTROL) || IsKeyDown($KEY_LEFT_CONTROL) ) {
        if (IsKeyPressed($KEY_UP)) {
          %this.moduleIndex--;
          %this.loadModule();
        } else  if (IsKeyPressed($KEY_DOWN)) {
            %this.moduleIndex++;
            %this.loadModule();
        } else if (IsKeyPressed($KEY_R)) {
            rl();
        }
    }

    BeginDrawing();
    ClearBackground("20 100 100");
    if (isObject(%this.module)){
        DrawText("Loaded module:" SPC %this.moduleName , 5, GetScreenHeight() - 30, 20, $BLUE);
        %this.module.render();
    } else {
        DrawText("Failed to load module:" SPC %this.moduleName, 5, GetScreenHeight() - 30, 16, $GREEN);
    }
    DrawText("CTRL + UP or DOWN to load an other module."  , 5, GetScreenHeight() - 50, 14, $BLACK);
    EndDrawing();
}

// -----------------------------------------------------------------------------
// -----------------------------------------------------------------------------
function MainInit() {

    $Main = new ScriptObject() {
        class = "Main";
        TypeS32 screenWidth = 800;
        TypeS32 screenHeight = 450;
        TypeS32 currentFps = 60;
        TypeS32 flags = $FLAG_WINDOW_RESIZABLE;
        TypeS32 moduleIndex = 0;
        TypeS32 module = 0;
    };


    $Main.init();

    return true;
}
function MainShutDown() {
    $Main.delete();
    CloseWindow();        // Close window and OpenGL context
}

function MainLoop() {
    $Main.loop();
}

function rl() { exec("assets/main.cs");}
