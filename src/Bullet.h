#pragma once
#include "raylib.h"

class Bullet {
public:
    Vector2 pos;
    Vector2 vel;
    float radius;
    bool active;        // true – пуля жива, false – можно удалить
    bool isEnemy;       // true – вражеская, false – игрока

    Bullet();
    Bullet(Vector2 position, Vector2 velocity, float radius, bool enemy);

    void Update();
    void Draw() const;
};