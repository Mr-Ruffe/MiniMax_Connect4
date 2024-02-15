#ifndef SYSTEM_H
#define SYSTEM_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class System
{
public:
	System();
	~System();
	SDL_Renderer* getRen() const;
	TTF_Font* getFont() const;
private:
	SDL_Window* win;
	SDL_Renderer* ren;
	TTF_Font* font;
};

extern System sys;

#endif