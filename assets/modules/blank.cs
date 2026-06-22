function createBlank() {
    %obj = new ScriptObject() {
        class = "Blank";
    };

    return %obj;
}
//----------------------------------------------------------------------
function Blank::onAdd(%this) {
    SetTargetFPS(0); //FPS TEST only calling module
    return true;
}
//----------------------------------------------------------------------
function Blank::OnRemove(%this) {

}
//----------------------------------------------------------------------
function Blank::Render(%this) {
    ClearBackground(WHITE);
}

