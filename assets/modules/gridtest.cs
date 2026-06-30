//----------------------------------------------------------------------
// GridTest ported from OhmFlux/ElfTest
// (c) 2026 XXTH
//----------------------------------------------------------------------
function creategridtest() {
    %obj = new SimSet() {
        class = "Gridtest";
    };

    return %obj;
}
//----------------------------------------------------------------------
function GridTest::onAdd(%this) {
    SetTargetFPS(60); //FPS TEST only calling module
    %this.Init();
    return true;
}
//----------------------------------------------------------------------
function GridTest::OnRemove(%this) {
    SetTargetFPS(60);
    %this.deleteObjects();
}
//----------------------------------------------------------------------
function GridTest::Render(%this) {
    ClearBackground("10 10 10");

    if (%this.crazy) %this.newTerrain();

    // ---- gui
    %gui = %this.gui;
    %gui.Begin(GetScreenWidth() - 120,10);
    %gui.Write("Grid Demo", 20, WHITE);
    %gui.Separator(80);
    if ( %gui.Button(80, "New Terrain") ) %this.newTerrain();
    %id = %this.getId();
    %gui.CheckBoxVar("Hide Terrain", %id @ ".hideTerrain");
    %gui.CheckBoxVar("Crazy!", %id @ ".crazy");


    if (!%this.hideTerrain) {
        %vert = %this.countX;
        %hor  = %this.countY;

        %idx = 0;
        %weight = 0;
        for (%i = 0; %i < %vert; %i++) {
            // %line = "";
            for (%j=0; %j < %hor; %j++) {
                %weight = %this.grid.getWeightByNodeId( %idx );
                // %this.writeText(65 + 50 * %j,%i*30 + 50,byteToHex(%weight), $align::left ,  %weight SPC "0.5 0.2");

                %rect = 65 + 50 * %j SPC %i*30 + 40 SPC 35 SPC 28;
                %color = %weight  SPC "128 0";
                DrawRectangleRec(%rect, %color);
                %idx++;
            }
        }
    }


    // path
    %lastPoint = "";
    %path = %this.path;
    if ( isObject(%path) ) {
        %cnt = %path.getDynamicFieldCount();
        for (%i = 0; %i < %cnt; %i++) {
            %pos = %path.getFieldValue("node" @ %i);
            %realPos = %pos.x * 50  + 85 SPC  %pos.y * 30 + 55;
            if ( %lastPoint ) DrawLineV(%lastPoint, %realPos  );
            %lastPoint = %realPos;
        }
    }


}

