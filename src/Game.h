#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>   // для std::remove_if
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

class Game {
public:
    Player player;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies;
    float enemySpawnTimer;
    float enemySpawnInterval;
    float asteroidSpawnTimer;
    float asteroidSpawnInterval;

    Game();
    void Update();
    void Draw();
    void CheckCollisions();
};