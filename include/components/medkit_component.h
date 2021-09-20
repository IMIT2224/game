#ifndef INCLUDE_COMPONENTS_MEDKIT_COMPONENT_H_
#define INCLUDE_COMPONENTS_MEDKIT_COMPONENT_H_
#include "../include/ecs/components.h"

class MedkitComponent : public IComponent {
 public:
  int health_;

  explicit MedkitComponent(int health) : health_(health) {}
};
#endif  // INCLUDE_COMPONENTS_MEDKIT_COMPONENT_H_
