#include "LevelRenderer.h"
#include "../Game.h"
using namespace LevelRenderer;

void LevelRenderer::renderStuck(uint8_t xDrawOffset, uint8_t yDrawOffset, Game &game){
    auto &arduboy = game.getArduboy();
    if (LevelUtils::isStuck(game))
    {
        arduboy.setCursor(xDrawOffset, yDrawOffset);
        arduboy.print(F("STUCK!"));
    }
}

void LevelRenderer::renderRandData(uint8_t xDrawOffset, uint8_t yDrawOffset, Game &game)
{
    auto &arduboy = game.getArduboy();
    auto &context = game.getGameContext();
    CatKey r = RandKey::toCatKey(context.currentSeed);
    for (uint8_t i = 0; i < CatKeyLength; i++)
    {
        CatChars::drawChar(xDrawOffset + (i * 8), yDrawOffset, true, r.key[i] + 2);
    }
}

void LevelRenderer::renderLevelData(uint8_t xDrawOffset, uint8_t yDrawOffset, Game &game)
{
    auto &arduboy = game.getArduboy();
    auto &context = game.getGameContext();
    arduboy.setCursor(xDrawOffset,yDrawOffset);
    arduboy.print(F("LVL: "));
    arduboy.print(context.stage + 1);
    arduboy.setCursor(xDrawOffset, yDrawOffset + 30);
    arduboy.print("B: Retry");
}

void LevelRenderer::renderLevel(uint8_t xDrawOffset, uint8_t yDrawOffset, Game &game)
{
    auto &context = game.getGameContext();
    for (int j = 0; j < Map::mapHeight; j++)
    {
        for (int i = 0; i < Map::mapWidth; i++)
        {
            uint8_t tileIndex = toTileIndex(context.mapObject.getTile(i, j));
            Sprites::drawOverwrite((i * Map::tileSize) + xDrawOffset,(j * Map::tileSize) + yDrawOffset, Cats, tileIndex);
        }
    }
}

void LevelRenderer::renderPlayer(uint8_t xDrawOffset, uint8_t yDrawOffset, Game &game)
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
    Sprites::drawOverwrite((context.hero.x * Map::tileSize) + xDrawOffset, (context.hero.y * Map::tileSize) + yDrawOffset, Cats, toTileIndex(type));
}

//=============================================


void LevelRenderer::render(Game &game)
{
    renderLevel(0,0,game);
    renderPlayer(0,0,game);
    renderLevelData(70,20,game);
    renderStuck(70,30,game);
    if (game.getGameMode() == GameMode::Random)
    {
        renderRandData(64,0,game);
    }
}

