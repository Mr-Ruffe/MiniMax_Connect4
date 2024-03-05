#ifndef PLAYERS_H
#define PLAYERS_H

#include "Session.h"
#include "Component.h"
#include "Label.h"

#include "Tile.h"
#include "GameBoard.h"


/// @brief The front-end controller, manipulating the gameboard based on player/computer input.
class Players : public Component
{
public:
	/// @brief Acts as a constructor and restricts the user to create Players-objects in other ways.
	/// @param ses the session-reference where the object can create new objects.
	/// @return A new Players-instance.
	static Players *getInstance(Session &ses);

	/// @brief Destructor of Players, destroying allocated data.
	virtual ~Players();

	/// @brief Called from Session every tick. Updates position and acts as initator for non-player players.
	virtual void tick();

	/// @brief Called every tick for updating the object in the renderer.
	virtual void draw() const;

	/// @brief Called when mouse down is pressed. Places a marker if allowed.
	/// @param SDL_Event Inputs the click event.
	virtual void mouseDown(const SDL_Event &);

	/// @brief Destroys the textures when existing the application.
	void destroyTexture();

	/// @brief A get:er for fetching the correct texture.
	/// @return The current texture.
	SDL_Texture *getTexture() const;

protected:
	/// @brief The protected constructor of the object, which constructs a component and creates the minimax-labels (if enabled).
	/// @param parameter The setup-parameter (enum), which alters between who is player and not.
	/// @param ses The session reference for adding new objects to the session.
	Players(common::SetupParameter parameter, Session &ses);

private:
	/// @brief Places a marker on the game-board in the UI, and sends the same information to the GameBoard-object.
	/// @return True if a marker was successfully placed. Else false.
	bool placeMarker();

	/// @brief Calls the minimax-methods to determine the best move and updates the labels containing the minimax-values.
	/// @return The suggested minimax-move for the current player.
	int miniMax();

	/// @brief Get:er for closest column based on the mouse position used when the player is inputing a tile.
	/// @return Returns the closest column based on the current mouse-position.
	int getClosestCol() const;

	/// @brief Updates the labels in the session with updated minimax-values.
	void updateLabels();

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