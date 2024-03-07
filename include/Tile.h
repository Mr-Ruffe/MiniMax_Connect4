#ifndef TILE_H
#define TILE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

#include "System.h"
#include "Component.h"
#include "Constants.h"

/// @brief The tile object displaying the red or green tile.
class Tile : public Component
{
public:
    /// @brief Acts as a constructor and restricts the user to create Tile-objects in other ways.
	/// @param x The target tile-place of the tile in x position.
	/// @param y The target tile-place of the tile in y position.
    /// @param xInit The initial position of where the tile should start.
    /// @param turn The indicator of whose turn it is.
    /// @return A new Tile-instance.
    static Tile *getInstance(int x, int y, int xInit, common::Turn turn);

	/// @brief Destructor of the Tile-object.
	virtual ~Tile();

	/// @brief Called every tick for updating the object in the renderer.
	virtual void draw() const;

	/// @brief Called from Session every tick. Updates the position until final.
	virtual void tick();

    /// @brief Check if the tile is in place.
    /// @return True if it is in place. Else false.
    bool inPlace();

	/// @brief Destroys the texture.
	void destroyTexture();

protected:
	/// @brief Constructor of the tile-object.
	/// @param x The target tile-place of the tile in x position.
	/// @param y The target tile-place of the tile in y position.
    /// @param xInit The initial position of where the tile should start.
    /// @param turn The indicator of whose turn it is.
	/// @param path Path to the texture used.
	Tile(int x, int y, int xInit, const std::string &path);

private:
	// The texture used.
	SDL_Texture *texture;

    // The final position of the tile.
    const int targetX, targetY;

    // Counter to prevent too fast movement.
    int counter = 0;

    // Boolean indicating final position.
    bool finalPos = false;
};

#endif