#include "../include/ecs/system.h"
#include "../include/scenes/scene_manager.h"

#ifndef INCLUDE_SYSTEMS_COLLISION_MANAGER_SYSTEM_H_
#define INCLUDE_SYSTEMS_COLLISION_MANAGER_SYSTEM_H_

class CollisionManagerSystem : public ISystem {
  EntityManager* const entity_manager_;
  Context* const ctx_;

 public:
  CollisionManagerSystem(EntityManager* entity_manager, SystemManager* system_manager, Context* const ctx);

 protected:
  void OnUpdate() override;
};

#endif  // INCLUDE_SYSTEMS_COLLISION_MANAGER_SYSTEM_H_
