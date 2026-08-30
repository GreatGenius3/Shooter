#include "flecs.h"
#include "Movement.h"
#include "../components/Position.h"
#include "../components/Velocity.h"

void MovementSystem(ecs_iter_t *it) {
    Position *pos = ecs_field(it, Position, 1);
    Velocity *vel = ecs_field(it, Velocity, 2);
    
    for (int i = 0; i < it->count; i++) {
        pos[i].x += vel[i].x;
        pos[i].y += vel[i].y;
    }
}

void RegisterMovementSystem(ecs_world_t *world) {
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_SYSTEM(world, MovementSystem, EcsOnUpdate, Position, Velocity);
}
