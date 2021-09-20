#ifndef INCLUDE_COMPONENTS_REWARD_COMPONENT_H_
#define INCLUDE_COMPONENTS_REWARD_COMPONENT_H_
#include "../include/ecs/components.h"

class RewardComponent : public IComponent {
 public:
  int reward_;

  explicit RewardComponent(int reward) : reward_(reward) {}
};
#endif  // INCLUDE_COMPONENTS_REWARD_COMPONENT_H_
