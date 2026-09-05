//
// Created by snill on 2026-09-04.
//

#include "RenderSystem.h"
#include "../TheGame.h"
#include "../components/components.h"
#include "../components/Render.h"

void RenderSprites(ecs_iter_t *it) {
    Position *pos = ecs_field(it, Position, 0);
    SpriteRenderer *renderer = ecs_field(it, SpriteRenderer, 1);
    
    for (int i = 0; i < it->count; i++) {
        Rectangle dest = {
            .x = pos[i].x,
            .y = pos[i].y,
            .width = renderer[i].source.width * renderer[i].scale,
            .height = renderer[i].source.height * renderer[i].scale
        };
        
        DrawRectangle((int)dest.x, (int)dest.y, (int)dest.width, (int)dest.height, renderer[i].tint);
    }
}