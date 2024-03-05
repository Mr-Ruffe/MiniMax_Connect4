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

/// @brief The front-end controller, manipulating the gameboard based on player/computer input.
class Players : public Component
{
public:
	/// @brief Acts as a constructor and restricts the user to create Players-objects in other ways.
	/// @param ses the session-reference where the object can create new objects.
	/// @return A new Players-instance.
	static Players *getInstance(Session &ses)
	{
		return new Players(constants::playerParamater, ses);
	}

	/// @brief Destructor of Players, destroying allocated data.
	virtual ~Players()
	{
		destroyTexture();
	}

	/// @brief Called from Session every tick. Updates position and acts as initator for non-player players.
	virtual void tick()
	{
		int outputX, outputY;
		SDL_GetMouseState(&outputX, &outputY);

		if (gameBoard.isPlayer())
		{
			if (updatingLabels && lastTile->inPlace() && constants::visualizeMinimax && !gameBoard.isGameOver())
			{
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

	/// @brief Called every tick for updating the object in the renderer.
	virtual void draw() const
	{
		// Handle the address to temporary object
		const SDL_Rect &rect = getRect();
		SDL_RenderCopy(sys.getRen(), getTexture(), NULL, &rect);
	}

	/// @brief Called when mouse down is pressed. Places a marker if allowed.
	/// @param SDL_Event Inputs the click event.
	virtual void mouseDown(const SDL_Event &)
	{
		if (!gameBoard.isPlayer() || (!boardEmpty && !lastTile->inPlace()) || gameBoard.isGameOver())
			return;
		placeMarker();
		updatingLabels = true;
	}

	/// @brief Destroys the textures when existing the application.
	void destroyTexture()
	{
		SDL_DestroyTexture(texture1);
		SDL_DestroyTexture(texture2);
	}

	/// @brief A get:er for fetching the correct texture.
	/// @return The current texture.
	SDL_Texture *getTexture() const
	{
		if (gameBoard.getTurn() == common::Turn::firstPlayer)
			return texture1;
		else
			return texture2;
	}

protected:
	/// @brief The protected constructor of the object, which constructs a component and creates the minimax-labels (if enabled).
	/// @param parameter The setup-parameter (enum), which alters between who is player and not.
	/// @param ses The session reference for adding new objects to the session.
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
	/// @brief Places a marker on the game-board in the UI, and sends the same information to the GameBoard-object.
	/// @return True if a marker was successfully placed. Else false.
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

	/// @brief Calls the minimax-methods to determine the best move and updates the labels containing the minimax-values.
	/// @return The suggested minimax-move for the current player.
	int miniMax()
	{
		common::Turn turn = gameBoard.getTurn();
		std::vector<std::vector<int>> matrix = gameBoard.getMatrixCopy();
		MoveScore minimax = MiniMax::minimaxAll(matrix, constants::searchDepth, (turn == common::Turn::firstPlayer));
		minimaxVector = minimax.evaluationVector;
		if (constants::visualizeMinimax)
		{
			if (constants::outputStdOut) {
				for (double d : minimaxVector)
					std::cout << d << ", ";
				std::cout << std::endl;
			}
			updateLabels();
		}
		return minimax.move;
	}

	/// @brief Get:er for closest column based on the mouse position used when the player is inputing a tile.
	/// @return Returns the closest column based on the current mouse-position.
	int getClosestCol() const
	{
		return (mouseX - 50) / 100;
	}

	/// @brief Updates the labels in the session with updated minimax-values.
	void updateLabels()
	{
		if (labelVector.empty())
		{
			return;
		}
		for (int i = 0; i < constants::sizeX; i++)
		{
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << minimaxVector[i];
			labelVector[i]->setText(ss.str());
		}
	}

	// Texture references (player 1 and player 2 marker)
	SDL_Texture *texture1, *texture2;

	// Reference to check whether tile is inplace or not
	Tile *lastTile;

	// Flag indicating if the board is empty
	bool boardEmpty = true;

	// Flag indicating if the game is over
	bool gameOver = false;

	// Flag used for rasing when updating the labels should be done in case of player
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