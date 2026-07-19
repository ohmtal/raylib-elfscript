/*
 * RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
 *  BeginTextureMode(target);
 *  EndTextureMode();
 *   DrawTextureRec(target.texture, (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }, (Vector2){ 0, 0 }, WHITE);
*/
#define _BATCH_COUNT_ 1000
#define _RECT_SIZE_ 50
#define _UPDATE_INTERVAL_ 3

function createRenderMap() {
    %obj = new ScriptObject() {
        class = "RenderMap";
    };

    return %obj;
}
//----------------------------------------------------------------------
function RenderMap::onAdd(%this) {


    $updateTimer = _UPDATE_INTERVAL_;

    $target = new RenderTextureObject() { width = GetScreenWidth(); height = GetScreenHeight(); };

    echo(" ---------- init done");
    return true;
}
//----------------------------------------------------------------------
function RenderMap::OnRemove(%this) {
    $target.delete();
    $target = 0;
}
//----------------------------------------------------------------------
function RenderMap::Render(%this) {

    $updateTimer += GetFrameTime();

    if ( $updateTimer > _UPDATE_INTERVAL_ ) {
        %h = GetScreenHeight() - _RECT_SIZE_;
        %w = GetScreenWidth() - _RECT_SIZE_;
        %size = _RECT_SIZE_ SPC _RECT_SIZE_;
        $updateTimer -= _UPDATE_INTERVAL_;

        $target.BeginTextureMode();
        ClearBackground(WHITE);

        for (%i = 0; %i < _BATCH_COUNT_; %i++) {

            %color = GetRandomValues(3,0,255) SPC 255;
            %pos = GetRandomValue(0, %w) SPC GetRandomValue(0, %h);
            DrawRectangleV(%pos, %size, %color);
        }
        $target.EndTextureMode();
    }
    ClearBackground(WHITE);
    DrawTextureRec($target.texture
    , "0 0" SPC $target.width SPC -$target.height
    , "0 0"
    , WHITE );

    DrawText("RenderBatch example. Rects: _BATCH_COUNT_ Timer is:" SPC strFormat("%d",$updateTimer) SPC "/" SPC _UPDATE_INTERVAL_, 5, 5, 20, YELLOW, true, BLACK);

    if (IsWindowResized()) {
       $target.resize( GetScreenWidth(),GetScreenHeight());
    }

}

