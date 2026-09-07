//
// Created by snill on 2026-09-05.
//

#include "Weapon.h"
#include "../components/components.h"
#include "raylib.h"
#include "raymath.h"

void WeaponSystem(ecs_iter_t *it) {
    Position *pos = ecs_field(it, Position, 0);
    Weapon *weapon = ecs_field(it, Weapon, 1);
    
    float currentTime = GetTime();
    
    for (int i = 0; i < it->count; i++) {
        // Kolla om vi kan skjuta (cooldown passerad)
        if (currentTime >= weapon[i].lastFireTime + weapon[i].cooldown) {
            if (IsKeyDown(weapon[i].fireKey)) {
                // Hämta Velocity från entiteten för att bestämma riktning
                const Velocity *entityVel = ecs_get(it->world, it->entities[i], Velocity);
                
                // Skapa en projektil
                ecs_entity_t projectile = ecs_new(it->world);
                
                Position projPos = {pos[i].x, pos[i].y};
                Velocity projVel = {0.0f, 0.0f};
                const SpriteRenderer *getSprite = ecs_get(it->world, it->entities[i], SpriteRenderer);

                // Kolla om vi har en lastDirection data
                const LastDirection *lastDir = ecs_get(it->world, it->entities[i], LastDirection);
                LastDirection defaultDir = {0.0f, -1.0f}; // Standard: uppåt
                if (!lastDir) {
                    lastDir = &defaultDir;
                }
                
                // Bestäm skjutriktning baserat på entitetens Velocity
                if (entityVel)
                {
                    float length = sqrtf(entityVel->x * entityVel->x + entityVel->y * entityVel->y);
                    if (length > 0.01f)
                    {
                        // Normalisera och applicera projektilhastighet
                        projVel.x = (entityVel->x / length) * weapon[i].projectileSpeed;
                        projVel.y = (entityVel->y / length) * weapon[i].projectileSpeed;
                    } else
                    {
                        // const LastDirection *lastDir = ecs_get(it->world, it->entities[i], LastDirection);
                        // Om entiteten står stilla, skjut uppåt som standard
                        // projVel.y = -weapon[i].projectileSpeed;
                        projVel.y = lastDir->y * weapon[i].projectileSpeed;
                        projVel.x = lastDir->x * weapon[i].projectileSpeed;
                    }
                } else {
                    // Ingen Velocity, skjut uppåt som standard
                    projVel.y = -weapon[i].projectileSpeed;
                }
                
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
