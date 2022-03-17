#include "LevelRenderer.h"
#include "../Game.h"
using namespace LevelRenderer;

void LevelRenderer::render(Game &game)
{
    auto &arduboy = game.getArduboy();
    if (LevelUtils::isStuck(game))
    {
        arduboy.setCursor(70, 30);
        arduboy.print(F("STUCK!"));
    }
    renderPlayArea(game);
}

void LevelRenderer::renderRandData(Game &game)
{
    auto &arduboy = game.getArduboy();
    auto &context = game.getGameContext();
    CatKey r = RandKey::toCatKey(context.currentSeed);
    for (uint8_t i = 0; i < CatKeyLength; i++)
    {
        CatChars::drawChar(64 + (i * 8), 0, true, r.key[i] + 2);
    }
}

void LevelRenderer::renderLevelData(Game &game)
{
    auto &arduboy = game.getArduboy();
    auto &context = game.getGameContext();
    arduboy.setCursor(70, 20);
    arduboy.print(F("LVL: "));
    arduboy.print(context.stage + 1);
    arduboy.setCursor(70, 50);
    arduboy.print("B: Retry");
}

void LevelRenderer::renderLevel(Game &game)
{
    auto &context = game.getGameContext();
    for (int j = 0; j < Map::mapHeight; j++)
    {
        for (int i = 0; i < Map::mapWidth; i++)
        {
            uint8_t tileIndex = toTileIndex(context.mapObject.getTile(i, j));
            Sprites::drawOverwrite(i * Map::tileSize, j * Map::tileSize, Cats, tileIndex);
        }
    }
}

void LevelRenderer::renderPlayer(Game &game)
{
    auto &context = game.getGameContext();
    TileType type;
    switch (context.hero.lastDirection)
    {
    case Direction::Center:
        type = TileType::Cat_Head_Down;
        break;
    case Direction::Down:
        type = TileType::Cat_Head_Down;
        break;
    case Direction::Up:
        type = TileType::Cat_Head_Up;
        break;
    case Direction::Left:
        type = TileType::Cat_Head_Left;
        break;
    case Direction::Right:
        type = TileType::Cat_Head_Right;
        break;
    }
    Sprites::drawOverwrite(context.hero.x * Map::tileSize, context.hero.y * Map::tileSize, Cats, toTileIndex(type));
}

void LevelRenderer::renderPlayArea(Game &game)
{
    renderLevel(game);
    renderPlayer(game);
    renderLevelData(game);
    if (game.getGameMode() == GameMode::Random)
    {
        renderRandData(game);
    }
}