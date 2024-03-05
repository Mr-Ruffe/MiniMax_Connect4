#include "BoardTile.h"
#include "System.h"
#include "Constants.h"

BoardTile *BoardTile::getInstance(int x, int y, int sizeX, int sizeY)
{
    return new BoardTile(x, y, sizeX, sizeY, 100, 100, constants::gResPath + "images/board_tile.png");
}

void BoardTile::draw() const
{
    const SDL_Rect &rect = getRect();

    // Repeat the number of times the sprite should be repeated in the x- and y-direction
    for (int i = 0; i < sizeX; ++i)
    {
        for (int j = 0; j < sizeY; ++j)
        {
            SDL_Rect destRect = rect;
            destRect.x = rect.x + i * rect.w;
            destRect.y = rect.y + j * rect.h;

            SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &destRect);
        }
    }
}

BoardTile::BoardTile(int x, int y, int sizeX, int sizeY, int frameWidth, int frameHeight, const std::string &path) : Component(x, y, frameWidth, frameHeight), sizeX(sizeX), sizeY(sizeY)
{
    texture = IMG_LoadTexture(sys.getRen(), path.c_str());
}
