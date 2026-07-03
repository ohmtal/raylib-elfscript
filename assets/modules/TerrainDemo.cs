function createTerrainDemo() {
    %obj = new ScriptObject() {
        class = "TerrainDemo";
    };

    %this = %obj; //map
    // ---- camera
    %this.camera = new Camera3DObject(CAMERA) {
        position = "-36.0 41.0 -57.0";    // Camera position
        target = "0.0 0.5 0.0";      // Camera looking at point
        up = "0.0 1.0 0.0";          // Camera up vector (rotation towards target)
        fovy = 45.0;                  // Camera field-of-view Y
        projection = CAMERA_PERSPECTIVE;  // Camera projection type

        moveSpeed = 100.0;
        panSpeed  = 10.0;
    };

    %this.terrain = new TerrainObject(TERRAIN) {
        HeightMapFilename = "assets/terrain/ohmtal_HM.png";
        Size = "2048.0 128.0 2048.0";
        // Size = "256.0 64.0 256.0";
        Position = "-1024 -0 -1024";
    };

    // level ... terrain should be also inside ... but for now this also rocks
    %this.levelObjects = new SimSet();


    // TreeBuilder as global reusable model:
    if ( $TreeTrunkModel * 1 == 0)
    {
        $TreeTrunkModel = GenModelCube(0.4, 2.0, 0.4);
        $TreeCrownModel = GenModelSphere(1.2, 16, 16);

        SetModelMapColor($TreeTrunkModel, "100 65 30 255", 0, 0);
        SetModelMapColor($TreeCrownModel, "40 120 40 255", 0, 0);
    }


    return %obj;
}
//----------------------------------------------------------------------
function TerrainDemo::onAdd(%this) {

    SetTargetFPS(60); //FPS TEST only calling module
    return true;
}
//----------------------------------------------------------------------
function TerrainDemo::OnRemove(%this) {
    EnableCursor();
    %this.camera.delete();
    %this.terrain.delete();

    %this.levelObjects.deleteObjects();
    %this.levelObjects.delete();
}
//----------------------------------------------------------------------
function Camera3DObject::updateFly(%this)
{
    %dt = getFrameTime();

        // Turbo-Modus mit Shift-Taste für schnelles Navigieren
        %speed = isKeyDown(KEY_LEFT_SHIFT) ? %this.moveSpeed * 2.0 : %this.moveSpeed;

        // --- Tastatur-Bewegung (Frame-unabhängig via %dt) ---
        if (isKeyDown(KEY_W)) {
            %this.moveForward(%dt * %speed, false);
        }
        if (isKeyDown(KEY_S)) {
            %this.moveForward(-%dt * %speed, false);
        }

        if (isKeyDown(KEY_D)) {
            %this.moveRight(%dt * %speed, false);
        }
        if (isKeyDown(KEY_A)) {
            %this.moveRight(-%dt * %speed, false);
        }

        if (isKeyDown(KEY_E)) {
            %this.moveUp(%dt * %speed);
        }
        if (isKeyDown(KEY_Q)) {
            %this.moveUp(-%dt * %speed);
        }

    if (IsCursorHidden())
    {
        // === SMOOTH MOUSE ROTATION ===
        %mouseDelta = GetMouseDelta();
        %deltaX = %mouseDelta.x;
        %deltaY = %mouseDelta.y;

        %sensitivity = 0.0015;

        %this.targetYaw   = -%deltaX * %this.panSpeed * %sensitivity;
        %this.targetPitch = -%deltaY * %this.panSpeed * %sensitivity;

        %smoothFactor = 15.0 * %dt;
        if (%smoothFactor > 1.0) %smoothFactor = 1.0; // Absicherung

        if (%this.targetYaw != 0 || %this.targetPitch != 0) {

            %currentYaw = %this.targetYaw * %smoothFactor;
            %currentPitch = %this.targetPitch * %smoothFactor;

            %this.yaw(%currentYaw, true);
            %this.pitch(%currentPitch, true, false, false);

            %this.targetYaw   -= %currentYaw;
            %this.targetPitch -= %currentPitch;
        }

//         // --- Maus-Rotation (Smooth ohne %dt) ---
//         %mouseDelta = GetMouseDelta();
//         %deltaX = %mouseDelta.x;
//         %deltaY = %mouseDelta.y;
// echo("MOUSE DELTE:" SPC %mouseDelta SPC "::" SPC %deltaX SPC %deltaY);
//         if (%deltaX != 0 || %deltaY != 0) {
//             %sensitivity = 0.03;
//   /*
//             CameraYaw(camera, -mousePositionDelta.x*CAMERA_MOUSE_MOVE_SENSITIVITY, rotateAroundTarget);
//             CameraPitch(camera, -mousePositionDelta.y*CAMERA_MOUSE_MOVE_SENSITIVITY, lockView, rotateAroundTarget, rotateUp);
//             */
//             %this.yaw(-%deltaX *  %sensitivity, true);
//             %this.pitch(-%deltaY *  %sensitivity, true, false, false);
//             // %this.yaw(-%deltaX * %this.panSpeed * %sensitivity, true);
//             // %this.pitch(-%deltaY * %this.panSpeed * %sensitivity, true, false, false);
//         }
    }
}

