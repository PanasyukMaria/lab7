// Copyright by PanasyukMaria

#ifndef INCLUDE_JSONSTORAGE_HPP_
#define INCLUDE_JSONSTORAGE_HPP_

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class JsonStorage{
 public:
  explicit JsonStorage(const std::string filename);
  [[nodiscard]] json get_storage() const;
  void load();

 private:
  json _storage;
  std::string _filename;
};

#endif  // INCLUDE_JSONSTORAGE_HPP_
