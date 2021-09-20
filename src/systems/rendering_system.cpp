#include "../include/systems/rendering_system.h"

#include <BearLibTerminal.h>

#include <string>

#include "../include/components/color_component.h"
#include "../include/components/enemy_component.h"
#include "../include/components/graphic_component.h"
#include "../include/components/player_component.h"
#include "../include/components/texture_component.h"
#include "../include/components/transform_component.h"
#include "../include/ecs/entity_manager.h"

static std::string to_str(char c) {
  std::string s = "";
  s += c;
  return s;
}

void RenderingSystem::OnUpdate() {
  for (int i = 4; i < 25; i++) {
    for (int j = 0; j < 80; j++) {
      terminal_printf(j, i, "[color=#946f6f].");
    }
  }
  for (auto& e : GetEntityManager()) {
    if (e.Contains<TransformComponent>() && e.Contains<TextureComponent>() && e.Contains<GraphicComponent>()) {
      auto transform = e.Get<TransformComponent>();
      if (e.Get<GraphicComponent>()->flag) {
        terminal_put(transform->x_, transform->y_, e.Get<GraphicComponent>()->code_);
      } else {
        terminal_printf(
            transform->x_, transform->y_,
            ("[color=" + e.Get<ColorComponent>()->color_ + "]" + to_str(e.Get<TextureComponent>()->symbol_)).c_str());
      }
    }
  }

  for (auto& e : GetEntityManager()) {
    if (e.Contains<EnemyComponent>()) {
      auto transform = e.Get<TransformComponent>();
      if (e.Get<GraphicComponent>()->flag) {
        terminal_put(transform->x_, transform->y_, e.Get<GraphicComponent>()->code_);
      } else {
        terminal_printf(
            transform->x_, transform->y_,
            ("[color=" + e.Get<ColorComponent>()->color_ + "]" + to_str(e.Get<TextureComponent>()->symbol_)).c_str());
      }
    } else if (e.Contains<PlayerComponent>()) {
      auto transform = e.Get<TransformComponent>();
      if (e.Get<GraphicComponent>()->flag) {
        terminal_put(transform->x_, transform->y_, e.Get<GraphicComponent>()->code_);
      } else {
        terminal_printf(
            transform->x_, transform->y_,
            ("[color=" + e.Get<ColorComponent>()->color_ + "]" + to_str(e.Get<TextureComponent>()->symbol_)).c_str());
      }
    }
  }
}
void RenderingSystem::OnPreUpdate() {
  terminal_clear();
}
void RenderingSystem::OnPostUpdate() {
  terminal_refresh();
}
RenderingSystem::RenderingSystem(EntityManager* const entity_manager, SystemManager* const system_manager)
    : ISystem(entity_manager, system_manager) {}
