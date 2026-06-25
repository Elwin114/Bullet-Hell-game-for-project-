#include "Game.h"
#include <algorithm>
#include <cmath>

Game::Game(Texture2D pTex): enemySpawnTimer(0), enemySpawnInterval(3.0f), patternSpawnTimer(0), patternSpawnInterval(1.0f), playerTex(pTex) {
    player.SetTexture(playerTex);
}

void Game::Update() {
    player.Update(bullets);

    // Обновить все пули
    for (auto& b : bullets) b.Update();

    // Удалить неактивные пули
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) { return !b.active; }), bullets.end());
    patternSpawnTimer -= GetFrameTime();
    if (patternSpawnTimer <= 0) {
        patternSpawnTimer = patternSpawnInterval;
        float x = GetRandomValue(50, GetScreenWidth()-50);
        Vector2 pos = {x, -20};
        int pattern = GetRandomValue(0, 2); // 0-цветок, 1-линия, 2-случайный
        switch (pattern) {
            case 0: Enemy::SpawnFlower(pos, bullets); break;
            case 1: Enemy::SpawnLine(pos, bullets); break;
            case 2: Enemy::SpawnRandom(pos, bullets); break;
        }
    }
    // Спавн врагов
    enemySpawnTimer -= GetFrameTime();
    if (enemySpawnTimer <= 0) {
        enemySpawnTimer = enemySpawnInterval;
        float x = GetRandomValue(50, GetScreenWidth()-50);
        // Выбираем тип врага случайно
        int rnd = GetRandomValue(0, 99);
        EnemyType type = (rnd < 70) ? VORTEX_ENEMY : ASTEROID_ENEMY;
        enemies.emplace_back(Vector2{x, -30}, type);   // <-- теперь передаём тип
    }

    // Обновить врагов
    for (auto& e : enemies) e.Update(bullets);

    // Проверка столкновений
    CheckCollisions();

    // Удалить неактивных врагов
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return !e.active; }), enemies.end());

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
                e.TakeDamage(b.damage);
                if (!e.active) {
                    e.OnDeath(bullets);
                }
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