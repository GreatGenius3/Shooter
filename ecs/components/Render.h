//
// Created by snill on 2026-09-04.
//

#ifndef SHOOTER_RENDER_H
#define SHOOTER_RENDER_H

#include "raylib.h"

typedef struct {
    Texture2D texture;
} SpriteTexture;

typedef struct {
    Rectangle source; // Delen av bilden som ska ritas (bra för spritesheets)
    float scale;      // Skala (1.0 = normal storlek)
    float rotation;   // Rotation i grader
    Color tint;       // Färgton (oftast WHITE)
} SpriteRenderer;

typedef struct {
    Vector2 scale; // Non-uniform scale (x = width scale, y = height scale)
} SpriteScale;

#endif //SHOOTER_RENDER_H
