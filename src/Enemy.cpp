#include "Enemy.h"
#include <cmath>

Enemy::Enemy(Vector2 position) {
    pos = position;
    radius = 20;
    shootTimer = 0;
    shootInterval = 1.5f; // сек между залпами
    active = true;
}

void Enemy::Update(std::vector<Bullet>& bullets) {
    if (!active) return;

    shootTimer -= GetFrameTime();
    if (shootTimer <= 0) {
        shootTimer = shootInterval;
        // Веер из 8 пуль
        int count = 8;
        for (int i = 0; i < count; ++i) {
            float angle = (2 * PI / count) * i;
            float speed = 3;
            Vector2 vel = {cosf(angle) * speed, sinf(angle) * speed};
            Bullet b(pos, vel, 5, true);
            bullets.push_back(b);
        }
    }
}

void Enemy::Draw() const {
    if (!active) return;
    DrawCircleV(pos, radius, PURPLE);
}