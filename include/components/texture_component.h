#ifndef INCLUDE_COMPONENTS_TEXTURE_COMPONENT_H_
#define INCLUDE_COMPONENTS_TEXTURE_COMPONENT_H_
#include "../include/ecs/components.h"

class TextureComponent : public IComponent {
 public:
  char symbol_;

  explicit TextureComponent(char symbol) : symbol_(symbol) {}
};
#endif  // INCLUDE_COMPONENTS_TEXTURE_COMPONENT_H_
