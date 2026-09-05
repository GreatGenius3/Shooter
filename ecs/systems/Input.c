//
// Created by snill on 2026-09-05.
//

#include "Input.h"
#include "../components/components.h"
#include "raylib.h"
#include "raymath.h"

void KeyboardInputSystem(ecs_iter_t *it) {
    Velocity *vel = ecs_field(it, Velocity, 0);
    PlayerInput *input = ecs_field(it, PlayerInput, 1);
    
    for (int i = 0; i < it->count; i++) {
        float moveX = 0.0f;
        float moveY = 0.0f;
        
        if (IsKeyDown(input[i].upKey)) {
            moveY -= 1.0f;
        }
        if (IsKeyDown(input[i].downKey)) {
            moveY += 1.0f;
        }
        if (IsKeyDown(input[i].leftKey)) {
            moveX -= 1.0f;
        }
        if (IsKeyDown(input[i].rightKey)) {
            moveX += 1.0f;
        }
        
        // Normalisera diagonal rörelse
        if (moveX != 0.0f && moveY != 0.0f) {
            float length = sqrtf(moveX * moveX + moveY * moveY);
            moveX /= length;
            moveY /= length;
        }
        
        vel[i].x = moveX * input[i].speed;
        vel[i].y = moveY * input[i].speed;
    }
}
