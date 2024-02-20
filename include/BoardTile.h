#ifndef BOARD_TILE_H
#define BOARD_TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "System.h"
#include "Component.h"

class BoardTile : public Component
{
public:
	static BoardTile *getInstance(int x, int y, int sizeX, int sizeY) 
	{
		return new BoardTile(x, y, sizeX, sizeY, 100, 100, constants::gResPath + "images/board_tile.png");
	}

	virtual ~BoardTile()
	{
		destroyTexture();
	}

	virtual void draw() const
	{
		const SDL_Rect &rect = getRect();

		// Calculate the number of times the sprite should be repeated in the x-direction

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
	virtual void tick() {}

	void destroyTexture() { SDL_DestroyTexture(texture); }

	SDL_Texture *getTexture() const { return texture; }

protected:
	BoardTile(int x, int y, int sizeX, int sizeY, int frameWidth, int frameHeight, const std::string &path) : Component(x, y, frameWidth, frameHeight), sizeX(sizeX), sizeY(sizeY)
	{
		texture = IMG_LoadTexture(sys.getRen(), path.c_str());
	}

private:
	SDL_Texture *texture;
	const int sizeX, sizeY;
};

#endif