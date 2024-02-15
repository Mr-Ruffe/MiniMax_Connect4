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
	static BoardTile *getInstance(int x, int y) 
	{
		return new BoardTile(x, y, 100, 100, constants::gResPath + "images/board_tile.png");
	}

	virtual ~BoardTile()
	{
		destroyTexture();
	}

	virtual void draw() const
	{
		// Handle the address to temporary object
		const SDL_Rect &rect = getRect();
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &rect);
	}
	virtual void tick() {}

	void destroyTexture() { SDL_DestroyTexture(texture); }

	SDL_Texture *getTexture() const { return texture; }

protected:
	BoardTile(int x, int y, int frameWidth, int frameHeight, const std::string &path) : Component(x, y, frameWidth, frameHeight)
	{
		texture = IMG_LoadTexture(sys.getRen(), path.c_str());
	}

private:
	SDL_Texture *texture;
};

#endif