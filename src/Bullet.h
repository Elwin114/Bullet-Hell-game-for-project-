#pragma once
#include <cstddef>
#include <vector>

#include "raylib.h"

enum BulletType {
  NORMAL,    // красные обычные
  ASTEROID,  // астероид
  VORTEX
};

class Bullet {
 public:
  Vector2 pos;
  Vector2 vel;
  float radius;
  bool active;  // true – пуля жива, false – можно удалить
  BulletType type;
  int damage;
  bool isEnemy;  // true – вражеская, false – игрока

  std::vector<Bullet> satellites;  // спутники, вращающиеся вокруг центра
  float orbitRadius;
  float orbitSpeed;
  float angle;

  Bullet();
  Bullet(Vector2 position, Vector2 velocity, float radius, bool enemy,
         BulletType type = NORMAL);

  Bullet(Vector2 position, Vector2 velocity, float radius, bool enemy,
         int satelliteCount, float orbitRadius, float orbitSpeed);  // Вихри

  void Update();
  void Draw() const;
};