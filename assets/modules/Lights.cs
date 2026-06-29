// Lights Demo

#define GLSL_VERSION 330
#define VEC3_ZERO "0 0 0"

#define MAX_LIGHTS 4
#define LIGHT_DIRECTIONAL 0
#define LIGHT_POINT 1

//------------------------------------------------------------------------------
function createLights() {
    %obj = new ScriptObject() {
        class = "Lights";
    };

    // ---- camera
    %obj.camera = new Camera3DObject() {
        position = "2.0 4.0 6.0 ";    // Camera position
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
    // Get some required shader locations
    //     mShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(mShader, "viewPos");
    SetShaderLocationByUniformName(%obj.shader, SHADER_LOC_VECTOR_VIEW, "viewPos");

    // Ambient light level (some basic lighting)
    %ambientLoc = GetShaderLocation(%obj.shader, "ambient");
    %ambient = "0.1 0.1 0.1 1.0";
    SetShaderValue(%obj.shader, %ambientLoc, %ambient, SHADER_UNIFORM_VEC4);
    // echo("*Ambient Location = " SPC %ambientLoc);

    //
    //     // Create lights
    //
    //     mLights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, -2 }, Vector3Zero(), YELLOW, mShader);
    //     mLights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, 2 }, Vector3Zero(), RED, mShader);
    //     mLights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, 2 }, Vector3Zero(), GREEN, mShader);
    //     mLights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, -2 }, Vector3Zero(), BLUE, mShader);
    //
    //     mLights[0].color=ORANGE;
    //
    // addField("shaderId", TypeS32, Offset(mShaderId, LightObject), "Id of the shader object");
    // addField("type", TypeS32, Offset(mLight.type, LightObject), "Type of Light:LIGHT_DIRECTIONAL=0 LIGHT_POINT=1");
    // addField("enabled", TypeBool, Offset(mLight.enabled, LightObject), "is enabled");
    // addField("position", TypeVector3, Offset(mLight.position, LightObject), "position of the light");
    // addField("target", TypeVector3, Offset(mLight.target, LightObject), "target of the light");
    // addField("color", TypeColor,  Offset(mLight.color, LightObject), "color of the light");
    // addField("attenuation", TypeF32,  Offset(mLight.attenuation, LightObject), "attenuation of the light");
    %obj.l0 = new LightObject() {
        enabled = true;
        shaderId = %obj.shader;
        type = LIGHT_POINT;
        position = "-2 1 -2";
        target = VEC3_ZERO;
        color = ORANGE;
    };
    %obj.l1 = new LightObject() {
        enabled = true;
        shaderId = %obj.shader;
        type = LIGHT_POINT;
        position = "2 1 2";
        target = VEC3_ZERO;
        color = RED;
    };

    %obj.l2 = new LightObject() {
        enabled = true;
        shaderId = %obj.shader;
        type = LIGHT_POINT;
        position = "-2 1 2";
        target = VEC3_ZERO;
        color = GREEN;
    };

    %obj.l3 = new LightObject() {
        enabled = true;
        shaderId = %obj.shader;
        type = LIGHT_POINT;
        position = "2 1 -2";
        target = VEC3_ZERO;
        color = BLUE;
    };

    // check lights!
    for (%i = 0; %i < MAX_LIGHTS; %i++)
    {
        %light = %obj.l[%i];
        echo("LIGHT #" @ %i SPC (isObject(%light) ? "OK" : "FAILED"));
    }


    return %obj;
}
//----------------------------------------------------------------------
function Lights::onAdd(%this) {
    SetTargetFPS(60);
    return true;
}
//----------------------------------------------------------------------
function Lights::OnRemove(%this) {
    %this.camera.delete();
    UnloadShader(%this.shader);
    for (%i = 0; %i < MAX_LIGHTS; %i++)
    {
        %light = %this.l[%i];
        if (isObject(%light)) %light.delete();
    }
}
//----------------------------------------------------------------------
function Lights::Render(%this) {
    ClearBackground(BLACK);
    %cam = %this.camera;
    %shader =  %this.shader;
    // Update the shader with the mCamera view vector (points towards { 0.0f, 0.0f, 0.0f })
    %camPos = %this.camera.position; //  F32 mCameraPos[3] = { mCamera.position.x, mCamera.position.y, mCamera.position.z };
//     SetShaderValue(mShader, mShader.locs[SHADER_LOC_VECTOR_VIEW], mCameraPos, SHADER_UNIFORM_VEC3);
    //FIXME does not change i guess ... so it's bad to fetch it every time on render
    %locIndex = GetShaderLocsLocation( %shader, SHADER_LOC_VECTOR_VIEW);
    // echo("locIndex = " SPC %locIndex SPC SHADER_LOC_VECTOR_VIEW);
    // echo("campos:" SPC %camPos);
    SetShaderValue(%shader, %locIndex, %camPos, SHADER_UNIFORM_VEC3);

    // Check key inputs to enable/disable lights
    // if (IsKeyPressed(KEY_Y)) { mLights[0].enabled = !mLights[0].enabled; }
    // if (IsKeyPressed(KEY_R)) { mLights[1].enabled = !mLights[1].enabled; }
    // if (IsKeyPressed(KEY_G)) { mLights[2].enabled = !mLights[2].enabled; }
    // if (IsKeyPressed(KEY_B)) { mLights[3].enabled = !mLights[3].enabled; }

    // Update light values (actually, only enable/disable them)
    // for (%i = 0; %i < MAX_LIGHTS; %i++) %this.l[i].update(); //UpdateLightValues(%this.shader, %this.l[i]);
    // for (%i = 0; %i < MAX_LIGHTS; %i++)
    // {
    //     %light = %this.l[%i];
    //     if (!isObject(%light)) continue;
    //     %light.update();
    // }

    %cam.update(CAMERA_ORBITAL); // UpdateCamera(&mCamera, CAMERA_ORBITAL);
    BeginMode3D(%cam);
    BeginShaderMode( %shader );
    DrawPlane(VEC3_ZERO, "10.0 10.0", WHITE);
    DrawCube(VEC3_ZERO, 2.0, 4.0, 2.0, WHITE);
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
}
//----------------------------------------------------------------------
//----------------------------------------------------------------------

/*
namespace RayTal::Demo {

    class Lights: public Core {
        Camera mCamera = { {0} };
        Shader mShader;
        Light mLights[MAX_LIGHTS] = { {0} };

    public:
        bool isEnabled = false;
        //----------------------------------------------------------------------
        bool Init() override {
            //-------
            // add basic lighting demo .....
            // Define the mCamera to look into our 3d world

            mCamera.position = (Vector3){ 2.0f, 4.0f, 6.0f };    // Camera position
            mCamera.target = (Vector3){ 0.0f, 0.5f, 0.0f };      // Camera looking at point
            mCamera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
            mCamera.fovy = 45.0f;                                // Camera field-of-view Y
            mCamera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

            // Load basic lighting shader
            mShader = LoadShader(TextFormat("%s/assets/shaders/glsl%i/lighting.vs", GetApplicationDirectory(),  GLSL_VERSION),
                                 TextFormat("%s/assets/shaders/glsl%i/lighting.fs", GetApplicationDirectory(), GLSL_VERSION));
            // Get some required shader locations
            mShader.locs[SHADER_LOC_VECTOR_VIEW] = GetShaderLocation(mShader, "viewPos");
            // NOTE: "matModel" location name is automatically assigned on shader loading,
            // no need to get the location again if using that uniform name
            //shader.locs[SHADER_LOC_MATRIX_MODEL] = GetShaderLocation(shader, "matModel");

            // Ambient light level (some basic lighting)
            int ambientLoc = GetShaderLocation(mShader, "ambient");
            float ambient[4] = { 0.1f, 0.1f, 0.1f, 1.0f };
            SetShaderValue(mShader, ambientLoc, ambient, SHADER_UNIFORM_VEC4);

            // Create lights

            mLights[0] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, -2 }, Vector3Zero(), YELLOW, mShader);
            mLights[1] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, 2 }, Vector3Zero(), RED, mShader);
            mLights[2] = CreateLight(LIGHT_POINT, (Vector3){ -2, 1, 2 }, Vector3Zero(), GREEN, mShader);
            mLights[3] = CreateLight(LIGHT_POINT, (Vector3){ 2, 1, -2 }, Vector3Zero(), BLUE, mShader);

            mLights[0].color=ORANGE;

            isEnabled = true;
            return true;
        }
        //----------------------------------------------------------------------
        void ShutDown() override {
            UnloadShader(mShader);

        }


        //----------------------------------------------------------------------
        void Update(F32 dt) override {
            if (!isEnabled) return;
            // must be in Render :/ UpdateCamera(&mCamera, CAMERA_ORBITAL);

            // Update the shader with the mCamera view vector (points towards { 0.0f, 0.0f, 0.0f })
            F32 mCameraPos[3] = { mCamera.position.x, mCamera.position.y, mCamera.position.z };
            SetShaderValue(mShader, mShader.locs[SHADER_LOC_VECTOR_VIEW], mCameraPos, SHADER_UNIFORM_VEC3);

            // Check key inputs to enable/disable lights
            if (IsKeyPressed(KEY_Y)) { mLights[0].enabled = !mLights[0].enabled; }
            if (IsKeyPressed(KEY_R)) { mLights[1].enabled = !mLights[1].enabled; }
            if (IsKeyPressed(KEY_G)) { mLights[2].enabled = !mLights[2].enabled; }
            if (IsKeyPressed(KEY_B)) { mLights[3].enabled = !mLights[3].enabled; }

            // Update light values (actually, only enable/disable them)
            for (int i = 0; i < MAX_LIGHTS; i++) UpdateLightValues(mShader, mLights[i]);


        }
        //----------------------------------------------------------------------
        void Render3D()  {
            if (!isEnabled) return;

            UpdateCamera(&mCamera, CAMERA_ORBITAL);

            BeginMode3D(mCamera);
            BeginShaderMode(mShader);
            DrawPlane(Vector3Zero(), (Vector2) { 10.0, 10.0 }, WHITE);
            DrawCube(Vector3Zero(), 2.0, 4.0, 2.0, WHITE);
            EndShaderMode();
            // Draw spheres to show where the lights are
            for (int i = 0; i < MAX_LIGHTS; i++)
            {
                if (mLights[i].enabled) DrawSphereEx(mLights[i].position, 0.2f, 8, 8, mLights[i].color);
                else DrawSphereWires(mLights[i].position, 0.2f, 8, 8, ColorAlpha(mLights[i].color, 0.3f));
            }
            DrawGrid(10, 1.0f);
            EndMode3D();
        }


        void RenderGui(Gui& gui) {
            if (!isEnabled) return;
            gui.Separator(100.f);
            gui.Write("LIGHTS:", 12, WHITE);

            gui.CheckBox( "R", &mLights[1].enabled);
            gui.SameLine();
            gui.CheckBox( "G", &mLights[2].enabled);

            gui.CheckBox( "B", &mLights[3].enabled);
            gui.SameLine();
            gui.CheckBox( "Y", &mLights[0].enabled);

        }

    }; //class...
}
*/
