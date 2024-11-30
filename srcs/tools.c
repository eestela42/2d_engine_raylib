#include "main.h"


long long currentTimeMillis() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (long long)(time.tv_sec) * 1000 + (time.tv_usec) / 1000;
}

Texture2D ResizeTexture(Texture2D texture, int newWidth, int newHeight) {
    // Create a render texture with the new size
    RenderTexture2D target = LoadRenderTexture(newWidth, newHeight);

    // Render the original texture to the render texture
    BeginTextureMode(target);
    ClearBackground(BLANK); // Clear the background to avoid artifacts
    DrawTexturePro(
        texture,                               // Source texture
        (Rectangle){ 0, 0, (float)texture.width, (float)-texture.height }, // Source rectangle (flip vertically)
        (Rectangle){ 0, 0, (float)newWidth, (float)newHeight },            // Destination rectangle
        (Vector2){ 0, 0 },                    // Origin
        0.0f,                                 // Rotation
        WHITE                                 // Tint
    );
    EndTextureMode();

    // The texture from the render target
    Texture2D resized = target.texture;

    // WARNING: Do not unload the render texture yet. It manages the resized texture's memory.
    return resized;
}