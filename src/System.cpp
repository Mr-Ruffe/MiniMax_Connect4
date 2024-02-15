#include "Constants.h"
#include "System.h"
#include <SDL2/SDL.h>
#include <iostream>

System::System()
{
	std::cout << "*** System::System()\n";

	SDL_Init(SDL_INIT_EVERYTHING);
	win = SDL_CreateWindow("Application", SDL_WINDOWPOS_CENTERED,
						   SDL_WINDOWPOS_CENTERED, 200+100*constants::sizeX, 200+100*constants::sizeY, 0);
	ren = SDL_CreateRenderer(win, -1, 0);
	TTF_Init();
	font = TTF_OpenFont((constants::gResPath + "fonts/arial.ttf").c_str(), 36);
}

System::~System()
{
	std::cout << "*** System::~System()\n";
	TTF_CloseFont(font);
	TTF_Quit();
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
}

SDL_Renderer *System::getRen() const
{
	return ren;
}

TTF_Font *System::getFont() const
{
	return font;
}

System sys;