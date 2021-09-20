#include "../include/scenes/reader.h"

#include <fstream>
#include <iostream>
#include <string>

reader::reader() {}

void reader::read_level(const std::string& name_source) {
  std::ifstream fin;
  fin.open(name_source);
  if (fin.is_open()) {
    std::string s;
    while (getline(fin, s)) {
      msg += s;
      msg += ')';
    }
  } else {
    msg = "-1";
  }
  fin.close();
}

std::string reader::Get_level() {
  return msg;
}
