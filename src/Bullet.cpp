#include "Bullet.h"
#include <cmath>
#include <cstddef>

Bullet::Bullet() : pos{0,0}, vel{0,0}, radius(5), active(false), isEnemy(false), type(NORMAL), damage(1),
orbitRadius(0), orbitSpeed(0), angle(0) {}

Bullet::Bullet(Vector2 position, Vector2 velocity, float r, bool enemy, BulletType t)
    : pos(position), vel(velocity), radius(r), active(true), isEnemy(enemy), type(t),
    orbitRadius(0), orbitSpeed(0), angle(0) {
        if (type == NORMAL) damage = 1;
        else if (type == ASTEROID) damage = 3;
        else if (type == VORTEX) damage = 1;
    }

// Конструктор для вихря (создаёт центр + спутники)
Bullet::Bullet(Vector2 position, Vector2 velocity, float r, bool enemy, int satelliteCount, float orbitR, float orbitS)
    : pos(position), vel(velocity), radius(r), active(true), isEnemy(enemy), type(VORTEX),
      orbitRadius(orbitR), orbitSpeed(orbitS), angle(0) {
    damage = 1; // урон центра
    // Создаём спутники
    for (int i = 0; i < satelliteCount; ++i) {
        float initAngle = (2 * PI / satelliteCount) * i;
        Vector2 offset = {cosf(initAngle) * orbitRadius, sinf(initAngle) * orbitRadius};
        Vector2 satPos = {pos.x + offset.x, pos.y + offset.y};
        Bullet sat(satPos, vel, 4, enemy, NORMAL); // маленькие пули
        sat.damage = 1; // урон спутника
        satellites.push_back(sat);
    }
}

void Bullet::Update() {
    if (!active) return;
    pos.x += vel.x * GetFrameTime() * 60; // условно 60 FPS
    pos.y += vel.y * GetFrameTime() * 60;

    if (type == VORTEX) {
        angle += orbitSpeed * GetFrameTime() * 60;
        for (size_t i = 0; i < satellites.size(); ++i) {
            float baseAngle = (2 * PI / satellites.size()) * i + angle;
            Vector2 offset = {cosf(baseAngle) * orbitRadius, sinf(baseAngle) * orbitRadius};
            satellites[i].pos = {pos.x + offset.x, pos.y + offset.y};
            satellites[i].vel = vel; // спутники движутся с той же скоростью
            satellites[i].Update();  // обновляем их (для выхода за экран)
        }
    }
    // Удаляем, если вышла за экран
    if (pos.x < -50 || pos.x > GetScreenWidth()+50 ||
        pos.y < -50 || pos.y > GetScreenHeight()+50){
        active = false;
        for (auto& sat : satellites) sat.active = false;
    }
}

void Bullet::Draw() const {
    if (!active) return;
    if (type == NORMAL) {
        Color color = isEnemy ? RED : YELLOW;
        DrawCircleV(pos,radius,color);
    }
    else if(type == ASTEROID)
    {
        DrawCircleV(pos, radius, BROWN);
        DrawCircleLines(pos.x, pos.y, radius, DARKBROWN);
    } else if (type == VORTEX){
        // Рисуем центр (белый/серый)
        DrawCircleV(pos, radius, GRAY);
        DrawCircleLines(pos.x, pos.y, radius, WHITE);
        // Рисуем спутники (красные, если вражеские)
        for (const auto& sat : satellites) {
            sat.Draw();
        }
    }

}