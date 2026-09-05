//
// Created by snill on 2026-09-05.
//

#include "Weapon.h"
#include "../components/components.h"
#include "raylib.h"

void WeaponSystem(ecs_iter_t *it) {
    Position *pos = ecs_field(it, Position, 0);
    Weapon *weapon = ecs_field(it, Weapon, 1);
    
    float currentTime = GetTime();
    
    for (int i = 0; i < it->count; i++) {
        // Kolla om vi kan skjuta (cooldown passerad)
        if (currentTime >= weapon[i].lastFireTime + weapon[i].cooldown) {
            if (IsKeyDown(weapon[i].fireKey)) {
                // Skapa en projektil
                ecs_entity_t projectile = ecs_new(it->world);
                
                Position projPos = {pos[i].x, pos[i].y};
                Velocity projVel = {0.0f, -weapon[i].projectileSpeed}; // Skjut uppåt för nu
                
                SpriteRenderer projRenderer = {
                    .source = {0, 0, 8, 8},
                    .scale = 1.0f,
                    .rotation = 0.0f,
                    .tint = YELLOW
                };
                
                Projectile projData = {
                    .lifetime = weapon[i].projectileLifetime,
                    .damage = 10.0f,
                    .owner = 1 // PLAYER
                };
                
                ecs_set_ptr(it->world, projectile, Position, &projPos);
                ecs_set_ptr(it->world, projectile, Velocity, &projVel);
                ecs_set_ptr(it->world, projectile, SpriteRenderer, &projRenderer);
                ecs_set_ptr(it->world, projectile, Projectile, &projData);
                
                weapon[i].lastFireTime = currentTime;
            }
        }
    }
}
