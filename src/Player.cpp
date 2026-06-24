#include "Player.h"
#include <cmath>

Player::Player() {
    pos = {400, 300};
    radius = 15;
    speed = 3;
    health = 5;
    shootCooldown = 0;
    shootDelay = 0.15f;
}

void Player::Update(std::vector<Bullet>& bullets) {
    // Управление
    Vector2 move = {0, 0};
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))    move.y -= 1;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN))  move.y += 1;
    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))  move.x -= 1;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) move.x += 1;

    if (move.x != 0 || move.y != 0) {
        float len = sqrtf(move.x*move.x + move.y*move.y);
        move.x /= len;
        move.y /= len;
        pos.x += move.x * speed;
        pos.y += move.y * speed;
    }

    // Ограничение в пределах экрана
    if (pos.x < radius) pos.x = radius;
    if (pos.x > GetScreenWidth() - radius) pos.x = GetScreenWidth() - radius;
    if (pos.y < radius) pos.y = radius;
    if (pos.y > GetScreenHeight() - radius) pos.y = GetScreenHeight() - radius;

    // Стрельба (пробел)
    shootCooldown -= GetFrameTime();
    if (IsKeyDown(KEY_SPACE) && shootCooldown <= 0) {
        shootCooldown = shootDelay;
        // Создаём пулю игрока (вверх)
        Bullet b(pos, {0, -8}, 4, false);
        bullets.push_back(b);
    }
}

void Player::Draw() const {
    DrawCircleV(pos, radius, BLUE);
    DrawCircleLines(pos.x, pos.y, radius, LIGHTGRAY);
}