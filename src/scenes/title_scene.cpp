#include "../include/scenes/title_scene.h"

#include <BearLibTerminal.h>

void TitleScene::OnCreate() {}
void TitleScene::OnRender() {
  terminal_clear();
  terminal_print(1, 1, "[color=#15e537]Game\nPress Enter to start");
  if (controls_.IsPressed(TK_ENTER)) {
    if (ctx_->graphic) {
      terminal_set("window.title='Game'; window.size=80x25; window.cellsize=16x16;");
    }
    ctx_->real_level = ctx_->real_level + 1;
    ctx_->scene_ = "game_" + std::to_string(ctx_->real_level);  // переходим на другую сцену
  }
  terminal_refresh();
}
void TitleScene::OnExit() {}
TitleScene::TitleScene(Context *ctx, const Controls &controls) : IScene(ctx), controls_(controls) {}
