// esphome/components/midea/midea_compat.h
#pragma once

#include <string>

// La librería MideaUART fue escrita para Arduino y usa su clase String.
// Creamos una clase 'String' básica que hereda de std::string de C++
// para que el código de la librería compile sin cambios.
class String : public std::string {
 public:
  // Constructores para permitir la creación desde literales de cadena y otros strings
  String() = default;
  String(const char *c_str) : std::string(c_str) {}
  String(const std::string &str) : std::string(str) {}

  // La librería podría usar .c_str(), así que nos aseguramos de que esté disponible
  const char *c_str() const { return this->data(); }
};
