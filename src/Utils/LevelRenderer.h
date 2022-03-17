#pragma once

#include <stdint.h>
#include <Arduboy2.h>
#include "LevelUtils.h"

class Game;
namespace LevelRenderer
{
    void render(Game &game);
    void renderRandData(Game &game);
    void renderLevelData(Game &game);
    void renderLevel(Game &game);
    void renderPlayer(Game &game);
    void renderPlayArea(Game &game);
};