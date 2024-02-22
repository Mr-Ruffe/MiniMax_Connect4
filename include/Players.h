#ifndef PLAYERS_H
#define PLAYERS_H

#include "System.h"
#include "Session.h"
#include "Component.h"
#include "Common.h"
#include "Constants.h"

#include "Tile.h"
#include "GameBoard.h"

class Players : public Component
{
public:
	static Players *getInstance(Session& ses) 
	{
		return new Players(constants::playerParamater, ses);
	}

	virtual void tick() {
		int outputX, outputY;
		SDL_GetMouseState(&outputX, &outputY);
		
		if (gameBoard.isPlayer()) {
			if (outputX)
				mouseX = outputX;
			setX(mouseX-50);
		}
		else if (boardEmpty || lastTile->inPlace()) {
			common::Turn turn = gameBoard.getTurn();
			int col, row;
			if (gameBoard.placeMinMaxMarker(col, row)) {
				lastTile = Tile::getInstance(col, row, mouseX-50, turn);
				ses.add(lastTile);
				boardEmpty = false;
			}
		}
	}

    virtual void draw() const {
		// Handle the address to temporary object
		const SDL_Rect &rect = getRect();
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &rect);
	}

	virtual void mouseDown(const SDL_Event&) {
		if (!gameBoard.isPlayer() || (!boardEmpty && !lastTile->inPlace()))
			return;
		common::Turn turn = gameBoard.getTurn();
		int col = getClosestCol();
		if (col >= 0 && col < constants::sizeX) {
			int row = gameBoard.peekMarker(col);
			if (row != -1) {
				lastTile = Tile::getInstance(col, row, mouseX-50, turn);
				ses.add(lastTile);
				boardEmpty = false;
			}
		}
	}

	void destroyTexture() { 
		SDL_DestroyTexture(texture1);
		SDL_DestroyTexture(texture2); 
	}

	SDL_Texture *getTexture() const {
		if (gameBoard.getTurn() == common::Turn::firstPlayer)
			return texture1;
		else
			return texture2;
	}

protected:
	Players(common::SetupParameter parameter, Session& ses) : Component(0, -50, 100, 100), ses(ses), gameBoard(parameter)
	{
		texture1 = IMG_LoadTexture(sys.getRen(), (constants::gResPath + "images/green_tile.png").c_str());
		texture2 = IMG_LoadTexture(sys.getRen(), (constants::gResPath + "images/red_tile.png").c_str());
    }

private:
	// Texture references (player 1 and player 2 marker)
	SDL_Texture *texture1, *texture2;

	// Reference to check whether tile is inplace or not
	Tile *lastTile;

	bool boardEmpty = true;

	// Reference to session in order to add objects
	Session& ses;

	// position of mouse
	int mouseX = 0;

	// Gameboard object
	GameBoard gameBoard;

	int getClosestCol() {
		return (mouseX-50)/100;
	}

};

#endif