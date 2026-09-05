#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "flecs.h"
#include "Position.h"
#include "Velocity.h"  
#include "Sprite.h"
#include "Render.h"
#include "Bounds.h"
#include "CollisionBox.h"
#include "PlayerInput.h"

extern ECS_COMPONENT_DECLARE(Position);
extern ECS_COMPONENT_DECLARE(Velocity);
extern ECS_COMPONENT_DECLARE(Sprite);
extern ECS_COMPONENT_DECLARE(SpriteRenderer);
extern ECS_COMPONENT_DECLARE(SpriteScale);
extern ECS_COMPONENT_DECLARE(Bounds);
extern ECS_COMPONENT_DECLARE(CollisionBox);
extern ECS_COMPONENT_DECLARE(PlayerInput);

// 3. En smidig funktion för att registrera allt i Flecs-världen vid start
void init_components(ecs_world_t *world);

#endif // COMPONENTS_H