#ifndef INCLUDE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_
#define INCLUDE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_

#include "../include/ecs/components.h"

class PlayerControlComponent : public IComponent {
 public:
  int left_;
  int right_;
  int up_;
  int down_;

  explicit PlayerControlComponent(int left, int right, int up, int down)
      : left_(left), right_(right), up_(up), down_(down) {}
};

#endif  // INCLUDE_COMPONENTS_PLAYER_CONTROL_COMPONENT_H_
