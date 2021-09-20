#ifndef INCLUDE_SCENES_GAME_SCENE_H_
#define INCLUDE_SCENES_GAME_SCENE_H_

#include <string>
#include <vector>

#include "../include/controls.h"
#include "../include/ecs/engine.h"
#include "../include/scenes/i_scene.h"

class GameScene : public IScene {
  const int width_ = 80 - 1;
  const int height_ = 24;
  const int menu_ground = 3;
  const int start_health = 100;
  const Engine engine{};
  const Controls& controls;
  const int max_step = 1500;
  const int damage = 25;
  const int reward = 10;
  const int medkit = 50;
  int x = 20;
  int y = 15;
  bool flag = true;

 public:
  GameScene(Context* const ctx, const Controls& controls);

  void Update();
  bool Check_en(int& n);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SCENES_GAME_SCENE_H_
