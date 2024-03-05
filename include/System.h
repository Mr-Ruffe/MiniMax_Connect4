#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

/// Based on the System class by @author jozef

/// @brief System class containing the system data.
class System
{
public:
	/// @brief Constructor of the system.
	System();

	/// @brief Destructor of the system.
	~System();

	/// @brief Get:er for the renderer.
	/// @return A pointer to the renderer.
	SDL_Renderer* getRen() const;

	/// @brief Get:er for the font set for the system.
	/// @return A pointer to the font used.
	TTF_Font* getFont() const;
private:
	// SDL window pointer
	SDL_Window* win;

	// SDL renderer pointer
	SDL_Renderer* ren;

	// SDL font pointer
	TTF_Font* font;
};

/// @brief Global system object
extern System sys;

#endif