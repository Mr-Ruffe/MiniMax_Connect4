#include "Session.h"
#include <SDL2/SDL.h>
#include "System.h"

#include <iostream>

Session::Session()
{
	std::cout << "*** Session::Session()\n";
}

void Session::add(Component *c)
{
	newComps.push_back(c);
}

void Session::run()
{
	bool quit = false;
	while (!quit)
	{
		SDL_Event eve;
		while (SDL_PollEvent(&eve))
		{
			switch (eve.type)
			{
			case SDL_QUIT:
				quit = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				for (Component *c : comps)
					c->mouseDown(eve);
				break;
			case SDL_MOUSEBUTTONUP:
				for (Component *c : comps)
					c->mouseUp(eve);
				break;
			case SDL_KEYDOWN:
				for (Component *c : comps)
					c->keyDown(eve);
				break;
			case SDL_KEYUP:
				for (Component *c : comps)
					c->keyUp(eve);
				break;
			}
		}

		SDL_SetRenderDrawColor(sys.getRen(), 255, 255, 255, 255);
		SDL_RenderClear(sys.getRen());
		for (auto it = comps.rbegin(); it != comps.rend(); ++it) {
			(*it)->tick();
			(*it)->draw();
		}
		for (auto it = newComps.rbegin(); it != newComps.rend(); ++it) {
			comps.push_back(*it);
			newComps.erase(std::next(it).base());
		}

		
		SDL_RenderPresent(sys.getRen());
	}
}
