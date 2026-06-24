#pragma once
#include "raylib.h"
#include <vector>
#include "Bullet.h"   // <-- добавить

enum Pattern {
    FLOWER,
    LINE,
    RANDOM
};

class Enemy {
public:
    Vector2 pos;
    float radius;
    float shootTimer;
    float shootInterval;
    bool active;
    Pattern currentPattern;

    Enemy(Vector2 position);
    void Update(std::vector<Bullet>& bullets);
    void Draw() const;
    void SpawnFlower(std::vector<Bullet>& bullets);
    void SpawnLine(std::vector<Bullet>& bullets);
    void SpawnRandom(std::vector<Bullet>& bullets);
};