//
// Created by snill on 2026-09-05.
//

#ifndef SHOOTER_COLLISIONBOX_H
#define SHOOTER_COLLISIONBOX_H

#include "raylib.h"

typedef struct {
    Rectangle box;      // Hitbox relativt till entitetens position
    int layer;          // Collision layer för att filtrera vilka som kolliderar
    int mask;           // Collision mask för att filtrera vilka vi kollar mot
    bool enabled;       // Om true, kollar kollision
} CollisionBox;

#endif //SHOOTER_COLLISIONBOX_H
