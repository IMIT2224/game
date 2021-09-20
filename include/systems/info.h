#ifndef INCLUDE_SYSTEMS_INFO_H_
#define INCLUDE_SYSTEMS_INFO_H_

#include <iostream>

class Info {
 private:
  int total_steps;
  int total_reward;

 public:
  Info() {
    total_steps = 0;
    total_reward = 0;
  }
  void Set_values(int ts, int tr) {
    total_steps = ts;
    total_reward = tr;
    std::cout << total_steps << " " << total_reward << std::endl;
  }
  int Get_ts() const {
    return total_steps;
  }

  int Get_tr() const {
    return total_reward;
  }
};

#endif  // INCLUDE_SYSTEMS_INFO_H_
