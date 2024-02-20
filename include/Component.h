#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

class Component
{
public:
	virtual ~Component() {}
	virtual void mouseDown(const SDL_Event&) {}
	virtual void mouseUp(const SDL_Event&) {}
	virtual void keyDown(const SDL_Event&) {}
	virtual void keyUp(const SDL_Event&) {}
	virtual void tick() {}
	virtual void draw() const = 0;
	const SDL_Rect& getRect() const { return rect; }
	void moveX(int x) { rect.x += x; }
	void moveY(int y) { rect.y += y; }
protected:
	Component(int x, int y, int w, int h) :rect{ x,y,w,h } {}
private:
	SDL_Rect rect;
	Component(const Component&) = delete;
	const Component& operator=(const Component&) = delete;
};

#endif
