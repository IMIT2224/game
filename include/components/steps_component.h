#ifndef INCLUDE_COMPONENTS_STEPS_COMPONENT_H_
#define INCLUDE_COMPONENTS_STEPS_COMPONENT_H_
#include "../include/ecs/components.h"

class StepsComponent : public IComponent {
 public:
  int steps_;

  explicit StepsComponent(int steps) : steps_(steps) {}
};
#endif  // INCLUDE_COMPONENTS_STEPS_COMPONENT_H_