// -----------------------------------------------------------------------------
function GridTest::Init(%this) {
    // Setup Grid
    %this.grid = new Grid();
    %x = 0; %y = 0;
    %w = 16; %h = 16;
    %this.grid.start = %x SPC %y;
    %this.grid.end  = %x + %w -1 SPC %y + %w - 1;
    %area  = %this.grid.start SPC %w SPC %h;
    %this.grid.squareSize = 1.0;
    echo("INIT:" SPC  %this.grid.init(%area, %this.grid.squareSize));
    %this.grid.getinfo();
    %this.add(%this.grid);


    %this.gui = new Gui() {
    };
    %this.add(%this.gui);


    %this.crazy  = false;
    %this.hideTerrain = false;
    %this.countX = %this.grid.getNodeCountY();
    %this.countY = %this.grid.getNodeCountX();
    %this.newTerrain();
}
// -----------------------------------------------------------------------------
function GridTest::newTerrain(%this) {
    %this.grid.addRandomMud();
    if ( isObject(%this.path) ) %this.path.delete();
    %this.path = %this.grid.findPath( %this.grid.start, %this.grid.end, false);
    if ( isObject(%this.path) ) %this.add( %this.path );
    // echo("PATH object is:" SPC %this.path);
}
// -----------------------------------------------------------------------------
function Grid::addRandomMud(%this) {
    %cnt = %this.getNodeCount();
    //reset grid
    for( %i = 0; %i < %cnt; %i++ ) {
        %this.setWeightByNodeId(%i, 0);
    }  
    
    for( %i = 0; %i < %cnt / 1.5; %i++ ) {
        %n = getRandom(%cnt - 1);
        // %w = getRandom(50,250);
        // let think about 7 ground textures:
        // max is 224, 256 would be invalid btw
        // 255 would block completly 
        %w = getRandom(6) * 32 + 32;
        %this.setWeightByNodeId(%n, %w);
    }
   
}
// -----------------------------------------------------------------------------
// function GridTest::onInputEvent( %this, %deviceString, %actionString, %mouseX, %mouseY, %keyValue ) {
//     if (%keyValue == 0  ) { //mouse up on left button
//         if (%actionString $= "R") {
//             exec("./gridtest.cs");
//         }
//         else
//         if (%actionString $= "button1" && pointInRect( %this.LabelNew.ButtonRect, %mouseX SPC %mouseY)) {
//             %this.newTerrain();
//         }
//     }
//
//
// }
// -----------------------------------------------------------------------------
// function GridTest::onRender(%this,%dt) {
//
//
//   %this.writeText(5,25, "Grid + Pathfinding Demo ",  $FontAlign_left, "0.5 0.2 0.5" );
//   %this.writeText(900, 150, getFPS() @ "fps" );
//    // %this.Line("5 35", "595 35", "0 1 0");
//
//
//     if (!%this.hideTerrain) {
//         %vert = %this.countX;
//         %hor  = %this.countY;
//
//         %idx = 0;
//         %weight = 0;
//         for (%i = 0; %i < %vert; %i++) {
//             // %line = "";
//             for (%j=0; %j < %hor; %j++) {
//                 %weight = %this.grid.getWeightByNodeId( %idx );
//                 // %this.writeText(65 + 50 * %j,%i*30 + 50,byteToHex(%weight), $align::left ,  %weight SPC "0.5 0.2");
//
//                 %rect = 65 + 50 * %j SPC %i*30 + 40 SPC 35 SPC 28;
//                 %color = (%weight / 255.0) SPC "0.5 0";
//                 %this.rect(%rect, %color, true);
//
//                 %idx++;
//             }
//         }
//     }
//
//     // path
//     %lastPoint = "";
//     if ( isObject(%this.path) ) {
//         %cnt = %this.path.getDynamicFieldCount();
//         for (%i = 0; %i < %cnt; %i++) {
//             %pos = %this.path.getFieldValue("node" @ %i);
//             // %realPos = getWord(%pos,0) * 50  + 85 SPC  getWord(%pos,1) * 30 + 55;
//             %realPos = %pos.x * 50  + 85 SPC  %pos.y * 30 + 55;
//             if ( %lastPoint ) %this.Line(%lastPoint, %realPos  );
//             %lastPoint = %realPos;
//
//             // if ( %pos !$= "" ) {
//             //     %this.writeText(getWord(%pos,0) * 50  + 52, getWord(%pos,1) * 30 + 50,"x", $align::left, "0 0 255" );
//             // }
//         }
//     }
//
//     %this.Rect( %this.LabelNew.ButtonRect,%this.labelNew.color , false);
//     // %this.ElipseRect( %this.LabelNew.ButtonRect,%this.labelNew.color );
// }
// -----------------------------------------------------------------------------
// function GridTest::onUpdate(%this, %dt) {
//     if (%this.crazy) %this.newTerrain();
//
//     // not really good performance!! >> i need a mouse move event
//     // or better an object which track it on c++ like MouseRect ...
//     if (pointInRect( %this.LabelNew.ButtonRect,getMousePos())) {
//         %this.labelNew.color = "0.5 1 0.5";
//     } else {
//         %this.labelNew.color = "1 1 1";
//     }
// }
// -----------------------------------------------------------------------------
// function GridTest::onRemove(%this) {
//     %this.deleteObjects();
// }

// --------------- TEST update  all 32 ms --------
function GridTest::start(%this) {
    if (%this.crazy) return;
    %this.crazy = true;
    // %this.crazyLoop();
}
function GridTest::stop(%this) {
    %this.crazy = false;
}



