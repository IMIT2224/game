#ifndef INCLUDE_SYSTEMS_RENDERING_SYSTEM_H_
#define INCLUDE_SYSTEMS_RENDERING_SYSTEM_H_

#include "../include/ecs/system.h"

class RenderingSystem : public ISystem {
 protected:
  void OnPreUpdate() override;
  void OnUpdate() override;
  void OnPostUpdate() override;

 public:
  RenderingSystem(EntityManager* entity_manager, SystemManager* system_manager);
};

#endif  // INCLUDE_SYSTEMS_RENDERING_SYSTEM_H_
