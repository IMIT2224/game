// Lib
#include "../include/scenes/game_scene.h"

#include <BearLibTerminal.h>

#include <iostream>
#include <string>

#include "../include/scenes/reader.h"

// Components
#include "../include/components/ai_control_component.h"
#include "../include/components/audio_component.h"
#include "../include/components/back_portal_component.h"
#include "../include/components/coin_component.h"
#include "../include/components/color_component.h"
#include "../include/components/damage_component.h"
#include "../include/components/enemy_component.h"
#include "../include/components/graphic_component.h"
#include "../include/components/grid_component.h"
#include "../include/components/health_component.h"
#include "../include/components/key_component.h"
#include "../include/components/med_component.h"
#include "../include/components/medkit_component.h"
#include "../include/components/money_component.h"
#include "../include/components/movement_component.h"
#include "../include/components/obtacle_component.h"
#include "../include/components/player_component.h"
#include "../include/components/player_control_component.h"
#include "../include/components/portal_component.h"
#include "../include/components/reward_component.h"
#include "../include/components/steps_component.h"
#include "../include/components/texture_component.h"
#include "../include/components/transform_component.h"

// Systems
#include "../include/systems/ai_control_system.h"
#include "../include/systems/collision_manager_system.h"
#include "../include/systems/menu_system.h"
#include "../include/systems/movement_system.h"
#include "../include/systems/rendering_system.h"

void GameScene::Update() {
  int ind = 2;
  int reward__ = 0;
  int health__ = 1;
  int total_steps__ = 0;

  while (true) {
    if (engine.GetEntityManager()->Get(ind) != nullptr &&
        engine.GetEntityManager()->Get(ind)->Contains<PlayerComponent>()) {
      reward__ = engine.GetEntityManager()->Get(ind)->Get<MoneyComponent>()->value_;
      health__ = engine.GetEntityManager()->Get(ind)->Get<HealthComponent>()->health_;
      total_steps__ = engine.GetEntityManager()->Get(ind)->Get<StepsComponent>()->steps_;
      // std::cout << ind << std::endl;
      break;
    }
    ind++;
  }

  ctx_->total_steps = total_steps__;
  ctx_->total_reward = reward__;
  ctx_->total_health = health__;
  if (health__ <= 0 || total_steps__ >= max_step) {
    ctx_->scene_ = "game_over";  // переходим на другую сцену
  }
}

bool GameScene::Check_en(int& n) {
  for (auto& i : ctx_->enemy_in_level[ctx_->real_level - 1]) {
    if ((n) == i) {
      n++;
      return false;
    }
  }
  return true;
}

