#include "components.h"

ECS_COMPONENT_DECLARE(Position);
ECS_COMPONENT_DECLARE(Velocity);
ECS_COMPONENT_DECLARE(Sprite);
ECS_COMPONENT_DECLARE(SpriteRenderer);
ECS_COMPONENT_DECLARE(SpriteScale);
ECS_COMPONENT_DECLARE(Bounds);
ECS_COMPONENT_DECLARE(CollisionBox);
ECS_COMPONENT_DECLARE(PlayerInput);
ECS_COMPONENT_DECLARE(Weapon);
ECS_COMPONENT_DECLARE(Projectile);

void init_components(ecs_world_t *world)
{
    ECS_COMPONENT_DEFINE(world, Position);
    ECS_COMPONENT_DEFINE(world, Velocity);
    ECS_COMPONENT_DEFINE(world, Sprite);
    ECS_COMPONENT_DEFINE(world, SpriteRenderer);
    ECS_COMPONENT_DEFINE(world, SpriteScale);
    ECS_COMPONENT_DEFINE(world, Bounds);
    ECS_COMPONENT_DEFINE(world, CollisionBox);
    ECS_COMPONENT_DEFINE(world, PlayerInput);
    ECS_COMPONENT_DEFINE(world, Weapon);
    ECS_COMPONENT_DEFINE(world, Projectile);
}