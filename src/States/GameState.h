#pragma once

enum class GameState : uint8_t
{
  SplashScreen,
  MainMenu,
  SelectLevel,
  SelectSeed,
  LoadLevel,
  GamePlay,
  Simulate,
};
