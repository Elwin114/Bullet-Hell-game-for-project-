#include "Enemy.h"
#include <cmath>

Enemy::Enemy(Vector2 position) : pos(position), radius(20), shootTimer(0), shootInterval(1.5f), active(true) {
    // выбрать случайный паттерн при создании
    currentPattern = static_cast<Pattern>(GetRandomValue(0, 2));
}

void Enemy::SpawnFlower(std::vector<Bullet>& bullets) {
    int count = 12; // количество пуль
    float baseSpeed = 3.0f;
    for (int i = 0; i < count; ++i) {
        float angle = (2 * PI / count) * i;
        Vector2 vel = {cosf(angle) * baseSpeed, sinf(angle) * baseSpeed};
        bullets.emplace_back(pos, vel, 5, true, BulletType::NORMAL);
    }
}

void Enemy::SpawnLine(std::vector<Bullet>& bullets) {
    int count = 5;
    float angle = atan2(GetScreenHeight()/2 - pos.y, GetScreenWidth()/2 - pos.x); // летят к центру
    for (int i = 0; i < count; ++i) {
        float offset = (i - count/2) * 10.0f; // смещение по перпендикуляру
        float perpAngle = angle + PI/2;
        Vector2 dir = {cosf(angle), sinf(angle)};
        Vector2 perp = {cosf(perpAngle), sinf(perpAngle)};
        Vector2 startPos = {pos.x + perp.x * offset, pos.y + perp.y * offset};
        Vector2 vel = {dir.x * 4.0f, dir.y * 4.0f};
        bullets.emplace_back(startPos, vel, 5, true, NORMAL);
    }
}

void Enemy::SpawnRandom(std::vector<Bullet>& bullets) {
    int count = 10;
    for (int i = 0; i < count; ++i) {
        float angle = GetRandomValue(0, 360) * DEG2RAD;
        float speed = GetRandomValue(1, 4);
        Vector2 vel = {cosf(angle) * speed, sinf(angle) * speed};
        bullets.emplace_back(pos, vel, 5, true, BulletType::NORMAL);
    }
}


void Enemy::Update(std::vector<Bullet>& bullets) {
    if (!active) return;

    shootTimer -= GetFrameTime();
    if (shootTimer <= 0) {
        shootTimer = shootInterval;
        // Веер из 8 пуль
        switch (currentPattern) {
            case FLOWER: SpawnFlower(bullets); break;
            case LINE: SpawnLine(bullets); break;
            case RANDOM: SpawnRandom(bullets); break;
        }
    }
}

void Enemy::Draw() const {
    if (!active) return;
    DrawCircleV(pos, radius, PURPLE);
}