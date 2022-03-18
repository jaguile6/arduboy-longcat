#include "GameStateSelectLevel.h"

#include "../Game.h"

void GameStateSelectLevel::update(Game &game)
{
	auto &arduboy = game.getArduboy();
	auto &context = game.getGameContext();
	if (arduboy.justPressed(DOWN_BUTTON))
	{
		if (this->selection > 0)
			this->selection--;
		context.stage = this->selection;
		LevelUtils::copyStaticLevel(game);
	}

	else if (arduboy.justPressed(UP_BUTTON))
	{
		if (this->selection < maxLevel-1)
			this->selection++;
		context.stage = this->selection;
		LevelUtils::copyStaticLevel(game);
	}

	else if (arduboy.justPressed(A_BUTTON))
	{
		
		context.currentSeed = 0;
		context.stage = this->selection;
		this->selection = 0;
		game.setGameMode(GameMode::Linear);
		game.setGameState(GameState::LoadLevel);
	}

	else if (arduboy.justPressed(B_BUTTON))
	{
		this->selection = 0;
		game.setGameState(GameState::MainMenu);
	}
}

uint8_t GameStateSelectLevel::lenBCD(uint8_t value, Game &game)
{
	uint8_t index = 0;
	while (value > 0)
	{
		value /= 10;
		index++;
	}
	return index;
}

void GameStateSelectLevel::printBCD(uint8_t x, uint8_t y, uint8_t value, Game &game)
{
	uint8_t bcdlength = lenBCD(value, game);
	uint8_t index = 0;

	if (value == 0)
	{
		CatChars::drawChar(x, y, true, 2);
		return;
	}

	while (value > 0)
	{
		uint8_t newUnit = value % 10;
		CatChars::drawChar((x + ((bcdlength - 1) * 8)) - (index * 8), y, true, newUnit + 2);
		value /= 10;
		index++;
	}
}

void GameStateSelectLevel::render(Game &game)
{
	const char *selectStage_s = "Stage:";
	uint8_t length = CatChars::length(selectStage_s);
	CatChars::print(0, 0, true, selectStage_s);
	printBCD(length * 8, 0, this->selection + 1, game);
	LevelRenderer::renderLevel(32,8,game);
	LevelRenderer::renderPlayer(32,8,game);
}