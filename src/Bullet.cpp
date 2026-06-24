#include "Bullet.h"

Bullet::Bullet() : pos{0,0}, vel{0,0}, radius(5), active(false), isEnemy(false) {}

Bullet::Bullet(Vector2 position, Vector2 velocity, float r, bool enemy)
    : pos(position), vel(velocity), radius(r), active(true), isEnemy(enemy) {}

void Bullet::Update() {
    if (!active) return;
    pos.x += vel.x * GetFrameTime() * 60; // условно 60 FPS
    pos.y += vel.y * GetFrameTime() * 60;

    // Удаляем, если вышла за экран
    if (pos.x < -50 || pos.x > GetScreenWidth()+50 ||
        pos.y < -50 || pos.y > GetScreenHeight()+50)
        active = false;
}

void Bullet::Draw() const {
    if (!active) return;
    Color color = isEnemy ? RED : YELLOW;
    DrawCircleV(pos, radius, color);
}