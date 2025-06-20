#pragma once // Stellt sicher, dass die Header-Datei nur einmal inkludiert wird

#include "esphome/core/component.h" // Basisklasse für ESPHome Komponenten
#include "esphome/components/light/light_output.h" // Für die Integration als Licht in Home Assistant
#include "esphome/core/hal.h" // Für GPIO-Pin-Operationen (digitalWrite, delayMicroseconds)
