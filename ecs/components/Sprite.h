#ifndef SHOOTER_ECS_SPRITE_H
#define SHOOTER_ECS_SPRITE_H

#include "raylib.h"
#include "flecs.h"

typedef struct Sprite {
    Texture2D texture;
    Rectangle sourceRect;
    Color tint;
} Sprite;

#endif //SHOOTER_ECS_SPRITE_H
