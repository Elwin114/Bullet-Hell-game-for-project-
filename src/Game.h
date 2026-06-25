#pragma once
#include <algorithm>  // для std::remove_if
#include <vector>

#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "raylib.h"

class Game {
 public:
  Player player;
  std::vector<Bullet> bullets;
  std::vector<Enemy> enemies;
  float enemySpawnTimer;
  float enemySpawnInterval;
  float asteroidSpawnTimer;
  float asteroidSpawnInterval;
  float patternSpawnTimer;
  float patternSpawnInterval;
  Texture2D playerTex;
  Texture2D asteroidTex;
  Texture2D vortexTex;

  Game(Texture2D pTex, Texture2D aTex, Texture2D vTex);
  void Update();
  void Draw();
  void CheckCollisions();
};