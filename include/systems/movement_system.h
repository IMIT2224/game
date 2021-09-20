//
// Created by s on 11.07.2021.
//

#ifndef INCLUDE_SYSTEMS_MOVEMENT_SYSTEM_H_
#define INCLUDE_SYSTEMS_MOVEMENT_SYSTEM_H_

#include "../include/controls.h"
#include "../include/ecs/system.h"

class MovementSystem : public ISystem {
 public:
  const Controls& controls;
  MovementSystem(EntityManager* entity_manager, SystemManager* system_manager, const Controls& controls);

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_SYSTEMS_MOVEMENT_SYSTEM_H_
