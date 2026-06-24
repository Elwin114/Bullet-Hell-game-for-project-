#pragma once
#include "raylib.h"
#include <vector>
#include "Bullet.h"   // <-- добавить

enum Pattern {
    PATTERN_FLOWER,
    PATTERN_LINE,
    PATTERN_RANDOM,
    PATTERN_VORTEX
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
private:
    void SpawnFlower(std::vector<Bullet>& bullets);
    void SpawnLine(std::vector<Bullet>& bullets);
    void SpawnRandom(std::vector<Bullet>& bullets);
    void SpawnVortex(std::vector<Bullet>& bullets);
};