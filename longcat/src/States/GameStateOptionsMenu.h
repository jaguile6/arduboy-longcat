#pragma once

#include <stdint.h>
#include "GameState.h"

class Game;
class GameStateOptionsMenu
{
  static const uint8_t maxSelection = 1;
  uint8_t selection = 0;
public:
  void update(Game &game);
  void render(Game &game);
};
