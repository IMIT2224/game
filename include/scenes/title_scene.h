#ifndef INCLUDE_SCENES_TITLE_SCENE_H_
#define INCLUDE_SCENES_TITLE_SCENE_H_

#include "../include/controls.h"
#include "../include/scenes/i_scene.h"

class TitleScene : public IScene {
  const Controls& controls_;

 public:
  TitleScene(Context* ctx, const Controls& controls);

  void OnCreate() override;
  void OnRender() override;
  void OnExit() override;
};

#endif  // INCLUDE_SCENES_TITLE_SCENE_H_
