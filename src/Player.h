#pragma once
#include "raylib.h"
#include <vector>
#include "Bullet.h"   // <-- добавить

class Player {
public:
    Vector2 pos;
    float radius;
    float speed;
    int health;
    float shootCooldown;
    float shootDelay;
    Texture2D texture;

    Player();
    void SetTexture(Texture2D tex);
    void Update(std::vector<Bullet>& bullets);
    void Draw() const;
};