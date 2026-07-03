//------------------------------------------------------------------------------
// Lights and Gui Demo
//------------------------------------------------------------------------------
function createLights() {
    %obj = new ScriptObject() {
        class = "Lights";
    };

    // ---- camera
    %obj.camera = new Camera3DObject() {
        position = "2.0 4.0 6.0";    // Camera position
        target = "0.0 0.5 0.0";      // Camera looking at point
        up = "0.0 1.0 0.0";          // Camera up vector (rotation towards target)
        fovy = 45.0;                  // Camera field-of-view Y
        projection = CAMERA_PERSPECTIVE;  // Camera projection type
    };

    // ---- shader
    // Load basic lighting shader

    %obj.shader = LoadShader(
        "assets/shaders/glsl" @ GLSL_VERSION @ "/lighting.vs",
        "assets/shaders/glsl" @ GLSL_VERSION @ "/lighting.fs"
    );
    echo("** Loader shaderId:" SPC %obj.shader);

    %obj.viewPosLoc = GetShaderLocation(%obj.shader, "viewPos");
    SetShaderLocation(%obj.shader, SHADER_LOC_VECTOR_VIEW, %obj.viewPosLoc);

    // in short but i need the viewPosLoc later!
    // SetShaderLocationByUniformName(%obj.shader, SHADER_LOC_VECTOR_VIEW, "viewPos");

    // Ambient light level (some basic lighting)
    %obj.ambientLoc = GetShaderLocation(%obj.shader, "ambient");
    %ambient = "0.1 0.1 0.1 1.0";
    SetShaderValue(%obj.shader, %obj.ambientLoc, %ambient, SHADER_UNIFORM_VEC4);

    // ---- lights

    %obj.l0 = new LightObject() {
        enabled = true;
        shaderId = %obj.shader;
        type = LIGHT_POINT;
        position = "-2 1 -2";
        target = VEC3_ZERO;
        color = ORANGE;

         caption = "O";
    };
    %obj.l1 = new LightObject() {
        enabled = true;
        shaderId = %obj.shader;
        type = LIGHT_POINT;
        position = "2 1 2";
        target = VEC3_ZERO;
        color = RED;

        caption = "R";
    };

    %obj.l2 = new LightObject() {
        enabled = true;
        shaderId = %obj.shader;
        type = LIGHT_POINT;
        position = "-2 1 2";
        target = VEC3_ZERO;
        color = GREEN;

         caption = "G";
    };

    %obj.l3 = new LightObject() {
        enabled = true;
        shaderId = %obj.shader;
        type = LIGHT_POINT;
        position = "2 1 -2";
        target = VEC3_ZERO;
        color = BLUE;

         caption = "B";
    };

    // check lights loaded:
    for (%i = 0; %i < MAX_LIGHTS; %i++)
    {
        %light = %obj.l[%i];
        echo("LIGHT #" @ %i SPC (isObject(%light) ? "OK" : "FAILED"));
    }

    //----- gui
    %obj.gui = new Gui() {
        class ="LightGui";
    };

    return %obj;
}
//----------------------------------------------------------------------
function Lights::onAdd(%this) {
    SetTargetFPS(60); //0 for benchmark
    return true;
}
//----------------------------------------------------------------------
function Lights::OnRemove(%this) {
    SetTargetFPS(60);

    %this.gui.delete();
    %this.camera.delete();
    UnloadShader(%this.shader);
    for (%i = 0; %i < MAX_LIGHTS; %i++)
    {
        %light = %this.l[%i];
        if (isObject(%light)) %light.delete();
    }
}
//----------------------------------------------------------------------
function LightGui::LightBox(%this, %light) {
    if (%this.CheckBox( %light.caption,  %light.enabled)) {
        %light.enabled = !  %light.enabled;
        %light.update();
    }
}
//----------------------------------------------------------------------
function Lights::Render(%this) {
    ClearBackground("10 10 40 255");
    %cam = %this.camera;
    %shader =  %this.shader;
    // Update the shader with the mCamera view vector (points towards { 0.0f, 0.0f, 0.0f })
    %camPos = %this.camera.position;
    %locIndex = %this.viewPosLoc;
    SetShaderValue(%shader, %locIndex, %camPos, SHADER_UNIFORM_VEC3);

    %cam.update(CAMERA_ORBITAL); // UpdateCamera(&mCamera, CAMERA_ORBITAL);
    BeginMode3D(%cam);
    BeginShaderMode( %shader );
    DrawPlane(VEC3_ZERO, "10.0 10.0", WHITE);
    // DrawCube(VEC3_ZERO, 2.0, 4.0, 2.0, WHITE);
    DrawSphere("0 1.0 0", 1.0, WHITE);
    EndShaderMode();
    // Draw spheres to show where the lights are
    for (%i = 0; %i < MAX_LIGHTS; %i++)
    {
        %light = %this.l[%i];
        if (!isObject(%light)) continue;
        // %light.update();
        if (%light.enabled) DrawSphereEx(%light.position, 0.2, 8, 8, %light.color);
        else DrawSphereWires( %light.position, 0.2, 8, 8, ColorAlpha( %light.color, 0.3));
    }
    DrawGrid(10, 1.0);
    EndMode3D();

    %gui = %this.gui;
    %gui.Begin(10,10);
    %gui.Write("Lights and Gui Demo GLSL" SPC GLSL_VERSION, 20, WHITE);
    %gui.Separator(80);
    %gui.Write("LIGHTS:", 12, WHITE);

    %gui.LightBox(%this.l0);
    %gui.SameLine();
    %gui.LightBox(%this.l1);

    %gui.LightBox(%this.l2);
    %gui.SameLine();
    %gui.LightBox(%this.l3);

    %gui.Separator(80);

   //with variable ...but i like the other way more
   // if ( %gui.checkBoxVar("Blue", %this.l3.getId() @ ".enabled") ) %this.l3.update();

}
//----------------------------------------------------------------------
// defines on bottom .. they get removed on load so the parse error line
// numbers are still valid.
//----------------------------------------------------------------------
#define GLSL_VERSION 100
#define VEC3_ZERO "0 0 0"

#define MAX_LIGHTS 4
#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1
//----------------------------------------------------------------------

