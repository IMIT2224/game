#ifndef INCLUDE_COMPONENTS_GRAPHIC_COMPONENT_H_
#define INCLUDE_COMPONENTS_GRAPHIC_COMPONENT_H_
#include "../include/ecs/components.h"

class GraphicComponent : public IComponent {
 public:
  int code_;
  bool flag = false;

  explicit GraphicComponent(int code) : code_(code) {}
};
#endif  // INCLUDE_COMPONENTS_GRAPHIC_COMPONENT_H_
