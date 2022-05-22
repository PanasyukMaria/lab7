// Copyright by PanasyukMaria

#include <fstream>
#include <sstream>
#include "JsonStorage.hpp"

JsonStorage::JsonStorage(const std::string filename) {
  _filename = filename;
}

json JsonStorage::get_storage() const {
  return _storage;
}

void JsonStorage::load(){
  try {
    std::ifstream f(_filename);
    f >> _storage;
  } catch (const std::exception& exception) {
    std::cout << exception.what() << std::endl;
  }
}
