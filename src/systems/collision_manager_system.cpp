//
// Created by s on 11.07.2021.
//

#include "systems/collision_manager_system.h"

#include <iostream>
#include <string>
#include <thread>

#include "../include/components/ai_control_component.h"
#include "../include/components/audio_component.h"
#include "../include/components/back_portal_component.h"
#include "../include/components/coin_component.h"
#include "../include/components/damage_component.h"
#include "../include/components/enemy_component.h"
#include "../include/components/grid_component.h"
#include "../include/components/health_component.h"
#include "../include/components/key_component.h"
#include "../include/components/med_component.h"
#include "../include/components/medkit_component.h"
#include "../include/components/money_component.h"
#include "../include/components/player_component.h"
#include "../include/components/portal_component.h"
#include "../include/components/reward_component.h"
#include "../include/components/transform_component.h"
#include "../include/ecs/entity.h"
#include "../include/ecs/entity_manager.h"

static void ff(std::string name) {
  std::string msg = "python3 audio.py " + name + " > log.txt";
  system(msg.c_str());
}

static bool Collide(Entity* entity_1, Entity* entity_2) {
  if (entity_1->GetId() == entity_2->GetId()) {
    return false;
  }

  auto tc1 = entity_1->Get<TransformComponent>();
  auto tc2 = entity_2->Get<TransformComponent>();

  if (tc1->x_ == tc2->x_ && tc1->y_ == tc2->y_) {
    return true;
  }
  return false;
}

CollisionManagerSystem::CollisionManagerSystem(EntityManager* const entity_manager, SystemManager* const system_manager,
                                               Context* const ctx)
    : ISystem(entity_manager, system_manager), entity_manager_(entity_manager), ctx_(ctx) {}

