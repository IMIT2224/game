#ifndef INCLUDE_SCENES_CONTEXT_H_
#define INCLUDE_SCENES_CONTEXT_H_
#include <BearLibTerminal.h>

#include <string>
#include <vector>

/**
 * В контексте хранится информация о сцене, которую нужно сейчас отрисоватывать.
 * Контекст должен создаться где-то во вне и передаться по указателю во все сцены,
 * чтобы они могли им манипулировать и в SceneManager,
 * чтобы он мог читать из него информацию о сценах.
 *
 * Кстати, можно использовать контекст для хранения некоторой информации при переходе между сценами.
 * Но рекомендуется придумать механизм, чтобы не пришлось постоянно править класс контектса.
 * Как минимум используйте map<string, iobject*>
 */
class Context {
 public:
  int real_level = 0;
  std::string scene_ = "";
  int total_steps = 0;
  int total_reward = 0;
  int total_health = 100;
  int max_level = 0;
  bool isUP = true;
  bool graphic = false;
  std::string random = "n";
  std::vector<std::vector<std::vector<int>>> data_level = {};
  std::vector<std::vector<std::vector<int>>> enemy_cor = {};
  std::vector<std::vector<int>> enemy_in_level = {};
  std::vector<bool> key_flag = {};
  std::vector<bool> is_first = {};
  Context(const int size) {
    terminal_bkcolor(color_from_name("#2b2b2b"));
    data_level.resize(size);
    enemy_in_level.resize(size);
    enemy_cor.resize(size);
    is_first.resize(size);
    key_flag.resize(size);

    max_level = size;
    terminal_set("0x1000: tileset.png, size=16x16");
    terminal_refresh();
    while (true) {
      terminal_clear();

      terminal_print(1, 1, "[color=#15e537]Press Enter for graphic mode OR press other key for text mode");
      if (terminal_has_input()) {
        auto key = terminal_read();
        // std::cout << key << std::endl;
        if (key == TK_ENTER) {
          graphic = true;
        }
        if (key != 225) {
          break;
        }
      }
      terminal_refresh();
    }

    terminal_refresh();
    while (true) {
      terminal_clear();

      terminal_print(1, 1, "[color=#15e537]Press Enter for random generation OR press other key for file read");
      if (terminal_has_input()) {
        auto key = terminal_read();
        // std::cout << key << std::endl;
        if (key == TK_ENTER) {
          std::string msg = "python3 gen_level.py " + std::to_string(max_level);
          system(msg.c_str());
          random = "r";
        }
        if (key != 225) {
          break;
        }
      }
      terminal_refresh();
    }
  }
  bool Check_out(std::vector<int> v) const {
    for (auto i : data_level[real_level - 1]) {
      if (i == v) {
        return 0;
      }
    }
    return 1;
  }
};

#endif  // INCLUDE_SCENES_CONTEXT_H_
