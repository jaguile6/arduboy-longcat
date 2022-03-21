#include "GameStateCredits.h"

#include "../Game.h"
#include "../Utils/CatChars.h"

void GameStateCredits::update(Game &game)
{
  auto &arduboy = game.getArduboy();
  if (arduboy.justPressed(A_BUTTON) or arduboy.justPressed(B_BUTTON))
  {
    game.setGameState(GameState::MainMenu);
  }
}

void GameStateCredits::render(Game &game)
{
  auto &arduboy = game.getArduboy();
  CatChars::print(70, 15, true, "jaguile6");	
  CatChars::print(70, 30, true, "Dreamer2345");	
  arduboy.drawBitmap(0,0,thumbsup,64,64,WHITE);
}