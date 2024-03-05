#include <iomanip>
#include <iostream>

#include "GameBoard.h"
#include "GameLogic.h"
#include "Constants.h"

GameBoard::GameBoard(const common::SetupParameter parameter) : parameter(parameter)
{
    matrix.resize(constants::sizeX, std::vector<int>(constants::sizeY, 0));
}

int GameBoard::peekMarker(int index)
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

int GameBoard::placeMarker(int index)
{
    int row = peekMarker(index);
    if (row != -1)
    {
        if (turn == common::Turn::firstPlayer)
            matrix[index][row] = 1;
        else
            matrix[index][row] = -1;
        if (constants::outputStdOut)
            GameLogic::printMatrix(matrix);
        if (!checkGameOver(index))
            changeTurn();
    }
    return row;
}

void GameBoard::changeTurn()
{
    turn = (turn == common::Turn::firstPlayer) ? common::Turn::secondPlayer : common::Turn::firstPlayer;
}

common::Turn GameBoard::getTurn() const
{
    return turn;
}

bool GameBoard::isPlayer() const
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

std::vector<std::vector<int>> GameBoard::getMatrixCopy()
{
    return matrix;
}

bool GameBoard::isGameOver()
{
    return gameOver;
}

bool GameBoard::checkGameOver(int index)
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
