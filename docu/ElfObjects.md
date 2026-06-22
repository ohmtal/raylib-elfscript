# ElfObjects

In the Interface i usually use the Resource Storage System to seamless call the RayLib function as it is
called in the C-Source. But sometimes it's not possible to do this and I added some Objects and so some function calls
are different: 

## RenderTexture2D / RenderTexture => RenderTextureObject

**C-Code:**
``` 
    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);
    ...
    BeginTextureMode(target);
    ...
    EndTextureMode();
    ...
     DrawTextureRec(target.texture
        , (Rectangle){ 0, 0, (float)target.texture.width, (float)-target.texture.height }
        , (Vector2){ 0, 0 }
        , WHITE);
    ...
    UnloadRenderTexture(target);
```
**ElfScript Code:**
```
    $target = new RenderTextureObject() { width = GetScreenWidth(); height = GetScreenHeight(); };
    $target.BeginTextureMode(); 
    ...
    $target.EndTextureMode();
    ...
     DrawTextureRec($target.texture
        , "0 0" SPC $target.width SPC -$target.height
        , "0 0"
        , WHITE ); 
        
    // extra feature:
    if (IsWindowResized()) {
       $target.resize( GetScreenWidth(),GetScreenHeight());
    }
    ... 
     $target.delete(); 
```

**Other methods:**
    
- bool resize (S32 width,S32 height, bool copyImage = true); // resize (recreate) a Render Texture
    

## Camera2D

FIXME docu

## Camera3D

FIXME docu
