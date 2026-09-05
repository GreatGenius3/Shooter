//
// Created by snill on 2026-09-05.
//

#include "Movement.h"
#include "../components/components.h"

void MovementSystem(ecs_iter_t *it) {
    Position *pos = ecs_field(it, Position, 0);
    Velocity *vel = ecs_field(it, Velocity, 1);
    Bounds *bounds = ecs_field(it, Bounds, 2);
    
    for (int i = 0; i < it->count; i++) {
        // Uppdatera position
        pos[i].x += vel[i].x * it->delta_time;
        pos[i].y += vel[i].y * it->delta_time;
        
        // Hantera gränser om Bounds finns
        if (bounds) {
            if (bounds[i].bounce) {
                // Studsa mot gränser
                if (pos[i].x < bounds[i].minX) {
                    pos[i].x = bounds[i].minX;
                    vel[i].x *= -1;
                } else if (pos[i].x > bounds[i].maxX) {
                    pos[i].x = bounds[i].maxX;
                    vel[i].x *= -1;
                }
                
                if (pos[i].y < bounds[i].minY) {
                    pos[i].y = bounds[i].minY;
                    vel[i].y *= -1;
                } else if (pos[i].y > bounds[i].maxY) {
                    pos[i].y = bounds[i].maxY;
                    vel[i].y *= -1;
                }
            } else {
                // Klumpa position vid gränser (studsa inte)
                if (pos[i].x < bounds[i].minX) {
                    pos[i].x = bounds[i].minX;
                } else if (pos[i].x > bounds[i].maxX) {
                    pos[i].x = bounds[i].maxX;
                }
                
                if (pos[i].y < bounds[i].minY) {
                    pos[i].y = bounds[i].minY;
                } else if (pos[i].y > bounds[i].maxY) {
                    pos[i].y = bounds[i].maxY;
                }
            }
        }
    }
}
