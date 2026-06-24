#include "Bullet.h"

Bullet::Bullet() : pos{0,0}, vel{0,0}, radius(5), active(false), isEnemy(false), type(NORMAL), damage(1) {}

Bullet::Bullet(Vector2 position, Vector2 velocity, float r, bool enemy, BulletType t)
    : pos(position), vel(velocity), radius(r), active(true), isEnemy(enemy), type(t) {
        if (type == NORMAL) damage = 1;
        else if (type == ASTEROID) damage = 3;
    }

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
    if (type == NORMAL) {
        Color color = isEnemy ? RED : YELLOW;
        DrawCircleV(pos,radius,color);
    }
    else if(type == ASTEROID)
    {
        DrawCircleV(pos, radius, BROWN);
        DrawCircleLines(pos.x, pos.y, radius, DARKBROWN);
    }

}