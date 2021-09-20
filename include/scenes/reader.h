#ifndef INCLUDE_SCENES_READER_H_
#define INCLUDE_SCENES_READER_H_

#include <string>

#include "../include/scenes/i_reader.h"

class reader : public IReader {
 private:
  std::string msg = "";

 public:
  reader();
  void read_level(const std::string& name_source) override;
  std::string Get_level() override;
};

#endif  // INCLUDE_SCENES_READER_H_
