//
// Created by s on 11.07.2021.
//
#ifndef INCLUDE_GRID_COLLISION_H_
#define INCLUDE_GRID_COLLISION_H_

#include "../include/components/damage_component.h"
#include "../include/components/enemy_component.h"
#include "../include/components/grid_component.h"
#include "../include/components/player_component.h"
#include "../include/components/player_control_component.h"
#include "../include/components/texture_component.h"
#include "../include/components/transform_component.h"
#include "../include/ecs/entity_manager.h"

class GridCollision {
 public:
  GridCollision() = default;
  ~GridCollision() = default;

  static bool Collide(const Entity& entity_1, const Entity& entity_2) {
    if (entity_1.GetId() == entity_2.GetId()) {
      return false;
    }

    auto tc1 = entity_1.Get<TransformComponent>();
    auto tc2 = entity_2.Get<TransformComponent>();

    if (tc1->x_ == tc2->x_ && tc1->y_ == tc2->y_) {
      if ((entity_1.Contains<GridComponent>() || entity_2.Contains<GridComponent>()) &&
          (entity_1.Contains<PlayerComponent>() || entity_2.Contains<PlayerComponent>())) {
        return true;
      }
    }
    return false;
  }

  static bool Collide_e(const Entity& entity_1, const Entity& entity_2) {
    if (entity_1.GetId() == entity_2.GetId()) {
      return false;
    }

    auto tc1 = entity_1.Get<TransformComponent>();
    auto tc2 = entity_2.Get<TransformComponent>();

    if (tc1->x_ == tc2->x_ && tc1->y_ == tc2->y_) {
      if ((entity_1.Contains<GridComponent>() || entity_2.Contains<GridComponent>()) &&
          (entity_1.Contains<EnemyComponent>() || entity_2.Contains<EnemyComponent>())) {
        return true;
      }
    }
    return false;
  }

  bool check(EntityManager& t) {
    for (auto& entity_1 : t) {
      if (entity_1.Contains<PlayerControlComponent>()) {
        for (auto& entity_2 : t) {
          if (Collide(entity_1, entity_2)) {
            return true;
          }
        }
      }
    }
    return false;
  }

  bool check_e(EntityManager& t) {
    for (auto& entity_1 : t) {
      if (entity_1.Contains<DamageComponent>()) {
        for (auto& entity_2 : t) {
          if (Collide_e(entity_1, entity_2)) {
            return true;
          }
        }
      }
    }
    return false;
  }
};

#endif  // INCLUDE_GRID_COLLISION_H_
