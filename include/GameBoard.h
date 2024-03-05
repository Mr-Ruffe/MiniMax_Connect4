#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Common.h"
#include "Constants.h"
#include "GameLogic.h"

#include <iostream>
#include <iomanip>
#include <vector>

/// @brief The game-board object containing the integer matrix and the interface that the player is using to interract with the game.
class GameBoard
{
public:
    /// @brief Constructor for the GameBoard-object.
    /// @param parameter The setup-parameter for who is played by who (computer or player).
    GameBoard(const common::SetupParameter parameter) : parameter(parameter)
    {
        matrix.resize(constants::sizeX, std::vector<int>(constants::sizeY, 0));
    }

    /// @brief Find a suitable tile to place a marker at (doesn't place it).
    /// @param index Column-index where the marker should be placed.
    /// @return Row-index for where the marker can be placed. -1 if column is full.
    int peekMarker(int index)
    {
        for (int row = 0; row < constants::sizeY; row++)
        {
            if (matrix[index][row] == 0)
            {
                return row;
            }
        }
        return -1;
    }

    /// @brief Places a marker at index (if possible).
    /// @param index Column-index where the marker should be placed.
    /// @return Row-index for where the marker can be placed. -1 if column is full.
    int placeMarker(int index)
    {
        int row = peekMarker(index);
        if (row != -1)
        {
            if (turn == common::Turn::firstPlayer)
                matrix[index][row] = 1;
            else
                matrix[index][row] = -1;
            GameLogic::printMatrix(matrix);
            if (!checkGameOver(index))
                changeTurn();
        }
        return row;
    }

    /// @brief Changes the turns between player 1 and player 2
    void changeTurn()
    {
        turn = (turn == common::Turn::firstPlayer) ? common::Turn::secondPlayer : common::Turn::firstPlayer;
    }

    /// @brief Get:er for whose turn it is.
    /// @return The turn of the current player.
    common::Turn getTurn() const
    {
        return turn;
    }

    /// @brief Check if the current turn is supposed to be played by a player.
    /// @return Returns true if the current turn is supposed to be performed by a player.
    bool isPlayer() const
    {
        switch (parameter)
        {
        case common::SetupParameter::bothPlayer:
            return true;
        case common::SetupParameter::firstPlayer:
            if (turn == common::Turn::firstPlayer)
                return true;
            else
                return false;
        case common::SetupParameter::secondPlayer:
            if (turn == common::Turn::secondPlayer)
                return true;
            else
                return false;
        case common::SetupParameter::noPlayer:
            return false;
        }
        return false;
    }

    /// @brief Get:er of the raw integer gameboard, creating a copy of it.
    /// @return Returns a copy of the raw integer gameboard.
    std::vector<std::vector<int>> getMatrixCopy()
    {
        return matrix;
    }

    /// @brief Get:er for if game is over.
    /// @return True if game is over. Otherwise false.
    bool isGameOver()
    {
        return gameOver;
    }

private:
    /// @brief Check if game is over (someone has won, or gameboard is full).
    /// @param index Column-index of the last placed tile.
    /// @return True if game is over. Otherwise false.
    bool checkGameOver(int index)
    {
        if (GameLogic::gameOver(matrix, index))
        {
            gameOver = true;
            std::cout << "Game Over!" << std::endl;
            int win = GameLogic::checkWin(matrix, index);
            if (win == 1)
                std::cout << "Green";
            else if (win == -1)
                std::cout << "Red";
            else
                std::cout << "No";
            std::cout << " player has won!" << std::endl;
        }
        return gameOver;
    }

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