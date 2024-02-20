#ifndef PLAYERS_H
#define PLAYERS_H

#include "System.h"
#include "Session.h"
#include "Component.h"
#include "Common.h"
#include "Constants.h"

#include "Tile.h"

class Players : public Component
{
public:
	static Players *getInstance(Session& ses) 
	{
		return new Players(constants::playerParamater, ses);
	}

	virtual void tick() {}

    virtual void draw() const {}

	virtual void mouseDown(const SDL_Event&) {}

protected:
	Players(common::SetupParameter parameter, Session& ses) : Component(0, 0, 0, 0), parameter(parameter), ses(ses)
	{
		Tile *tile = Tile::getInstance(1, 1, turn);
		ses.add(tile);
    }

private:
    // Indicates who is a player, and who is played by the computer
    const common::SetupParameter parameter;

    // Indicates whose turn it is
    common::Turn turn = common::Turn::firstPlayer;

	// Reference to session in order to add objects
	Session& ses;

};

#endif