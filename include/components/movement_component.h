//
// Created by s on 11.07.2021.
//

#ifndef INCLUDE_COMPONENTS_MOVEMENT_COMPONENT_H_
#define INCLUDE_COMPONENTS_MOVEMENT_COMPONENT_H_
#include "../include/ecs/components.h"

class MovementComponent : public IComponent {
 public:
  int old_x;
  int old_y;
};
#endif  // INCLUDE_COMPONENTS_MOVEMENT_COMPONENT_H_