void CollisionManagerSystem::OnUpdate() {
  for (auto& entity_1 : GetEntityManager()) {
    for (auto& entity_2 : GetEntityManager()) {
      if (Collide(&entity_1, &entity_2)) {
        // Money
        if ((entity_1.Contains<CoinComponent>() && entity_2.Contains<PlayerComponent>()) ||
            (entity_2.Contains<CoinComponent>() && entity_1.Contains<PlayerComponent>())) {
          if (entity_1.Contains<CoinComponent>()) {
            std::thread th(ff, entity_1.Get<AudioComponent>()->file_name_);
            th.detach();
            entity_2.Get<MoneyComponent>()->Set_value(entity_1.Get<RewardComponent>()->reward_);
            int temp_x = entity_1.Get<TransformComponent>()->x_;
            int temp_y = entity_1.Get<TransformComponent>()->y_;
            ctx_->data_level[ctx_->real_level - 1].push_back({temp_x, temp_y});
            entity_manager_->DeleteEntity(entity_1.GetId());
          } else {
            std::thread th(ff, entity_2.Get<AudioComponent>()->file_name_);
            th.detach();
            entity_1.Get<MoneyComponent>()->Set_value(entity_2.Get<RewardComponent>()->reward_);
            int temp_x = entity_2.Get<TransformComponent>()->x_;
            int temp_y = entity_2.Get<TransformComponent>()->y_;
            ctx_->data_level[ctx_->real_level - 1].push_back({temp_x, temp_y});
            entity_manager_->DeleteEntity(entity_2.GetId());
          }
        }
        // Health
        else if ((entity_1.Contains<MedComponent>() && entity_2.Contains<PlayerComponent>()) ||
                 (entity_2.Contains<MedComponent>() && entity_1.Contains<PlayerComponent>())) {
          if (entity_1.Contains<MedComponent>()) {
            std::thread th(ff, entity_1.Get<AudioComponent>()->file_name_);
            th.detach();
            entity_2.Get<HealthComponent>()->Set_health(entity_1.Get<MedkitComponent>()->health_);
            int temp_x = entity_1.Get<TransformComponent>()->x_;
            int temp_y = entity_1.Get<TransformComponent>()->y_;
            ctx_->data_level[ctx_->real_level - 1].push_back({temp_x, temp_y});
            entity_manager_->DeleteEntity(entity_1.GetId());
          } else {
            std::thread th(ff, entity_2.Get<AudioComponent>()->file_name_);
            th.detach();
            entity_1.Get<HealthComponent>()->Set_health(entity_2.Get<MedkitComponent>()->health_);
            int temp_x = entity_2.Get<TransformComponent>()->x_;
            int temp_y = entity_2.Get<TransformComponent>()->y_;
            ctx_->data_level[ctx_->real_level - 1].push_back({temp_x, temp_y});
            entity_manager_->DeleteEntity(entity_2.GetId());
          }
        }  // KEY
        else if ((entity_1.Contains<KeyComponent>() && entity_2.Contains<PlayerComponent>()) ||
                 (entity_2.Contains<KeyComponent>() && entity_1.Contains<PlayerComponent>())) {
          if (entity_1.Contains<KeyComponent>()) {
            std::thread th(ff, entity_1.Get<AudioComponent>()->file_name_);
            th.detach();
            ctx_->key_flag[ctx_->real_level - 1] = true;
            int temp_x = entity_1.Get<TransformComponent>()->x_;
            int temp_y = entity_1.Get<TransformComponent>()->y_;
            ctx_->data_level[ctx_->real_level - 1].push_back({temp_x, temp_y});
            entity_manager_->DeleteEntity(entity_1.GetId());
          } else {
            std::thread th(ff, entity_2.Get<AudioComponent>()->file_name_);
            th.detach();
            ctx_->key_flag[ctx_->real_level - 1] = true;
            int temp_x = entity_2.Get<TransformComponent>()->x_;
            int temp_y = entity_2.Get<TransformComponent>()->y_;
            ctx_->data_level[ctx_->real_level - 1].push_back({temp_x, temp_y});
            entity_manager_->DeleteEntity(entity_2.GetId());
          }
        }
        //  Portal
        else if (((entity_1.Contains<PortalComponent>() && entity_2.Contains<PlayerComponent>()) ||
                  (entity_2.Contains<PortalComponent>() && entity_1.Contains<PlayerComponent>())) &&
                 ctx_->key_flag[ctx_->real_level - 1]) {
          if (entity_1.Contains<PortalComponent>()) {
            std::thread th(ff, entity_1.Get<AudioComponent>()->file_name_);
            th.detach();
            ctx_->enemy_cor[ctx_->real_level - 1] = {};
            for (auto& ind : GetEntityManager()) {
              if (ind.Contains<EnemyComponent>()) {
                ctx_->enemy_cor[ctx_->real_level - 1].push_back(
                    {ind.Get<TransformComponent>()->x_, ind.Get<TransformComponent>()->y_});
              }
            }
            ctx_->isUP = true;
            ctx_->real_level = ctx_->real_level + 1;
            ctx_->scene_ = "game_" + std::to_string(ctx_->real_level);
            entity_manager_->DeleteEntity(entity_1.GetId());
          } else {
            std::thread th(ff, entity_2.Get<AudioComponent>()->file_name_);
            th.detach();
            ctx_->enemy_cor[ctx_->real_level - 1] = {};
            for (auto& ind : GetEntityManager()) {
              if (ind.Contains<EnemyComponent>()) {
                ctx_->enemy_cor[ctx_->real_level - 1].push_back(
                    {ind.Get<TransformComponent>()->x_, ind.Get<TransformComponent>()->y_});
              }
            }
            ctx_->isUP = true;
            ctx_->real_level = ctx_->real_level + 1;
            ctx_->scene_ = "game_" + std::to_string(ctx_->real_level);
            entity_manager_->DeleteEntity(entity_2.GetId());
          }
        }

        // Back Portal
        else if ((entity_1.Contains<BackPortalComponent>() && entity_2.Contains<PlayerComponent>()) ||
                 (entity_2.Contains<BackPortalComponent>() && entity_1.Contains<PlayerComponent>())) {
          if (entity_1.Contains<BackPortalComponent>()) {
            std::thread th(ff, entity_1.Get<AudioComponent>()->file_name_);
            th.detach();
            ctx_->enemy_cor[ctx_->real_level - 1] = {};
            for (auto& ind : GetEntityManager()) {
              if (ind.Contains<EnemyComponent>()) {
                ctx_->enemy_cor[ctx_->real_level - 1].push_back(
                    {ind.Get<TransformComponent>()->x_, ind.Get<TransformComponent>()->y_});
              }
            }
            ctx_->isUP = false;
            ctx_->real_level = ctx_->real_level - 1;
            ctx_->scene_ = "game_" + std::to_string(ctx_->real_level);
            entity_manager_->DeleteEntity(entity_1.GetId());

          } else {
            std::thread th(ff, entity_2.Get<AudioComponent>()->file_name_);
            th.detach();
            ctx_->enemy_cor[ctx_->real_level - 1] = {};
            for (auto& ind : GetEntityManager()) {
              if (ind.Contains<EnemyComponent>()) {
                ctx_->enemy_cor[ctx_->real_level - 1].push_back(
                    {ind.Get<TransformComponent>()->x_, ind.Get<TransformComponent>()->y_});
              }
            }
            ctx_->isUP = false;
            ctx_->real_level = ctx_->real_level - 1;
            ctx_->scene_ = "game_" + std::to_string(ctx_->real_level);
            entity_manager_->DeleteEntity(entity_2.GetId());
          }
        }
        // Enemy
        else if ((entity_1.Contains<EnemyComponent>() && entity_2.Contains<PlayerComponent>()) ||
                 (entity_2.Contains<EnemyComponent>() && entity_1.Contains<PlayerComponent>())) {
          if (entity_1.Contains<EnemyComponent>()) {
            std::thread th(ff, entity_1.Get<AudioComponent>()->file_name_);
            th.detach();
            entity_2.Get<HealthComponent>()->Set_health(-1 * entity_1.Get<DamageComponent>()->damage_);
            ctx_->enemy_in_level[ctx_->real_level - 1].push_back(entity_1.Get<EnemyComponent>()->en_id_);
            entity_manager_->DeleteEntity(entity_1.GetId());
          } else {
            std::thread th(ff, entity_2.Get<AudioComponent>()->file_name_);
            th.detach();
            entity_1.Get<HealthComponent>()->Set_health(-1 * entity_2.Get<DamageComponent>()->damage_);
            ctx_->enemy_in_level[ctx_->real_level - 1].push_back(entity_2.Get<EnemyComponent>()->en_id_);
            entity_manager_->DeleteEntity(entity_2.GetId());
          }
        }
      }
    }
  }
}
