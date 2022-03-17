#include "GameStateMainMenu.h"

#include "../Game.h"

void GameStateMainMenu::update(Game &game)
{
	auto &arduboy = game.getArduboy();
	if (arduboy.justPressed(UP_BUTTON))
	{
		if (this->selection > 1)
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
			context.stage = 0;
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
	const char *mainmenu_s = " \0";
	const char *linear_s = "  Linear\0";
	const char *random_s = "  Random\0";
	const char *select_level_s = "  Select Level\0";
	const char *select_seed_s = "  Select Seed\0";
	const char *option_a_s = " \0";
	const char *option_b_s = " \0";
	const char *strings[] = {mainmenu_s, linear_s, random_s, select_level_s, select_seed_s, option_a_s, option_b_s};
	for (uint8_t i = 0; i < 7; i++)
	{
		CatChars::print(0, i * 9+4, true, strings[i]);
		if (selection == i - 1)
		{
			uint8_t len = CatChars::length(strings[i]);
			CatChars::drawChar((len)*8 + (((sin(arduboy.frameCount / 15.0f) + 1) / 2.0f) * 5) + 1, (this->selection * 9) + 9+4, true, 45);
		}
	}
	int a=80;
	if(arduboy.frameCount%(2*a)<=a){
		CatChars::print((arduboy.frameCount/2%a), 2, true, "<  <  <  <\0");
	}else{
		CatChars::print(a-(arduboy.frameCount/2%a), 2, true, "<  <  <  <\0");
	}
	
	if(arduboy.frameCount%(2*a)<=a){
		CatChars::print(a/2-(arduboy.frameCount/2%a), 52, true, "<  <  <  <\0");
	}else{
		CatChars::print((arduboy.frameCount/2%a)-a/2, 52, true, "<  <  <  <\0");
	}
		
	
}
