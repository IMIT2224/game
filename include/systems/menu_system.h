//
// Created by s on 11.07.2021.
//

#ifndef INCLUDE_SYSTEMS_MENU_SYSTEM_H_
#define INCLUDE_SYSTEMS_MENU_SYSTEM_H_

#include "../include/ecs/system.h"

class MenuSystem : public ISystem {
  int money = 0;
  int health = 0;
  int total_steps = 0;
  const int max_steps_;
  const EntityManager* entity_manager_;

 public:
  MenuSystem(EntityManager* entity_manager, SystemManager* system_manager, const int max_step);
  void Render_menu();

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_SYSTEMS_MENU_SYSTEM_H_
