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
    static Tile *getInstance(int x, int y, int xInit, common::Turn turn)
	{
        std::string image;
        if (turn == common::Turn::firstPlayer)
            image = constants::gResPath + "images/green_tile.png";
        else
            image = constants::gResPath + "images/red_tile.png";
		return new Tile(x, y, xInit, image);
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
        if (finalPos)
            return;
        counter++;
        if (counter >= 5) {
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

    bool inPlace() {
        return finalPos;
    }

	void destroyTexture() { SDL_DestroyTexture(texture); }

	SDL_Texture *getTexture() const { return texture; }

protected:
	Tile(int x, int y, int xInit, const std::string &path) : Component(xInit, -50, 100, 100), targetX(x*100+50), targetY(constants::sizeY*100 - y*100)
	{
		texture = IMG_LoadTexture(sys.getRen(), path.c_str());
	}

private:
	SDL_Texture *texture;
    const int targetX, targetY;
    int counter = 0;
    bool finalPos = false;
};

#endif