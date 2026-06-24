#include "Game.h"
#include <algorithm>
#include <cmath>

Game::Game() 
    : enemySpawnTimer(0), enemySpawnInterval(3.0f), asteroidSpawnTimer(0), asteroidSpawnInterval(5.0f) {
}

void Game::Update() {
    player.Update(bullets);

    // Обновить все пули
    for (auto& b : bullets) b.Update();

    // Удалить неактивные пули
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) { return !b.active; }), bullets.end());

    // Спавн врагов
    enemySpawnTimer -= GetFrameTime();
    if (enemySpawnTimer <= 0) {
        enemySpawnTimer = enemySpawnInterval;
        float x = GetRandomValue(50, GetScreenWidth()-50);
        enemies.emplace_back(Vector2{x, -30});
    }

    // Обновить врагов
    for (auto& e : enemies) e.Update(bullets);

    // Проверка столкновений
    CheckCollisions();

    // Удалить неактивных врагов
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return !e.active; }), enemies.end());
    // Спавн астероидов
    asteroidSpawnTimer -= GetFrameTime();
    if (asteroidSpawnTimer <= 0) {
        asteroidSpawnTimer = asteroidSpawnInterval;
        // Спавним один астероид сбоку или сверху
        float x = GetRandomValue(0, GetScreenWidth());
        float y = -30; // сверху, но можно сбоку
        // Создаём пулю-астероид
        Vector2 dir = {0, 1}; // летит вниз
        // Можно направить на игрока:
        Vector2 toPlayer = {player.pos.x - x, player.pos.y - y};
        float len = sqrtf(toPlayer.x*toPlayer.x + toPlayer.y*toPlayer.y);
        if (len > 0) { dir = {toPlayer.x/len, toPlayer.y/len}; }
        float speed = 1.5f; // медленнее обычных
        Vector2 vel = {dir.x * speed, dir.y * speed};
        Bullet asteroid({x, y}, vel, 20, true, ASTEROID);
        bullets.push_back(asteroid);
    }
}

void Game::Draw() {
    player.Draw();
    for (const auto& b : bullets) b.Draw();
    for (const auto& e : enemies) e.Draw();

    // UI: здоровье
    DrawText(TextFormat("HP: %d", player.health), 10, 10, 20, WHITE);
}

void Game::CheckCollisions() {
    // Пули игрока vs враги
    for (auto& b : bullets) {
        if (!b.active || b.isEnemy) continue;
        for (auto& e : enemies) {
            if (!e.active) continue;
            float dx = b.pos.x - e.pos.x;
            float dy = b.pos.y - e.pos.y;
            if (dx*dx + dy*dy < (b.radius + e.radius)*(b.radius + e.radius)) {
                b.active = false;
                e.active = false;
            }
        }
    }

    // Вражеские пули vs игрок
    for (auto& b : bullets) {
        if (!b.active || !b.isEnemy) continue;
        float dx = b.pos.x - player.pos.x;
        float dy = b.pos.y - player.pos.y;
        if (dx*dx + dy*dy < (b.radius + player.radius)*(b.radius + player.radius)) {
            b.active = false;
            player.health -= b.damage;
        }
    }

    // Враги vs игрок
    for (auto& e : enemies) {
        if (!e.active) continue;
        float dx = e.pos.x - player.pos.x;
        float dy = e.pos.y - player.pos.y;
        if (dx*dx + dy*dy < (e.radius + player.radius)*(e.radius + player.radius)) {
            e.active = false;
            player.health--;
        }
    }
}