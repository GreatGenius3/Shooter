//
// Created by snill on 2026-08-30.
//

#include "TheGame.h"
#include "ecs/components/Components.h"
#include "systems/Systems.h"
#include "systems/RenderSystem.h"

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
    newgame->textureFilter = TEXTURE_FILTER_POINT;
    
    return newgame;
}

void DestroyGame(Game *game)
{
    ecs_fini(game->world);
    free(game->title);
    UnloadRenderTexture(game->target);
    free(game);
}

void RunGame(Game *game)
{
    // Starta fönstret via din SDL3-backend
    InitWindow(game->screenWidth, game->screenHeight, game->title);

    game->target = LoadRenderTexture(game->virtualWidth, game->virtualHeight);

    SetTextureFilter(game->target.texture, game->textureFilter);

    SetTargetFPS(game->fps);

    game->world = ecs_init();
    init_components(game->world);
    init_game_systems(game);

    // Skapa en test-entitet med Position, Velocity, SpriteRenderer och Bounds (studsande)
    ecs_entity_t testEntity = ecs_new(game->world);
    
    Position pos = {100.0f, 100.0f};
    Velocity vel = {100.0f, 60.0f}; // pixlar per sekund
    
    SpriteRenderer renderer = {
        .source = {0, 0, 32, 32},
        .scale = 1.0f,
        .rotation = 0.0f,
        .tint = RED
    };
    
    Bounds bounds = {
        .minX = 0.0f,
        .minY = 0.0f,
        .maxX = (float)game->virtualWidth,
        .maxY = (float)game->virtualHeight,
        .bounce = true
    };
    
    ecs_set_ptr(game->world, testEntity, Position, &pos);
    ecs_set_ptr(game->world, testEntity, Velocity, &vel);
    ecs_set_ptr(game->world, testEntity, SpriteRenderer, &renderer);
    ecs_set_ptr(game->world, testEntity, Bounds, &bounds);
    
    // Skapa en spelar-entitet med tangentbordskontroll
    ecs_entity_t playerEntity = ecs_new(game->world);
    
    Position playerPos = {200.0f, 200.0f};
    Velocity playerVel = {0.0f, 0.0f}; // Sätts av InputSystem
    
    SpriteRenderer playerRenderer = {
        .source = {0, 0, 32, 32},
        .scale = 1.0f,
        .rotation = 0.0f,
        .tint = GREEN
    };
    
    PlayerInput playerInput = {
        .speed = 200.0f, // pixlar per sekund
        .upKey = KEY_W,
        .downKey = KEY_S,
        .leftKey = KEY_A,
        .rightKey = KEY_D
    };
    
    Bounds playerBounds = {
        .minX = 0.0f,
        .minY = 0.0f,
        .maxX = (float)game->virtualWidth,
        .maxY = (float)game->virtualHeight,
        .bounce = false // Spelaren studsar inte
    };
    
    ecs_set_ptr(game->world, playerEntity, Position, &playerPos);
    ecs_set_ptr(game->world, playerEntity, Velocity, &playerVel);
    ecs_set_ptr(game->world, playerEntity, SpriteRenderer, &playerRenderer);
    ecs_set_ptr(game->world, playerEntity, PlayerInput, &playerInput);
    ecs_set_ptr(game->world, playerEntity, Bounds, &playerBounds);

    // Huvudloop
    while (!WindowShouldClose())
    {
        DrawGame(game);
    }
}

void DrawGame(Game *game)
{
    float delta_time = GetFrameTime();

    BeginTextureMode(game->target);

    ClearBackground(BLACK);
    ecs_progress(game->world, delta_time);

    EndTextureMode();

    BeginDrawing();

    ClearBackground(BLACK);

    // Rita ut vår virtuella canvas på skärmen och skala upp den till fönstret.
    // OBS: Raylib vänder RenderTexture upp-och-ner i OpenGL (Y-axeln),
    // så vi skickar ett negativt höjdvärde i koll-rektangeln för att vända den rätt!
    DrawTexturePro(
        game->target.texture,
        (Rectangle){ 0.0f, 0.0f, (float)game->target.texture.width, (float)-game->target.texture.height },
        (Rectangle){ 0.0f, 0.0f, (float)game->screenWidth, (float)game->screenHeight },
        (Vector2){ 0.0f, 0.0f },
        0.0f,
        WHITE
    );

    // (Valfritt) H�r kan du rita saker som ALLTID ska vara i f�nsteruppl�sning (t.ex. HD-gr�nssnitt eller FPS)
    DrawFPS(10, 10);

    EndDrawing();
}
