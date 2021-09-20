#include "../include/ecs/system.h"
#include "../include/scenes/scene_manager.h"

#ifndef INCLUDE_SYSTEMS_AI_CONTROL_SYSTEM_H_
#define INCLUDE_SYSTEMS_AI_CONTROL_SYSTEM_H_

class AIControlSystem : public ISystem {
  EntityManager* const entity_manager_;

 public:
  int64_t i = 0;
  int player_pos_x = -1;
  int player_pos_y = -1;
  AIControlSystem(EntityManager* entity_manager, SystemManager* system_manager);

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_SYSTEMS_AI_CONTROL_SYSTEM_H_
