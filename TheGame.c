//
// Created by snill on 2026-08-30.
//

#include "TheGame.h"

Game *CreateGame(const char *title, int sWidth, int sHeight, int vWidth, int vHeight, int fps)
{
    Game *newgame = malloc(sizeof(Game));
    if (newgame == NULL)
        return NULL;
    size_t len = strlen(title);
    newgame->title = malloc(len + 1);
    strcpy(newgame->title, title);
    newgame->screenWidth = sWidth;
    newgame->screenHeight = sHeight;
    newgame->virtualWidth = vWidth;
    newgame->virtualHeight = vHeight;
    newgame->fps = fps;
    newgame->target = LoadRenderTexture(vWidth, vHeight);
    newgame->textureFilter = TEXTURE_FILTER_POINT;
    return newgame;
}

void DestroyGame(Game *game)
{
    free(game->title);
    UnloadRenderTexture(game->target);
    free(game);
}

void RunGame(Game *game)
{
    // Starta fönstret via din SDL3-backend
    InitWindow(game->screenWidth, game->screenHeight, game->title);

    SetTextureFilter(game->target.texture, game->textureFilter);

    SetTargetFPS(game->fps);

    // Huvudloop
    while (!WindowShouldClose())
    {
        UpdateGame(game);
        DrawGame(game);
    }
}

void UpdateGame(Game *game)
{

}

void DrawGame(Game *game)
{
    BeginTextureMode(game->target);

    ClearBackground(BLACK);

    EndTextureMode();

    BeginDrawing();

    ClearBackground(BLACK);

    // Rita ut vår virtuella canvas på skärmen och skala upp den till fönstret.
    // OBS: Raylib vänder RenderTexture upp-och-ner i OpenGL (Y-axeln),
    // så vi skickar ett negativt höjdvärde i käll-rektangeln för att vända den rätt!
    DrawTexturePro(
        game->target.texture,
        (Rectangle){ 0.0f, 0.0f, (float)game->target.texture.width, (float)-game->target.texture.height },
        (Rectangle){ 0.0f, 0.0f, (float)game->screenWidth, (float)game->screenHeight },
        (Vector2){ 0.0f, 0.0f },
        0.0f,
        WHITE
    );

    // (Valfritt) Här kan du rita saker som ALLTID ska vara i fönsterupplösning (t.ex. HD-gränssnitt eller FPS)
    DrawFPS(10, 10);

    EndDrawing();
}