#ifndef INCLUDE_COMPONENTS_ENEMY_COMPONENT_H_
#define INCLUDE_COMPONENTS_ENEMY_COMPONENT_H_

#include "../include/ecs/components.h"

class EnemyComponent : public IComponent {
 public:
  int en_id_;
  explicit EnemyComponent(int en_id) : en_id_(en_id) {}
};

#endif  // INCLUDE_COMPONENTS_ENEMY_COMPONENT_H_
