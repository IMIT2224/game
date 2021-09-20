#include "../include/systems/ai_control_system.h"

#include <cmath>
#include <vector>

#include "../include/components/ai_control_component.h"
#include "../include/components/transform_component.h"
#include "../include/ecs/entity.h"
#include "../include/ecs/entity_manager.h"
#include "../include/grid_collision.h"

AIControlSystem::AIControlSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager), entity_manager_(entity_manager) {}

static int check_min(std::vector<double> v) {
  int ind = 0;
  int res = -1;
  double max_distance = 1000000;
  for (auto& i : v) {
    if (i < max_distance) {
      res = ind;
      max_distance = i;
    }
    ind += 1;
  }
  return res;
}

void AIControlSystem::OnUpdate() {
  for (auto& player : GetEntityManager()) {
    if (player.Contains<PlayerComponent>()) {
      int player_x = player.Get<TransformComponent>()->x_;
      int player_y = player.Get<TransformComponent>()->y_;
      if ((player_x != player_pos_x || player_y != player_pos_y)) {
        i++;
        player_pos_x = player_x;
        player_pos_y = player_y;
        // std::cout << i << std::endl;
        if (i % 2 == 0) {
          for (auto& entity_t : GetEntityManager()) {
            if (entity_t.Contains<AIControlComponent>()) {
              int temp_x = entity_t.Get<TransformComponent>()->x_;
              int temp_y = entity_t.Get<TransformComponent>()->y_;

              double no = sqrt((player_x - temp_x) * (player_x - temp_x) + (player_y - temp_y) * (player_y - temp_y));
              double up = sqrt((player_x - temp_x) * (player_x - temp_x) +
                               (player_y - (temp_y - 1)) * (player_y - (temp_y - 1)));
              double down = sqrt((player_x - temp_x) * (player_x - temp_x) +
                                 (player_y - (temp_y + 1)) * (player_y - (temp_y + 1)));
              double left = sqrt((player_x - (temp_x - 1)) * (player_x - (temp_x - 1)) +
                                 (player_y - temp_y) * (player_y - temp_y));
              double right = sqrt((player_x - (temp_x + 1)) * (player_x - (temp_x + 1)) +
                                  (player_y - temp_y) * (player_y - temp_y));
              std::vector<double> go = {no, up, down, left, right};
              int result = check_min(go);
              // std::cout << no << " " << up << " " << down << " " << left << " " << right << std::endl;
              // std::cout << result << std::endl;
              if (result == 1) {
                entity_t.Get<TransformComponent>()->y_ = entity_t.Get<TransformComponent>()->y_ - 1;
              } else if (result == 2) {
                entity_t.Get<TransformComponent>()->y_ = entity_t.Get<TransformComponent>()->y_ + 1;
              } else if (result == 3) {
                entity_t.Get<TransformComponent>()->x_ = entity_t.Get<TransformComponent>()->x_ - 1;
              } else if (result == 4) {
                entity_t.Get<TransformComponent>()->x_ = entity_t.Get<TransformComponent>()->x_ + 1;
              }
              EntityManager& t = GetEntityManager();
              GridCollision gcs;
              if (gcs.check_e(t)) {
                // std::cout << "NO" << std::endl;
                entity_t.Get<TransformComponent>()->x_ = temp_x;
                entity_t.Get<TransformComponent>()->y_ = temp_y;
              }
            }
          }
        }
      }
    }
  }
}
