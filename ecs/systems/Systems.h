//
// Created by snill on 2026-09-04.
//

#ifndef SHOOTER_SYSTEMS_H
#define SHOOTER_SYSTEMS_H

#include "flecs.h"
#include <math.h>

// Berätta för kompilatorn att Engine-structen existerar (Forward declaration)
typedef struct Game Engine;

// En samlingsfunktion för att registrera alla spelsystem
void init_game_systems(Engine *engine);

#endif //SHOOTER_SYSTEMS_H
