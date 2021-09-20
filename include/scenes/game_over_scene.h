#ifndef INCLUDE_SCENES_GAME_OVER_SCENE_H_
#define INCLUDE_SCENES_GAME_OVER_SCENE_H_

#include "../include/controls.h"
#include "../include/scenes/i_scene.h"

class GameOverScene : public IScene {
  const Controls& controls_;

 public:
  GameOverScene(Context* ctx, const Controls& controls);
  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SCENES_GAME_OVER_SCENE_H_
