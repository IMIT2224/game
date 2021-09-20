#ifndef INCLUDE_COMPONENTS_TRANSFORM_COMPONENT_H_
#define INCLUDE_COMPONENTS_TRANSFORM_COMPONENT_H_
#include "../include/ecs/components.h"

class TransformComponent : public IComponent {
 public:
  int x_;
  int y_;

  explicit TransformComponent(int x, int y) : x_(x), y_(y) {}
};
#endif  // INCLUDE_COMPONENTS_TRANSFORM_COMPONENT_H_
