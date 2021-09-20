#ifndef INCLUDE_COMPONENTS_DAMAGE_COMPONENT_H_
#define INCLUDE_COMPONENTS_DAMAGE_COMPONENT_H_
#include "../include/ecs/components.h"

class DamageComponent : public IComponent {
 public:
  int damage_;

  explicit DamageComponent(int damage) : damage_(damage) {}
};
#endif  // INCLUDE_COMPONENTS_DAMAGE_COMPONENT_H_
