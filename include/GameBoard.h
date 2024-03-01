#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Common.h"
#include "Constants.h"
#include "GameLogic.h"

#include <iostream>
#include <iomanip>
#include <vector>

class GameBoard
{
public:
    GameBoard(const common::SetupParameter parameter) : parameter(parameter)
    {
        matrix.resize(constants::sizeX, std::vector<int>(constants::sizeY, 0));
    }

    // Find a suitable tile to place a marker at
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

    // Place a marker at index. If full, return -1, else return row and switch turn
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
            if (!checkGameOver())
                changeTurn();
        }
        return row;
    }

    // Changes the turns between player 1 and player 2
    void changeTurn()
    {
        turn = (turn == common::Turn::firstPlayer) ? common::Turn::secondPlayer : common::Turn::firstPlayer;
    }

    // Returns whose turn it is
    common::Turn getTurn() const
    {
        return turn;
    }

    // Returns true if the current turn is supposed to be performed by a player
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

    std::vector<std::vector<int>> getMatrixCopy() {
        return matrix;
    }

    bool isGameOver() {
        return gameOver;
    }

private:

    bool checkGameOver() {
        if (GameLogic::gameOver(matrix)) {
            gameOver = true;
            std::cout << "Game Over!" << std::endl;
            int win = GameLogic::checkWin(matrix);
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

    // GameBoard
    std::vector<std::vector<int>> matrix;

    bool gameOver = false;
};

#endif