//
// Created by snill on 2026-09-05.
//

#include "Projectile.h"
#include "../components/components.h"
#include "raylib.h"

void ProjectileSystem(ecs_iter_t *it) {
    Projectile *projectile = ecs_field(it, Projectile, 0);
    
    for (int i = 0; i < it->count; i++) {
        projectile[i].lifetime -= it->delta_time;
        
        // Ta bort entiteten om lifetime är slut
        if (projectile[i].lifetime <= 0.0f) {
            ecs_delete(it->world, it->entities[i]);
        }
    }
}