//----------------------------------------------------------------------
function TerrainDemo::Render(%this) {

    if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))  DisableCursor();
    else if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) EnableCursor();

    if (!IsCursorHidden() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) %this.onMouseLeftClick();

    ClearBackground("60 60 150");
    %cam = %this.camera;
    %ter = %this.terrain;

    %cam.updateFly();



    // %playerPos = %cam.position;
    // %playerRadius = 0.1;
    // example for push to terrain:
    // %groundHeight = %this.terrain.getHeight(%playerPos);
    // %playerPos.y = %groundHeight + %playerRadius;
    // %player.position = %playerPos;


    BeginMode3D(%this.camera);
      %ter.drawBasic();

      // level models render:
      %l = %this.levelObjects;
      %cnt = %l.getCount();
      for (%i = 0; %i < %cnt; %i++) %l.getObject(%i).draw(  );


      // DrawGrid(20, 1.0);
    EndMode3D();

    DrawText("CAM:" SPC %cam.position,10,10);
}

//----------------------------------------------------------------------
function TerrainDemo::spawnScriptTree(%this, %worldPos)
{

    %trunkHeight = getRandomF(1.0,3.0);
    %trunk = new ModelObject() {
        Position = %worldPos.x SPC (%worldPos.y + (%trunkHeight / 2)) SPC %worldPos.z;
        ModelId = $TreeTrunkModel;
        Scale = getRandomF(0.8,1.2) SPC 1.0 SPC getRandomF(0.8,1.2);
    };

    // %crownY = %worldPos.y + %trunkHeight;
    %relY = %trunkHeight / 2.0 + 0.5; // 0.5 == halve crown height
    %crown = new ModelObject() {
        Position = 0 SPC %relY SPC 0;
        ModelId = $TreeCrownModel;
        Scale = getRandomF(0.8,1.2) SPC 1.0 SPC getRandomF(0.8,1.2);
    };
    %trunk.add( %crown ); //link them together

    // add to levelObjects only trunk since crown is a child!
    %this.levelObjects.add(%trunk);
    // now using recursive %this.levelObjects.add(%crown);

    return %trunk;
}

//----------------------------------------------------------------------
function TerrainDemo::onMouseLeftClick(%this)
{
    %camera = %this.camera;
    %terrain = %this.terrain;
    %model = %this.selectedModel;

    %mousePos = GetMousePosition();
    %ray = %this.camera.getScreenToWorldRay(%mousePos); //<< GetMouseRay

    %collisionStr = %terrain.getRayCollision(%ray);

    if (%collisionStr $= "") {
        return;
    }

    %hitX = getWord(%collisionStr, 0);
    %hitY = getWord(%collisionStr, 1);
    %hitZ = getWord(%collisionStr, 2);

    %normX = getWord(%collisionStr, 3);
    %normY = getWord(%collisionStr, 4);
    %normZ = getWord(%collisionStr, 5);

    // or simply as vector3 string:
    %hitPoint = getWords(%collisionStr, 0,2);
    %hitNormal = getWords(%collisionStr, 3,5);
    warn("HITPOINT" SPC %hitPoint SPC "HITNORMAL" SPC %hitNormal);

    %distance = getWord(%collisionStr, 6);

    %tree = %this.spawnScriptTree(%hitX SPC %hitY SPC %hitZ);

    echo("new Tree:" SPC  %tree SPC "created. Position:" SPC %tree.position);
}


