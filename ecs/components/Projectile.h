//
// Created by snill on 2026-09-05.
//

#ifndef SHOOTER_PROJECTILE_H
#define SHOOTER_PROJECTILE_H

typedef struct {
    float lifetime;    // Hur länge skottet lever i sekunder
    float damage;      // Skada vid träff
    int owner;        // Vem som sköt (t.ex. PLAYER=1, ENEMY=2)
} Projectile;

#endif //SHOOTER_PROJECTILE_H
