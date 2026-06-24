#pragma once
#include "raylib.h"
#include <vector>
#include "Bullet.h"   // <-- добавить

class Enemy {
public:
    Vector2 pos;
    float radius;
    float shootTimer;
    float shootInterval;
    bool active;

    Enemy(Vector2 position);
    void Update(std::vector<Bullet>& bullets);
    void Draw() const;
};