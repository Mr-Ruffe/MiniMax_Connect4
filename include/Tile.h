#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "System.h"
#include "Component.h"
#include "Constants.h"

#include "Players.h"

class Tile : public Component
{
public:
    static Tile *getInstance(int x, int y, common::Turn turn)
	{
        std::string image;
        if (turn == common::Turn::firstPlayer)
            image = constants::gResPath + "images/green_tile.png";
        else
            image = constants::gResPath + "images/red_tile.png";
		return new Tile(x, y, image);
	}

	virtual ~Tile()
	{
		destroyTexture();
	}

	virtual void draw() const
	{
		// Handle the address to temporary object
		const SDL_Rect &rect = getRect();
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &rect);
	}
	virtual void tick() 
    {
        if (!finalPos) {
            SDL_Rect rect = getRect();
            if (rect.y >= targetY)
                finalPos = true;
            else
            {
                counter++;
                if (counter >= 10) {
                    moveY(1);
                    counter = 0;
                }
            }
        }
    }
	void destroyTexture() { SDL_DestroyTexture(texture); }

	SDL_Texture *getTexture() const { return texture; }

protected:
	Tile(int x, int y, const std::string &path) : Component(x*100+50, -50, 100, 100), targetY(constants::sizeY*100 - y*100)
	{
		texture = IMG_LoadTexture(sys.getRen(), path.c_str());
	}

private:
	SDL_Texture *texture;
    const int targetY;
    int counter = 0;
    bool finalPos = false;
};

#endif