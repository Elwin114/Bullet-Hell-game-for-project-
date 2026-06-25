#include "Game.h"
#include <algorithm>
#include <cmath>

Game::Game(Texture2D pTex, Texture2D aTex, Texture2D vTex)
    : enemySpawnTimer(0), enemySpawnInterval(3.0f),
      patternSpawnTimer(0), patternSpawnInterval(1.0f),
      playerTex(pTex), asteroidTex(aTex), vortexTex(vTex) {
    player.SetTexture(playerTex);
}

void Game::Update() {
    player.Update(bullets);

    for (auto& b : bullets) b.Update();
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
        [](const Bullet& b) { return !b.active; }), bullets.end());

    patternSpawnTimer -= GetFrameTime();
    if (patternSpawnTimer <= 0) {
        patternSpawnTimer = patternSpawnInterval;
        float x = GetRandomValue(50, GetScreenWidth()-50);
        Vector2 pos = {x, -20};
        int pattern = GetRandomValue(0, 2);
        switch (pattern) {
            case 0: Enemy::SpawnFlower(pos, bullets); break;
            case 1: Enemy::SpawnLine(pos, bullets); break;
            case 2: Enemy::SpawnRandom(pos, bullets); break;
        }
    }

    enemySpawnTimer -= GetFrameTime();
    if (enemySpawnTimer <= 0) {
        enemySpawnTimer = enemySpawnInterval;
        float x = GetRandomValue(50, GetScreenWidth()-50);
        int rnd = GetRandomValue(0, 99);
        EnemyType type = (rnd < 70) ? VORTEX_ENEMY : ASTEROID_ENEMY;
        Enemy enemy(Vector2{x, -30}, type);
        if (type == VORTEX_ENEMY) {
            enemy.SetTexture(vortexTex);
        } else if (type == ASTEROID_ENEMY) {
            enemy.SetTexture(asteroidTex);
        }
        enemies.push_back(enemy);
    }

    for (auto& e : enemies) e.Update(bullets);
    CheckCollisions();
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
        [](const Enemy& e) { return !e.active; }), enemies.end());
}

void Game::Draw() {
    player.Draw();
    for (const auto& b : bullets) b.Draw();
    for (const auto& e : enemies) e.Draw();
    DrawText(TextFormat("HP: %d", player.health), 10, 10, 20, WHITE);
}

void Game::CheckCollisions() {
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

    for (auto& b : bullets) {
        if (!b.active || !b.isEnemy) continue;
        float dx = b.pos.x - player.pos.x;
        float dy = b.pos.y - player.pos.y;
        if (dx*dx + dy*dy < (b.radius + player.radius)*(b.radius + player.radius)) {
            b.active = false;
            player.health -= b.damage;
        }
    }

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