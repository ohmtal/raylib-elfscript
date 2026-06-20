// -----------------------------------------------------------------------------
// attempt to optimze speed with global variables and but seams to be the same..
// the loop over starcount is not really the best idea when using interpreted
// script. maybe with a jit compiler but we dont have this.
// This "optimized" version is faster than v1 - not sure which change did it ;)
// -----------------------------------------------------------------------------

function createshapes_starfield_effect() {
    %obj = new ScriptObject() {
        class = "shapes_starfield_effect";
        // TypeF32 speed = 10.0/9.0;
        TypeColor bgColor = 0;

        TypeBool drawLines = true;
        TypeS32 starCount = 175; // orig 420
    };
    return %obj;
}
// -----------------------------------------------------------------------------
function shapes_starfield_effect::onRemove(%this) {
 // unload the variables
  deleteVariables("$starPoints*");
  deleteVariables("$starPointsScreenPos*");
  SetTargetFPS(60);
}
// -----------------------------------------------------------------------------
function shapes_starfield_effect::Init(%this) {
    %this.bgColor = ColorLerp($DARKBLUE, $BLACK, 0.69);

    $screenHeight = GetScreenHeight();
    $screenWidth = GetScreenWidth();

    // save as min/max
    $minH = -$screenWidth / 2;
    $maxH = $screenWidth / 2;
    $minW = -$screenHeight / 2;
    $maxW = $screenHeight / 2;

    $hW = $screenWidth  * 0.5;
    $hH = $screenHeight  * 0.5;

    for ( %i = 0; %i < %this.starCount; %i++)
    {
        $starPoints_X[%i] = GetRandomValue($minH ,  $maxH);
        $starPoints_Y[%i] = GetRandomValue($minW ,   $maxW);
        $starPoints_Z[%i] = 1.0;

        echo("STAR #" @ %i SPC $starPoints_X[%i] SPC $starPoints_Y[%i] SPC $starPoints_Z[%i]
        SPC "rand" SPC GetRandomValue($minH ,  $maxH));
    }

    $speed = 10.0/9.0;

    return true;
}

function shapes_starfield_effect::Update(%this) {}
// -----------------------------------------------------------------------------
function shapes_starfield_effect::UpdatePoint(%this, %i , %dt) {
    // Update star's timer
    $starPoints_Z[%i] -= %dt * $speed;

    // Calculate the screen position
    $starPointsScreenPos_X[%i] = $hW + $starPoints_X[%i] / $starPoints_Z[%i];
    $starPointsScreenPos_Y[%i] = $hH + $starPoints_Y[%i]/$starPoints_Z[%i];

    // If the star is too old, or offscreen, it dies and we make a new random one
    if (($starPoints_Z[%i] < 0.0) || ($starPointsScreenPos_X[%i] < 0) || ($starPointsScreenPos_Y[%i] < 0.0) ||
        ($starPointsScreenPos_X[%i] > $screenWidth) || ($starPointsScreenPos_Y[%i] > $screenHeight))
    {
        $starPoints_X[%i] = GetRandomValue($minH, $maxH);
        $starPoints_Y[%i] = GetRandomValue($minW, $maxW);
        $starPoints_Z[%i] = 1.0;
    }
}
// -----------------------------------------------------------------------------
function shapes_starfield_effect::Render(%this) {

    %mouseMove = GetMouseWheelMove();

    if (%mouseMove != 0) $speed += 2.0 * %mouseMove / 9.0;
    if ($speed < 0.0) $speed = 0.1;
    else if ($speed > 2.0) $speed = 2.0;

    // Toggle lines / points with space bar
    if (IsKeyPressed($KEY_SPACE)) {
        %this.drawLines = !%this.drawLines;
        echo("SPACE pressed new drawlines is: " SPC %this.drawLines );
    }
    if (IsKeyPressed($KEY_U)) {
        SetTargetFPS(0);
    }
    if (IsKeyPressed($KEY_R)) {
        SetTargetFPS(60);
    }


     %dt = GetFrameTime();

     // does also not speed up ..
     // $randomValues = GetRandomValues(%this.starCount * 2,$minH, $maxH );


    ClearBackground(%this.bgColor);
    for ( %i = 0; %i < %this.starCount; %i++)
    {
        %this.updatePoint(%i, %dt);
        if (%this.drawLines)
        {
            // Get the time a little while ago for this star, but clamp it
            %t = mClamp($starPoints_Z[%i] + 1.0 / 32.0 , 0.0 , 1.0 );
            // If it's different enough from the current time, we proceed
            if ((%t - $starPoints_Z[%i]) > 1e-3)
            {
                // Calculate the screen position of the old point
                %startPos =
                    $hW + $starPoints_X[%i] / %t SPC
                    $hH + $starPoints_Y[%i] / %t;


                // Draw a line connecting the old point to the current point
                DrawLineV(%startPos, $starPointsScreenPos_X[%i] SPC $starPointsScreenPos_Y[%i], $RAYWHITE);
            }
        }
        else
        {
            // Make the %this.radius grow as the star ages
            // Draw the circle
            %radius = mLerp($starPoints_Z[%i], 1.0, 5.0);

            DrawCircleV($starPointsScreenPos_X[%i] SPC $starPointsScreenPos_Y[%i], %radius, $RAYWHITE);
        }
    }

    DrawText("[MOUSE WHEEL] Current Speed:" SPC  9.0 * $speed / 2.0 , 10, 40, 20, $RAYWHITE);
    DrawText("[SPACE] Current draw mode:" SPC  ( %this.drawLines ? "Lines" : "Circles" ) , 10, 70, 20, $RAYWHITE);

    DrawFPS(10, 10);
}
