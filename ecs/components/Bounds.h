//
// Created by snill on 2026-09-05.
//

#ifndef SHOOTER_BOUNDS_H
#define SHOOTER_BOUNDS_H

#include "raylib.h"

typedef struct {
    float minX;
    float minY;
    float maxX;
    float maxY;
    bool bounce; // Om true, studsar mot gränserna
} Bounds;

#endif //SHOOTER_BOUNDS_H
