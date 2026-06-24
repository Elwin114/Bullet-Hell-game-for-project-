#pragma once
#include "raylib.h"

enum BulletType {
    NORMAL,   // красные обычные
    ASTEROID  // астероид
};

class Bullet {
public:
    Vector2 pos;
    Vector2 vel;
    float radius;
    bool active;        // true – пуля жива, false – можно удалить
    BulletType type;
    int damage;
    bool isEnemy;       // true – вражеская, false – игрока

    Bullet();
    Bullet(Vector2 position, Vector2 velocity, float radius, bool enemy, BulletType type = NORMAL);

    void Update();
    void Draw() const;
};