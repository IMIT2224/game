#include "../include/scenes/game_over_scene.h"

#include <BearLibTerminal.h>

#include <string>
#include <thread>

static void ff(std::string name) {
  std::string msg = "python3 audio.py " + name + " > log.txt";
  system(msg.c_str());
}

void GameOverScene::OnCreate() {
  std::thread th(ff, "win.ogg");
  th.detach();
}
void GameOverScene::OnRender() {
  terminal_set("window.title='Game'; window.size=80x25; window.cellsize=9x12;");
  terminal_clear();
  terminal_print(1, 1, "[color=#15e537]You Win");
  std::string msg1 = "[color=#15e537]Money: " + std::to_string(ctx_->total_reward);
  std::string msg2 = "[color=#15e537]Steps: " + std::to_string(ctx_->total_steps);
  terminal_print(1, 2, msg1.c_str());
  terminal_print(1, 3, msg2.c_str());
  terminal_refresh();
}
void GameOverScene::OnExit() {}
GameOverScene::GameOverScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
