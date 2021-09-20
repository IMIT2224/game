#include "../include/systems/menu_system.h"

#include <BearLibTerminal.h>

#include <string>

#include "../include/components/health_component.h"
#include "../include/components/money_component.h"
#include "../include/components/player_component.h"
#include "../include/components/steps_component.h"
#include "../include/ecs/entity_manager.h"

MenuSystem::MenuSystem(EntityManager* const entity_manager, SystemManager* const system_manager, const int max_step)
    : ISystem(entity_manager, system_manager), max_steps_(max_step), entity_manager_(entity_manager) {}

void MenuSystem::Render_menu() {
  std::string msg1 = "[color=#15e537]MONEY: " + std::to_string(money);
  std::string msg2 = "[color=#15e537]HEALTH: " + std::to_string(health);
  std::string msg3 = "[color=#15e537]TOTAL STEPS: " + std::to_string(total_steps);
  std::string msg4 = "[color=#15e537]MAX STEPS: " + std::to_string(max_steps_);

  terminal_printf(1, 1, msg1.c_str());
  terminal_printf(34, 1, msg3.c_str());
  terminal_printf(1, 2, msg2.c_str());
  terminal_printf(34, 2, msg4.c_str());
}

void MenuSystem::OnUpdate() {
  int ind = 2;
  money = 0;
  health = 0;
  total_steps = 0;

  while (true) {
    if (entity_manager_->Get(ind) != nullptr && entity_manager_->Get(ind)->Contains<PlayerComponent>()) {
      money = entity_manager_->Get(ind)->Get<MoneyComponent>()->value_;
      health = entity_manager_->Get(ind)->Get<HealthComponent>()->health_;
      total_steps = entity_manager_->Get(ind)->Get<StepsComponent>()->steps_;
      break;
    }
    ind++;
  }

  Render_menu();
}
