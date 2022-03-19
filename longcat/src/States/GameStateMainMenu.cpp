#include "GameStateMainMenu.h"

#include "../Game.h"

void GameStateMainMenu::update(Game &game)
{
	auto &arduboy = game.getArduboy();
	if (arduboy.justPressed(UP_BUTTON))
	{
		if (this->selection > 0)
			this->selection--;
	}

	if (arduboy.justPressed(DOWN_BUTTON))
	{
		if (this->selection < maxSelection)
			this->selection++;
	}

	if (arduboy.justPressed(A_BUTTON))
	{
		auto &context = game.getGameContext();
		switch (selection)
		{
		case 0:
			context.currentSeed = 0;
			//context.stage = 0;
			this->selection = 0;
			game.setGameMode(GameMode::Linear);
			game.setGameState(GameState::LoadLevel);
			break;
		case 1:
			context.currentSeed = arduboy.generateRandomSeed();
			context.stage = 0;
			this->selection = 0;
			game.setGameMode(GameMode::Random);
			game.setGameState(GameState::LoadLevel);
			break;
		case 2:
			context.currentSeed = 0;
			context.stage = 0;
			this->selection = 0;
			game.setGameMode(GameMode::Linear);
			game.setGameState(GameState::SelectLevel);
			break;
		case 3:
			context.currentSeed = 0;
			context.stage = 0;
			this->selection = 0;
			game.setGameMode(GameMode::Fixed);
			game.setGameState(GameState::SelectSeed);
			break;
		}

		if (arduboy.justPressed(B_BUTTON))
		{
			this->selection = 0;
			game.setGameState(GameState::SplashScreen);
		}
	}
}

void GameStateMainMenu::render(Game &game)
{
	auto &arduboy = game.getArduboy();
	// arduboy.fillScreen(WHITE);
	const char *linear_s = "  Campaign";
	const char *random_s = "  Random";
	const char *select_level_s = "  Select Level";
	const char *select_seed_s = "  Select Seed";
	const char *strings[] = {linear_s, random_s, select_level_s, select_seed_s};
	for (uint8_t i = 0; i < 4; i++)
	{
		CatChars::print(0, (i * 9) + 12, true, strings[i]);
		if (selection == i)
		{
			uint8_t len = CatChars::length(strings[i]);
			CatChars::drawChar((len)*8 + (((sin(arduboy.frameCount / 15.0f) + 1) / 2.0f) * 5) + 1, (this->selection * 9) + 12, true, 45);
		}
	}

	const int loopLength = 80;
	if (arduboy.frameCount % (2 * loopLength) <= loopLength)
	{
		CatChars::print((arduboy.frameCount / 2 % loopLength), 2, true, "<  <  <  <");
	}
	else
	{
		CatChars::print(loopLength - (arduboy.frameCount / 2 % loopLength), 2, true, "<  <  <  <");
	}

	if (arduboy.frameCount % (2 * loopLength) <= loopLength)
	{
		CatChars::print(loopLength / 2 - (arduboy.frameCount / 2 % loopLength), 52, true, "<  <  <  <");
	}
	else
	{
		CatChars::print((arduboy.frameCount / 2 % loopLength) - loopLength / 2, 52, true, "<  <  <  <");
	}
}
