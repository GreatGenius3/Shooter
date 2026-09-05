//
// Created by snill on 2026-09-04.
//

#include "Systems.h"
#include "../TheGame.h"
#include "RenderSystem.h"
#include "Movement.h"
#include "Input.h"
#include "Weapon.h"
#include "Projectile.h"

void init_game_systems(Engine *engine) {
    ecs_world_t *world = engine->world;
    
    // Registrera KeyboardInputSystem - sätter Velocity baserat på tangentbord
    ECS_SYSTEM(world, KeyboardInputSystem, EcsOnUpdate, Velocity, PlayerInput);
    
    // Registrera WeaponSystem - hanterar skjut-knapp och skapar projektiler
    ECS_SYSTEM(world, WeaponSystem, EcsOnUpdate, Position, Weapon);
    
    // Registrera ProjectileSystem - tar bort gamla projektiler
    ECS_SYSTEM(world, ProjectileSystem, EcsOnUpdate, Projectile);
    
    // Registrera MovementSystem med optional Bounds för studs
    ECS_SYSTEM(world, MovementSystem, EcsOnUpdate, Position, Velocity, ?Bounds);
    
    // Registrera RenderSystem (Position, SpriteRenderer) - enkel primitiv rendering
    ECS_SYSTEM(world, RenderSprites, EcsOnUpdate, Position, SpriteRenderer);
}