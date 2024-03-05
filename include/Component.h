#ifndef COMPONENT_H
#define COMPONENT_H

#include <SDL2/SDL.h>

/// Based on the Component class by @author jozef

/// @brief The abstract class used as a frontend component.
class Component
{
public:
	/// @brief Default destructor
	virtual ~Component() {}

	/// @brief Default interface for mouse down.
	/// @param SDL_Event The event triggered.
	virtual void mouseDown(const SDL_Event &) {}

	/// @brief Default interface for mouse up.
	/// @param SDL_Event The event triggered.
	virtual void mouseUp(const SDL_Event &) {}

	/// @brief Default interface for key down.
	/// @param SDL_Event The event triggered.
	virtual void keyDown(const SDL_Event &) {}

	/// @brief Default interface for key up.
	/// @param SDL_Event The event triggered.
	virtual void keyUp(const SDL_Event &) {}

	/// @brief Default interface for the tick-call.
	virtual void tick() {}

	/// @brief The forced implementation of the draw-method (updating the object in the renderer).
	virtual void draw() const = 0;

	/// @brief The get:er of the SDL_Rect (the rectangular object containing the position and size).
	/// @return The SDL_Rect object reference for the object.
	const SDL_Rect &getRect() const { return rect; }

	/// @brief Move the object (the SDL_Rect) in x-direction.
	/// @param x Incremental position in x.
	void moveX(int x) { rect.x += x; }

	/// @brief Move the object (the SDL_Rect) in y-direction.
	/// @param y Incremental position in y.
	void moveY(int y) { rect.y += y; }

	/// @brief Set the object (the SDL_Rect) in x-direction.
	/// @param x Absolute position in x.
	void setX(int x) { rect.x = x; }

	/// @brief Set the object (the SDL_Rect) in y-direction.
	/// @param y Absolute position in y.
	void setY(int y) { rect.y = y; }

protected:
	/// @brief Protected constructor of the Component-object.
	/// @param x The position of the object in x-direction.
	/// @param y The position of the object in y-direction.
	/// @param w The width of the object.
	/// @param h The height of the object.
	Component(int x, int y, int w, int h) : rect{x, y, w, h} {}

private:
	// The rectangle object from SDL.
	SDL_Rect rect;

	/// @brief Removing the copy-constructor.
	/// @param Component the reference to the object to be copied.
	Component(const Component &) = delete;

	/// @brief Removing the assignment-operator.
	/// @param Component the reference to the object to be copied.
	/// @return The new Component that should've been created.
	const Component &operator=(const Component &) = delete;
};

#endif
