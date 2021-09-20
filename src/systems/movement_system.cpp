#include "../include/systems/movement_system.h"

#include "../include/components/health_component.h"
#include "../include/components/movement_component.h"
#include "../include/components/player_control_component.h"
#include "../include/components/steps_component.h"
#include "../include/components/texture_component.h"
#include "../include/components/transform_component.h"
#include "../include/ecs/entity_manager.h"
#include "../include/grid_collision.h"

MovementSystem::MovementSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                               const Controls& controls)
    : ISystem(entity_manager, system_manager), controls(controls) {}
void MovementSystem::OnUpdate() {
  for (auto& entity : GetEntityManager()) {
    if (entity.Contains<MovementComponent>() && entity.Contains<PlayerControlComponent>()) {
      auto tc = entity.Get<PlayerControlComponent>();
      auto pc = entity.Get<TransformComponent>();
      auto mc = entity.Get<MovementComponent>();
      auto hc = entity.Get<HealthComponent>();
      auto sc = entity.Get<StepsComponent>();
      mc->old_x = pc->x_;
      mc->old_y = pc->y_;
      EntityManager& t = GetEntityManager();
      GridCollision gcs;
      if (controls.IsPressed(tc->up_)) {
        pc->y_ -= 1;
        hc->Step();
        sc->steps_ = sc->steps_ + 1;
        if (gcs.check(t)) {
          pc->x_ = mc->old_x;
          pc->y_ = mc->old_y;
          hc->health_ = hc->health_ + 1;
          sc->steps_ = sc->steps_ - 1;
        }
      } else if (controls.IsPressed(tc->down_)) {
        pc->y_ += 1;
        hc->Step();
        sc->steps_ = sc->steps_ + 1;
        if (gcs.check(t)) {
          pc->x_ = mc->old_x;
          pc->y_ = mc->old_y;
          hc->health_ = hc->health_ + 1;
          sc->steps_ = sc->steps_ - 1;
        }
      } else if (controls.IsPressed(tc->left_)) {
        pc->x_ -= 1;
        hc->Step();
        sc->steps_ = sc->steps_ + 1;
        if (gcs.check(t)) {
          pc->x_ = mc->old_x;
          pc->y_ = mc->old_y;
          hc->health_ = hc->health_ + 1;
          sc->steps_ = sc->steps_ - 1;
        }
      } else if (controls.IsPressed(tc->right_)) {
        pc->x_ += 1;
        hc->Step();
        sc->steps_ = sc->steps_ + 1;
        if (gcs.check(t)) {
          pc->x_ = mc->old_x;
          pc->y_ = mc->old_y;
          hc->health_ = hc->health_ + 1;
          sc->steps_ = sc->steps_ - 1;
        }
      }
    }
  }
}
