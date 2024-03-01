#ifndef PLAYERS_H
#define PLAYERS_H

#include "System.h"
#include "Session.h"
#include "Component.h"
#include "Common.h"
#include "Constants.h"
#include "Label.h"

#include "Tile.h"
#include "GameBoard.h"
#include "MiniMax.h"

#include <iostream>
#include <sstream>
#include <iomanip>

class Players : public Component
{
public:
	static Players *getInstance(Session &ses)
	{
		return new Players(constants::playerParamater, ses);
	}

	virtual void tick()
	{
		int outputX, outputY;
		SDL_GetMouseState(&outputX, &outputY);

		if (gameBoard.isPlayer())
		{
			if (updatingLabels && lastTile->inPlace() && constants::visualizeMinimax && !gameBoard.isGameOver()) {
				miniMax(); // Update minimax for player
				updatingLabels = false;
			}
			if (outputX)
				mouseX = outputX;
			setX(mouseX - 50);
		}
		else if ((boardEmpty || lastTile->inPlace()) && !gameBoard.isGameOver())
		{
			placeMarker();
			updatingLabels = true;
		}
	}

	virtual void draw() const
	{
		// Handle the address to temporary object
		const SDL_Rect &rect = getRect();
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &rect);
	}

	virtual void mouseDown(const SDL_Event &)
	{
		if (!gameBoard.isPlayer() || (!boardEmpty && !lastTile->inPlace()) || gameBoard.isGameOver())
			return;
		placeMarker();
		updatingLabels = true;
	}

	void destroyTexture()
	{
		SDL_DestroyTexture(texture1);
		SDL_DestroyTexture(texture2);
	}

	SDL_Texture *getTexture() const
	{
		if (gameBoard.getTurn() == common::Turn::firstPlayer)
			return texture1;
		else
			return texture2;
	}

protected:
	Players(common::SetupParameter parameter, Session &ses) : Component(0, -50, 100, 100), ses(ses), gameBoard(parameter)
	{
		texture1 = IMG_LoadTexture(sys.getRen(), (constants::gResPath + "images/green_tile.png").c_str());
		texture2 = IMG_LoadTexture(sys.getRen(), (constants::gResPath + "images/red_tile.png").c_str());
		if (constants::visualizeMinimax)
		{
			miniMax();
			for (int i = 0; i < constants::sizeX; i++)
			{
				std::stringstream ss;
				ss << std::fixed << std::setprecision(2) << minimaxVector[i];
				Label *currentLabel = Label::getInstance(75 + i * 100, 700, 50, 50, ss.str());
				ses.add(currentLabel);
				labelVector.push_back(currentLabel);
			}
		}
	}

private:
	// Place marker
	bool placeMarker()
	{
		int col;
		common::Turn turn = gameBoard.getTurn();
		if (gameBoard.isPlayer())
			col = getClosestCol();
		else
			col = miniMax();
		if (col >= 0 && col < constants::sizeX)
		{
			int row = gameBoard.placeMarker(col);
			if (row != -1)
			{
				lastTile = Tile::getInstance(col, row, mouseX - 50, turn);
				ses.add(lastTile);
				boardEmpty = false;
				
				return true;
			}
		}
		return false;
	}

	int miniMax()
	{
		common::Turn turn = gameBoard.getTurn();
		std::vector<std::vector<int>> matrix = gameBoard.getMatrixCopy();
		MoveScore minimax = MiniMax::minimaxAll(matrix, constants::searchDepth, (turn == common::Turn::firstPlayer));
		minimaxVector = minimax.evaluationVector;
		if (constants::visualizeMinimax)
		{
			for (double d : minimaxVector)
				std::cout << d << ", ";
			std::cout << std::endl;
			updateLabels();
		}
		return minimax.move;
	}

	int getClosestCol() const
	{
		return (mouseX - 50) / 100;
	}

	void updateLabels()
	{
		if (labelVector.empty()) {
			return;
		}
		for (int i = 0; i < constants::sizeX; i++)
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << minimaxVector[i];
			labelVector[i]->setText(ss.str());
		}
	}

	int frame = 0;

	// Texture references (player 1 and player 2 marker)
	SDL_Texture *texture1, *texture2;

	// Reference to check whether tile is inplace or not
	Tile *lastTile;

	bool boardEmpty = true;

	bool gameOver = false;

	bool updatingLabels = false;

	// Reference to session in order to add objects
	Session &ses;

	// position of mouse
	int mouseX = 0;

	// minimax vector
	std::vector<double> minimaxVector;

	// Label vector
	std::vector<Label *> labelVector;

	// Gameboard object
	GameBoard gameBoard;
};

#endif