void GameScene::OnCreate() {
  std::string data;

  reader r;
  r.read_level("scene/scene_" + std::to_string(ctx_->real_level) + ctx_->random + ".txt");
  data = r.Get_level();
  if (data == "-1") {
    std::cout << "[Error] Level no correct!" << std::endl;
  }

  int x_p = 0;
  int y_p = 0;

  for (const auto& i : data) {
    if (i == '@') {  // player желательно объявить первым
      auto player = engine.GetEntityManager()->CreateEntity();
      if (flag) {
        x = x_p;
        y = y_p;
      }
      if (!ctx_->isUP) {
        player->Add<TransformComponent>(x, y);
      } else {
        player->Add<TransformComponent>(x_p, y_p);
      }
      flag = false;
      player->Add<TextureComponent>('@');
      player->Add<MoneyComponent>(ctx_->total_reward);
      player->Add<StepsComponent>(ctx_->total_steps);
      player->Add<HealthComponent>(ctx_->total_health);
      player->Add<MovementComponent>();
      player->Add<PlayerControlComponent>(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN);
      player->Add<PlayerComponent>();
      player->Add<GraphicComponent>(0x1000);
      player->Add<ColorComponent>("#db40de");
      if (ctx_->graphic) {
        player->Get<GraphicComponent>()->flag = true;
      }
    }
    x_p++;
    if (i == ')') {
      x_p = 0;
      y_p++;
    }
  }
  x_p = 0;
  y_p = 0;
  int id_e = 0;
  int f_id_e = 0;
  for (const auto& i : data) {
    if (i == '>') {
      auto portal = engine.GetEntityManager()->CreateEntity();
      portal->Add<TransformComponent>(x_p, y_p);
      portal->Add<TextureComponent>('>');
      portal->Add<PortalComponent>();
      portal->Add<GraphicComponent>(0x1003);
      portal->Add<ColorComponent>("#4d40de");
      portal->Add<AudioComponent>("portal.ogg");
      if (ctx_->graphic) {
        portal->Get<GraphicComponent>()->flag = true;
      }
    } else if (i == '<') {
      auto back_portal = engine.GetEntityManager()->CreateEntity();
      back_portal->Add<TransformComponent>(x_p, y_p);
      back_portal->Add<TextureComponent>('<');
      back_portal->Add<BackPortalComponent>();
      back_portal->Add<GraphicComponent>(0x1004);
      back_portal->Add<ColorComponent>("#4d40de");
      back_portal->Add<AudioComponent>("portal.ogg");
      if (ctx_->graphic) {
        back_portal->Get<GraphicComponent>()->flag = true;
      }
    } else if (i == '#') {
      auto grid = engine.GetEntityManager()->CreateEntity();
      grid->Add<TransformComponent>(x_p, y_p);
      grid->Add<TextureComponent>('#');
      grid->Add<ObstacleComponent>();
      grid->Add<GridComponent>();
      grid->Add<GraphicComponent>(0x1006);
      grid->Add<ColorComponent>("dark #470000");
      if (ctx_->graphic) {
        grid->Get<GraphicComponent>()->flag = true;
      }
    } else if (i == '$' && ctx_->Check_out({x_p, y_p})) {
      auto coin = engine.GetEntityManager()->CreateEntity();
      coin->Add<TransformComponent>(x_p, y_p);
      coin->Add<TextureComponent>('$');
      coin->Add<RewardComponent>(reward);
      coin->Add<CoinComponent>();
      coin->Add<GraphicComponent>(0x1005);
      coin->Add<ColorComponent>("#e2e515");
      coin->Add<AudioComponent>("coin.ogg");
      if (ctx_->graphic) {
        coin->Get<GraphicComponent>()->flag = true;
      }
    } else if (i == '0') {
      x = x_p;
      y = y_p;
    } else if (i == '%' && ctx_->Check_out({x_p, y_p})) {
      auto health = engine.GetEntityManager()->CreateEntity();
      health->Add<TransformComponent>(x_p, y_p);
      health->Add<TextureComponent>('&');
      health->Add<MedkitComponent>(medkit);
      health->Add<MedComponent>();
      health->Add<GraphicComponent>(0x1001);
      health->Add<ColorComponent>("dark green");
      health->Add<AudioComponent>("health.ogg");
      if (ctx_->graphic) {
        health->Get<GraphicComponent>()->flag = true;
      }
    } else if (i == 'K' && ctx_->Check_out({x_p, y_p})) {
      auto key = engine.GetEntityManager()->CreateEntity();
      key->Add<TransformComponent>(x_p, y_p);
      key->Add<TextureComponent>('K');
      key->Add<KeyComponent>();
      key->Add<GraphicComponent>(0x1007);
      key->Add<ColorComponent>("dark orange");
      key->Add<AudioComponent>("key.ogg");
      if (ctx_->graphic) {
        key->Get<GraphicComponent>()->flag = true;
      }

    } else if (i == 'E' && Check_en(id_e)) {
      auto enemy = engine.GetEntityManager()->CreateEntity();
      enemy->Add<MovementComponent>();
      if (ctx_->is_first[ctx_->real_level - 1]) {  // no first
        enemy->Add<TransformComponent>(ctx_->enemy_cor[ctx_->real_level - 1][f_id_e][0],
                                       ctx_->enemy_cor[ctx_->real_level - 1][f_id_e][1]);
      } else {
        enemy->Add<TransformComponent>(x_p, y_p);
      }
      enemy->Add<TextureComponent>('E');
      enemy->Add<AIControlComponent>();
      enemy->Add<DamageComponent>(damage);
      enemy->Add<EnemyComponent>(id_e);
      enemy->Add<AudioComponent>("enemy.ogg");
      id_e++;
      f_id_e++;
      enemy->Add<GraphicComponent>(0x1002);
      enemy->Add<ColorComponent>("red");
      if (ctx_->graphic) {
        enemy->Get<GraphicComponent>()->flag = true;
      }
    }
    x_p++;
    if (i == ')') {
      x_p = 0;
      y_p++;
    }
  }

  auto sys = engine.GetSystemManager();
  sys->AddSystem<MovementSystem>(controls);
  sys->AddSystem<CollisionManagerSystem>(ctx_);
  sys->AddSystem<MenuSystem>(max_step);
  sys->AddSystem<AIControlSystem>();
  sys->AddSystem<RenderingSystem>();
  ctx_->is_first[ctx_->real_level - 1] = true;
}

void GameScene::OnRender() {
  Update();
  engine.OnUpdate();
}

void GameScene::OnExit() {
  engine.GetEntityManager()->DeleteAll();
  engine.GetSystemManager()->DeleteAll();
}

GameScene::GameScene(Context* const ctx, const Controls& controls) : IScene(ctx), controls(controls) {}
