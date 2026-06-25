// -----------------------------------------------------------------------------
// batch render version
// so much time to implement it and get it work and only 5-10 (130-140) fps more.
// rects are much faster than circle and i do not see a big difference: 200fps
// -----------------------------------------------------------------------------

// orig 420
#define STAR_COUNT 420

function createshapes_starfield_nativ() {
    %obj = new StarField() { //NOTE BatchRender!!
        class = "shapes_starfield_nativ";
        count = STAR_COUNT;
        mode = 0;
        speed = 1;
        color = "200 255 200 255";

        modeName = "Lines";
    };

    return %obj;
}
// -----------------------------------------------------------------------------
function shapes_starfield_nativ::onRemove(%this) {
    SetTargetFPS(60);
}

// -----------------------------------------------------------------------------
function shapes_starfield_nativ::OnAdd(%this) {
    SetTargetFPS(0);
    return true;
}
// -----------------------------------------------------------------------------
function shapes_starfield_nativ::Render(%this) {

    %mouseMove = GetMouseWheelMove();

    if (%mouseMove != 0) {
        %this.speed += %mouseMove / 10.0;
        %this.speed= mClampF(%this.speed, 0.05, 5.0);

    }
    // Toggle lines / points with space bar
    if (IsKeyPressed(KEY_SPACE)) {
        %this.mode = (%this.mode + 1) % 3;
        switch (%this.mode) {
            case 0: %this.modeName = "Lines";
            case 1: %this.modeName = "Rectangles";
            case 2: %this.modeName = "Circle";
        }
        echo("SPACE pressed new mode is: " SPC %this.modeName );
    }
    if (IsKeyPressed(KEY_U)) {
        SetTargetFPS(0);
    }
    if (IsKeyPressed(KEY_R)) {
        SetTargetFPS(60);
    }


    %this.loop();  // run the object Loop
    DrawFPS(10, 10);


    DrawText("[MOUSE WHEEL] Current Speed:" SPC  strFormat("%.2f",%this.speed) , 10, 40, 20, RAYWHITE);
    DrawText("[SPACE] Current draw mode:"  SPC  %this.modeName , 10, 70, 20, RAYWHITE);

}
