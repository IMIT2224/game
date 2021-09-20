#ifndef INCLUDE_COMPONENTS_COLOR_COMPONENT_H_
#define INCLUDE_COMPONENTS_COLOR_COMPONENT_H_
#include <string>

#include "../include/ecs/components.h"

class ColorComponent : public IComponent {
 public:
  std::string color_;

  explicit ColorComponent(std::string color) : color_(color) {}
};
#endif  // INCLUDE_COMPONENTS_COLOR_COMPONENT_H_
