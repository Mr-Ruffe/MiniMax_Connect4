#include "Tile.h"

#include "Players.h"

Tile *Tile::getInstance(int x, int y, int xInit, common::Turn turn)
{
    std::string image;
    if (turn == common::Turn::firstPlayer)
        image = constants::gResPath + "images/green_tile.png";
    else
        image = constants::gResPath + "images/red_tile.png";
    return new Tile(x, y, xInit, image);
}

Tile::~Tile()
{
    destroyTexture();
}

void Tile::draw() const
{
    // Handle the address to temporary object
    const SDL_Rect &rect = getRect();
    SDL_RenderCopy(sys.getRen(), texture, NULL, &rect);
}
void Tile::tick()
{
    if (finalPos)
        return;
    counter++;
    if (counter >= 5)
    {
        counter = 0;
        SDL_Rect rect = getRect();
        if (rect.x > targetX)
            moveX(-1);
        else if (rect.x < targetX)
            moveX(1);
        else
        {
            if (rect.y >= targetY)
                finalPos = true;
            else
                moveY(1);
        }
    }
}

bool Tile::inPlace()
{
    return finalPos;
}

void Tile::destroyTexture()
{
    SDL_DestroyTexture(texture);
}


Tile::Tile(int x, int y, int xInit, const std::string &path) : Component(xInit, -50, 100, 100), targetX(x * 100 + 100), targetY(constants::sizeY * 100 - y * 100)
{
    texture = IMG_LoadTexture(sys.getRen(), path.c_str());
}
