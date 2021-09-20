#ifndef INCLUDE_COMPONENTS_HEALTH_COMPONENT_H_
#define INCLUDE_COMPONENTS_HEALTH_COMPONENT_H_
#include "../include/ecs/components.h"

class HealthComponent : public IComponent {
 public:
  int health_;
  void Set_health(int n) {
    health_ += n;
  }
  void Step() {
    health_--;
  }
  explicit HealthComponent(int health) : health_(health) {}
};
#endif  // INCLUDE_COMPONENTS_HEALTH_COMPONENT_H_
