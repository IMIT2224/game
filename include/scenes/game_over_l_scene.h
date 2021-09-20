#ifndef INCLUDE_SCENES_GAME_OVER_L_SCENE_H_
#define INCLUDE_SCENES_GAME_OVER_L_SCENE_H_

#include "../include/controls.h"
#include "../include/scenes/i_scene.h"

class GameOverLScene : public IScene {
  const Controls& controls_;

 public:
  GameOverLScene(Context* ctx, const Controls& controls);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SCENES_GAME_OVER_L_SCENE_H_
