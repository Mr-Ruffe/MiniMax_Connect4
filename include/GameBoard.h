#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include <vector>

#include "Common.h"

/// @brief The game-board object containing the integer matrix and the interface that the player is using to interract with the game.
class GameBoard
{
public:
    /// @brief Constructor for the GameBoard-object.
    /// @param parameter The setup-parameter for who is played by who (computer or player).
    GameBoard(const common::SetupParameter parameter);

    /// @brief Find a suitable tile to place a marker at (doesn't place it).
    /// @param index Column-index where the marker should be placed.
    /// @return Row-index for where the marker can be placed. -1 if column is full.
    int peekMarker(int index);

    /// @brief Places a marker at index (if possible).
    /// @param index Column-index where the marker should be placed.
    /// @return Row-index for where the marker can be placed. -1 if column is full.
    int placeMarker(int index);

    /// @brief Changes the turns between player 1 and player 2
    void changeTurn();

    /// @brief Get:er for whose turn it is.
    /// @return The turn of the current player.
    common::Turn getTurn() const;

    /// @brief Check if the current turn is supposed to be played by a player.
    /// @return Returns true if the current turn is supposed to be performed by a player.
    bool isPlayer() const;

    /// @brief Get:er of the raw integer gameboard, creating a copy of it.
    /// @return Returns a copy of the raw integer gameboard.
    std::vector<std::vector<int>> getMatrixCopy();

    /// @brief Get:er for if game is over.
    /// @return True if game is over. Otherwise false.
    bool isGameOver();

private:
    /// @brief Check if game is over (someone has won, or gameboard is full).
    /// @param index Column-index of the last placed tile.
    /// @return True if game is over. Otherwise false.
    bool checkGameOver(int index);

    // Indicates who is a player, and who is played by the computer
    const common::SetupParameter parameter;

    // Indicates whose turn it is
    common::Turn turn = common::Turn::firstPlayer;

    // The raw integer game-board
    std::vector<std::vector<int>> matrix;

    // Indicating if the game is over or not
    bool gameOver = false;
};

#endif