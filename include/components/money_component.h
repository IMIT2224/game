#ifndef INCLUDE_COMPONENTS_MONEY_COMPONENT_H_
#define INCLUDE_COMPONENTS_MONEY_COMPONENT_H_
#include "../include/ecs/components.h"

class MoneyComponent : public IComponent {
 public:
  int value_;
  void Set_value(int n) {
    value_ += n;
  }
  explicit MoneyComponent(int total) : value_(total) {}
};
#endif  // INCLUDE_COMPONENTS_MONEY_COMPONENT_H_
