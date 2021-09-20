#ifndef INCLUDE_SCENES_I_READER_H_
#define INCLUDE_SCENES_I_READER_H_

#include <string>

class IReader {
 public:
  virtual void read_level(const std::string& name_source) = 0;

  virtual std::string Get_level() = 0;
};

#endif  // INCLUDE_SCENES_I_READER_H_
