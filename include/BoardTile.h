#ifndef BOARD_TILE_H
#define BOARD_TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "System.h"
#include "Component.h"

/// @brief The component displaying the board in the UI.
class BoardTile : public Component
{
public:
	/// @brief Acts as a constructor and restricts the user to create BoardTile-objects in other ways.
	/// @param x Position of the tile in x.
	/// @param y Position of the tile in y.
	/// @param sizeX Amount of tiles in X-direction.
	/// @param sizeY Amount of tiles in Y-direction.
	/// @return A new BoardTile-instance.
	static BoardTile *getInstance(int x, int y, int sizeX, int sizeY)
	{
		return new BoardTile(x, y, sizeX, sizeY, 100, 100, constants::gResPath + "images/board_tile.png");
	}

	/// @brief Destructor of BoardTile, destroying allocated data.
	virtual ~BoardTile()
	{
		destroyTexture();
	}

	/// @brief Called every tick for updating the object in the renderer.
	virtual void draw() const
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
	/// @brief Override of the tick-method called every tick. Empty function.
	virtual void tick() {}

	/// @brief Called by the destructor and destroys the allocated texture.
	void destroyTexture() { SDL_DestroyTexture(texture); }

	/// @brief Get:er for texture used by the object.
	/// @return The texture used by the object.
	SDL_Texture *getTexture() const { return texture; }

protected:
	/// @brief Protected constructor of the BoardTile-object. Loads the texture in the path.
	/// @param x Position of the tile in x.
	/// @param y Position of the tile in y.
	/// @param sizeX Amount of tiles in X-direction.
	/// @param sizeY Amount of tiles in Y-direction.
	/// @param frameWidth Width of the texture used per tile.
	/// @param frameHeight Height of the texture used per tile.
	/// @param path Path to the texture used.
	BoardTile(int x, int y, int sizeX, int sizeY, int frameWidth, int frameHeight, const std::string &path) : Component(x, y, frameWidth, frameHeight), sizeX(sizeX), sizeY(sizeY)
	{
		texture = IMG_LoadTexture(sys.getRen(), path.c_str());
	}

private:
	// The texture used by the object.
	SDL_Texture *texture;

	// The set sizes of the game-board (amount of tiles).
	const int sizeX, sizeY;
};

#endif