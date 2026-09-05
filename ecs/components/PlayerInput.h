//
// Created by snill on 2026-09-05.
//

#ifndef SHOOTER_PLAYERINPUT_H
#define SHOOTER_PLAYERINPUT_H

#include "raylib.h"

typedef struct {
    float speed;         // Hastighet i pixlar per sekund
    int upKey;           // Tangent för upp (t.ex. KEY_W)
    int downKey;         // Tangent för ner (t.ex. KEY_S)
    int leftKey;         // Tangent för vänster (t.ex. KEY_A)
    int rightKey;        // Tangent för höger (t.ex. KEY_D)
} PlayerInput;

#endif //SHOOTER_PLAYERINPUT_H
