#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "Constants.h"

/// GameLogic is a class containing the static functions used checking gameboard logic.

class GameLogic
{
public:
    /// @brief Function to print the gameboard-matrix to std::cout.
    /// @param matrix Reference to the raw integer gameboard.
    static void printMatrix(const std::vector<std::vector<int>> &matrix)
    {
        for (int j = constants::sizeY - 1; j >= 0; --j)
        {
            for (int i = 0; i < constants::sizeX; ++i)
            {
                std::cout << std::setw(3) << matrix[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    /// @brief Function to check if game is over.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param move Column index of the last performed move.
    /// @return True if game is over. Otherwise false.
    static bool gameOver(const std::vector<std::vector<int>> &matrix, int move)
    {
        if (checkBoardFull(matrix))
            return true;

        int win = checkWin(matrix, move);
        if (win != 0)
            return true;

        return false;
    }

    /// @brief Check if board is full.
    /// @param matrix Reference to the raw integer gameboard.
    /// @return True if board is full. Otherwise false.
    static bool checkBoardFull(const std::vector<std::vector<int>> &matrix)
    {
        for (int index = 0; index < constants::sizeX; index++)
        {
            if (matrix[index][constants::sizeY - 1] == 0)
                return false;
        }
        return true;
    }

    /// @brief Function to check if a player has won the game with added move.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param column The column index of the last performed move.
    /// @return 1 if first player has won, -1 if second player has won, 0 if no player has won.
    static int checkWin(const std::vector<std::vector<int>> &matrix, int column)
    {
        int row = findLastMoveRow(matrix, column);

        int playerMarker = matrix[column][row];

        // Vertical
        if (row >= 3)
        {
            bool won = true;
            for (int j = row; j >= row - 3; j--)
            {
                if (matrix[column][j] != playerMarker)
                {
                    won = false;
                    break;
                }
            }
            if (won)
                return playerMarker;
        }

        // Horizontal
        int left = 0, right = 0;
        for (int i = column + 1; i <= std::min(constants::sizeX - 1, column + 3); i++)
        {
            if (matrix[i][row] == playerMarker)
                right++;
            else
                break;
        }
        for (int i = column - 1; i >= std::max(0, column - 3); i--)
        {
            if (matrix[i][row] == playerMarker)
                left++;
            else
                break;
        }
        if (left + right + 1 >= 4)
            return playerMarker;

        // Diagonal TL -> BR
        left = 0, right = 0;
        for (int i = 1; i <= 3; i++)
        {
            if (column + i >= constants::sizeX || row - i < 0)
                break;
            if (matrix[column + i][row - i] == playerMarker)
                right++;
            else
                break;
        }
        for (int i = 1; i <= 3; i++)
        {
            if (column - i < 0 || row + i >= constants::sizeY)
                break;
            if (matrix[column - i][row + i] == playerMarker)
                right++;
            else
                break;
        }
        if (left + right + 1 >= 4)
            return playerMarker;

        // Diagonal TR -> BL
        left = 0, right = 0;
        for (int i = 1; i <= 3; i++)
        {
            if (column - i < 0 || row - i < 0)
                break;
            if (matrix[column - i][row - i] == playerMarker)
                right++;
            else
                break;
        }
        for (int i = 1; i <= 3; i++)
        {
            if (column + i >= constants::sizeX || row + i >= constants::sizeY)
                break;
            if (matrix[column + i][row + i] == playerMarker)
                right++;
            else
                break;
        }
        if (left + right + 1 >= 4)
            return playerMarker;

        // No player has won
        return 0;
    }

    /// @brief Function to retrieve possible moves, with the most central moves first.
    /// @param matrix Reference to the raw integer gameboard.
    /// @return A vector of all potential moves, with the most central ones first.
    static std::vector<int> getPossibleMoves(const std::vector<std::vector<int>> &matrix)
    {
        std::vector<int> moves;
        int middle = constants::sizeX / 2;
        for (int index = 0; index < constants::sizeX; index++)
        {
            int indexNew = middle + (index + 1) / 2 * ((index % 2 == 0) ? 1 : -1);
            if (matrix[indexNew][constants::sizeY - 1] == 0)
                moves.push_back(indexNew);
        }
        return moves;
    }

private:
    /// @brief Find the row of the last placed tile.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param column The column index of the last performed move.
    /// @return The row index of the last performed move.
    static int findLastMoveRow(const std::vector<std::vector<int>> &matrix, int column)
    {
        for (int j = 1; j < constants::sizeY; j++)
        {
            if (matrix[column][j] == 0)
            {
                return j - 1;
            }
        }
        return constants::sizeY - 1;
    }
};

#endif