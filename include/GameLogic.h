#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>

/// GameLogic is a class containing the static functions used checking gameboard logic.

class GameLogic
{
public:
    /// @brief Function to print the gameboard-matrix to std::cout.
    /// @param matrix Reference to the raw integer gameboard.
    static void printMatrix(const std::vector<std::vector<int>> &matrix);

    /// @brief Function to check if game is over.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param move Column index of the last performed move.
    /// @return True if game is over. Otherwise false.
    static bool gameOver(const std::vector<std::vector<int>> &matrix, int move);

    /// @brief Check if board is full.
    /// @param matrix Reference to the raw integer gameboard.
    /// @return True if board is full. Otherwise false.
    static bool checkBoardFull(const std::vector<std::vector<int>> &matrix);

    /// @brief Function to check if a player has won the game with added move.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param column The column index of the last performed move.
    /// @return 1 if first player has won, -1 if second player has won, 0 if no player has won.
    static int checkWin(const std::vector<std::vector<int>> &matrix, int column);

    /// @brief Function to retrieve possible moves, with the most central moves first.
    /// @param matrix Reference to the raw integer gameboard.
    /// @return A vector of all potential moves, with the most central ones first.
    static std::vector<int> getPossibleMoves(const std::vector<std::vector<int>> &matrix);

private:
    /// @brief Find the row of the last placed tile.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param column The column index of the last performed move.
    /// @return The row index of the last performed move.
    static int findLastMoveRow(const std::vector<std::vector<int>> &matrix, int column);
};

#endif