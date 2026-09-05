//
// Created by snill on 2026-08-30.
//

#ifndef SHOOTER_THEGAME_H
#define SHOOTER_THEGAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
// #include "SDL3/SDL.h"
#include "raylib.h"
// #include "SDL3/SDL_mixer.h"
#include "flecs.h"

typedef struct Game
{
    char *title;
    int screenWidth;
    int screenHeight;
    int virtualWidth;
    int virtualHeight;
    int fps;
    RenderTexture2D target;
    int textureFilter;
    ecs_world_t *world;

    Font nesFont;
} Game;

Game *CreateGame(const char *title, int sWidth, int sHeight, int vWidth, int vHeight, int fps);
void DestroyGame(Game *game);
void RunGame(Game *game);
void UpdateGame(Game *game);
void DrawGame(Game *game);

#endif //SHOOTER_THEGAME_H
