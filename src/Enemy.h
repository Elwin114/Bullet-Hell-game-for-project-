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

enum EnemyType {
    NORMAL_ENEMY,
    VORTEX_ENEMY,
    ASTEROID_ENEMY
};


class Enemy {
public:
    Vector2 pos;
    Vector2 velocity;
    float radius;
    float shootTimer;
    float shootInterval;
    bool active;
    Pattern currentPattern;
    EnemyType type;
    int health;
    int maxHealth;
    Texture2D texture;

    Enemy(Vector2 position, EnemyType type = NORMAL_ENEMY);
    void SetTexture(Texture2D tex);
    void Update(std::vector<Bullet>& bullets);
    void Draw() const;
    void TakeDamage(int damage);
    void OnDeath(std::vector<Bullet>& bullets); // эффекты при смерти
    static void SpawnFlower(Vector2 pos, std::vector<Bullet>& bullets);
    static void SpawnLine(Vector2 pos, std::vector<Bullet>& bullets);
    static void SpawnRandom(Vector2 pos, std::vector<Bullet>& bullets);
private:
    void SpawnVortex(std::vector<Bullet>& bullets);
};