//
// Created by snill on 2026-09-05.
//

#ifndef SHOOTER_WEAPON_H
#define SHOOTER_WEAPON_H

#include "raylib.h"

typedef struct {
    int fireKey;        // Tangent för att skjuta (t.ex. KEY_SPACE)
    float cooldown;     // Tid mellan skott i sekunder
    float lastFireTime; // Senaste gången vi sköt
    float projectileSpeed; // Hastighet på projektiler
    float projectileLifetime; // Hur länge projektiler lever
} Weapon;

#endif //SHOOTER_WEAPON_H
