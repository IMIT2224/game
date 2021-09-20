#include <BearLibTerminal.h>

#include <iostream>

#include "../include/controls.h"
#include "../include/scenes/game_over_l_scene.h"
#include "../include/scenes/game_over_scene.h"
#include "../include/scenes/game_scene.h"
#include "../include/scenes/scene_manager.h"
#include "../include/scenes/title_scene.h"

int main() {
  const int NUMBER_LEVELS = 3;  // Количество уровней в игре
  terminal_open();
  terminal_refresh();

  Controls controls;

  Context ctx(NUMBER_LEVELS);  // создаем контекст на стеке в самом начале приложения
  SceneManager sm(ctx);  // создаем менеджер сцен на стеке

  // Регистрируем сцены в менеджер
  sm.Put("game_over", new GameOverLScene(&ctx, controls));
  sm.Put("title", new TitleScene(&ctx, controls));
  for (int i = 0; i < NUMBER_LEVELS; i++) {
    sm.Put("game_" + std::to_string(i + 1), new GameScene(&ctx, controls));
  }
  sm.Put("game_" + std::to_string(NUMBER_LEVELS + 1), new GameOverScene(&ctx, controls));
  // Выставляем текущую сцену
  ctx.scene_ = "title";

  while (true) {
    controls.OnUpdate();
    if (controls.IsPressed(TK_CLOSE)) {
      break;
    }

    sm.OnRender();
    controls.Reset();
  }
  sm.OnExit();

  terminal_close();
}
