#include "Enemy.h"

#include <cmath>
#include <cstdlib>

Enemy::Enemy(Vector2 position, EnemyType t)
    : pos(position),
      radius(20),
      shootTimer(0),
      shootInterval(1.5f),
      active(true),
      type(t),
      texture({0}) {
  switch (type) {
    case VORTEX_ENEMY:
      radius = 25;
      health = 4;
      velocity = {0, 0.3f};
      shootInterval = 2.0f;
      break;
    case ASTEROID_ENEMY:
      radius = 40;
      health = 6;
      velocity = {0, 0.2f};
      shootInterval = 0;  // не стреляет
      break;
  }
  if (type == VORTEX_ENEMY)
    currentPattern = static_cast<Pattern>(GetRandomValue(0, 3));
}
void Enemy::SetTexture(Texture2D tex) { texture = tex; }
void Enemy::SpawnFlower(Vector2 pos, std::vector<Bullet>& bullets) {
  int count = 12;  // количество пуль
  float baseSpeed = 3.0f;
  for (int i = 0; i < count; ++i) {
    float angle = (2 * PI / count) * i;
    Vector2 vel = {cosf(angle) * baseSpeed, sinf(angle) * baseSpeed};
    bullets.emplace_back(pos, vel, 5, true, BulletType::NORMAL);
  }
}

void Enemy::SpawnLine(Vector2 pos, std::vector<Bullet>& bullets) {
  int count = 5;
  float angle = atan2(GetScreenHeight() / 2 - pos.y,
                      GetScreenWidth() / 2 - pos.x);  // летят к центру
  for (int i = 0; i < count; ++i) {
    float offset = (i - count / 2) * 10.0f;  // смещение по перпендикуляру
    float perpAngle = angle + PI / 2;
    Vector2 dir = {cosf(angle), sinf(angle)};
    Vector2 perp = {cosf(perpAngle), sinf(perpAngle)};
    Vector2 startPos = {pos.x + perp.x * offset, pos.y + perp.y * offset};
    Vector2 vel = {dir.x * 4.0f, dir.y * 4.0f};
    bullets.emplace_back(startPos, vel, 5, true, NORMAL);
  }
}

void Enemy::SpawnRandom(Vector2 pos, std::vector<Bullet>& bullets) {
  int count = 10;
  for (int i = 0; i < count; ++i) {
    float angle = GetRandomValue(0, 360) * DEG2RAD;
    float speed = GetRandomValue(1, 4);
    Vector2 vel = {cosf(angle) * speed, sinf(angle) * speed};
    bullets.emplace_back(pos, vel, 5, true, BulletType::NORMAL);
  }
}
void Enemy::SpawnVortex(std::vector<Bullet>& bullets) {
  // Создаём вихрь: центр движется в случайном направлении
  float angle = GetRandomValue(0, 360) * DEG2RAD;
  float speed = 2.0f;
  Vector2 vel = {cosf(angle) * speed, sinf(angle) * speed};
  // Количество спутников, радиус орбиты, скорость вращения
  int satelliteCount = 6;
  float orbitRadius = 30.0f;
  float orbitSpeed = 3.0f;  // радиан в секунду
  Bullet vortex(pos, vel, 10, true, satelliteCount, orbitRadius, orbitSpeed);
  bullets.push_back(vortex);
}

void Enemy::Update(std::vector<Bullet>& bullets) {
  if (!active) return;
  // Движение
  pos.x += velocity.x * GetFrameTime() * 60;
  pos.y += velocity.y * GetFrameTime() * 60;
  if (pos.y > GetScreenHeight() + 50) {
    active = false;
    return;
  }
  if (type == VORTEX_ENEMY) {
    shootTimer -= GetFrameTime();
    if (shootTimer <= 0) {
      shootTimer = shootInterval;
      switch (currentPattern) {
        case PATTERN_FLOWER:
          SpawnFlower(pos, bullets);
          break;
        case PATTERN_LINE:
          SpawnLine(pos, bullets);
          break;
        case PATTERN_RANDOM:
          SpawnRandom(pos, bullets);
          break;
        case PATTERN_VORTEX:
          SpawnVortex(bullets);
          break;
      }
    }
  }
}

void Enemy::TakeDamage(int damage) {
  health -= damage;
  if (health <= 0) {
    active = false;
  }
}

void Enemy::OnDeath(std::vector<Bullet>& bullets) {
  if (type == ASTEROID_ENEMY) {
    // 8 пуль во все стороны
    for (int i = 0; i < 8; ++i) {
      float angle = (2 * PI / 8) * i;
      Vector2 vel = {cosf(angle) * 3.0f, sinf(angle) * 3.0f};
      bullets.emplace_back(pos, vel, 5, true, NORMAL);
    }
  } else if (type == VORTEX_ENEMY) {
    // 4 пули с небольшим разбросом
    for (int i = 0; i < 4; ++i) {
      float angle = (2 * PI / 4) * i + GetRandomValue(0, 30) * DEG2RAD;
      Vector2 vel = {cosf(angle) * 2.0f, sinf(angle) * 2.0f};
      bullets.emplace_back(pos, vel, 4, true, NORMAL);
    }
  }
}

void Enemy::Draw() const {
  if (!active) return;
  if (texture.id > 0) {
    Vector2 origin = {texture.width / 2.0f, texture.height / 2.0f};
    Vector2 drawPos = {pos.x - origin.x, pos.y - origin.y};
    DrawTextureV(texture, drawPos, WHITE);
  } else {
    // Fallback – круги (на случай, если текстура не загружена)
    Color color = (type == VORTEX_ENEMY) ? ORANGE : BROWN;
    DrawCircleV(pos, radius, color);
    DrawCircleLines(pos.x, pos.y, radius, WHITE);
  }
}