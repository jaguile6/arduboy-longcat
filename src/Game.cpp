#include "Game.h"

void Game::setup()
{
  this->arduboy.begin();
  this->arduboy.setFrameRate(60);
  this->arduboy.initRandomSeed();
}

void Game::loop()
{
  if (!this->arduboy.nextFrame())
    return;

  this->arduboy.pollButtons();

  switch (this->gameState)
  {
  case GameState::SplashScreen:
    this->arduboy.clear();
    this->splashScreenState.update(*this);
    this->splashScreenState.render(*this);
    this->arduboy.display();
    break;

  case GameState::MainMenu:
    this->arduboy.clear();
    this->mainMenuState.update(*this);
    this->mainMenuState.render(*this);
    this->arduboy.display();
    break;

  case GameState::SelectLevel:
    this->arduboy.clear();
    this->selectLevelState.update(*this);
    this->selectLevelState.render(*this);
    this->arduboy.display();
    break;

  case GameState::SelectSeed:
    this->arduboy.clear();
    this->selectSeedState.update(*this);
    this->selectSeedState.render(*this);
    this->arduboy.display();
    break;

  case GameState::LoadLevel:
    this->loadLevelState.update(*this);
    this->loadLevelState.render(*this);
    break;

  case GameState::GamePlay:
    this->arduboy.clear();
    this->gamePlayState.update(*this);
    this->gamePlayState.render(*this);
    this->arduboy.display();
    break;

  case GameState::Simulate:
    this->arduboy.clear();
    this->simulateState.update(*this);
    this->simulateState.render(*this);
    this->arduboy.display();
    break;
  }
}
