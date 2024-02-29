#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>
#include <iostream>
#include <iomanip>

#include "Constants.h"

class GameLogic {
public:
    // Function to print the matrix to std::cout
    static void printMatrix(const std::vector<std::vector<int>> &matrix) {
        for (int j = constants::sizeY-1; j >= 0; --j) {
            for (int i = 0; i < constants::sizeX; ++i) {
                std::cout << std::setw(3) << matrix[i][j];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Function to check if game is over
    static bool gameOver(const std::vector<std::vector<int>> &matrix)
    { // (&matrix)
        // Check if board is full
        bool full = true;
        for (int index = 0; index < constants::sizeX; index++)
        {
            if (matrix[index][constants::sizeY-1] == 0)
                full = false;
        }
        if (full)
            return true;

        int win = checkWin(matrix);
        if (win != 0)
            return true;

        return false;
    }

    // Function to check if a player has won the game
    static int checkWin(const std::vector<std::vector<int>> &matrix)
    {
        // Check horizontally
        for (int j = 0; j < constants::sizeY; j++)
        {
            int counter = 0;
            int current = 0;
            for (int i = 0; i < constants::sizeX; i++)
            {
                if (current == matrix[i][j] && matrix[i][j] != 0) 
                    counter++;
                else {
                    counter = 1;
                    current = matrix[i][j];
                }
                if (counter >= 4) {
                    return current;
                } 
            }
        }

        // Check vertically
        for (int i = 0; i < constants::sizeX; i++)
        {
            int counter = 0;
            int current = 0;
            for (int j = 0; j < constants::sizeY; j++)
            {
                if (current == matrix[i][j] && matrix[i][j] != 0) 
                    counter++;
                else {
                    counter = 1;
                    current = matrix[i][j];
                }
                if (counter >= 4) {
                    return current;
                }
            }
        }

        // Check diagonally
        int diagonalMaxIndex = (constants::sizeX-4) + (constants::sizeY-4);
        
        for (int k = 0; k < diagonalMaxIndex; k++) {
            int counterBottomLeft = 0;
            int currentBottomLeft = 0;
            int counterBottomRight = 0;
            int currentBottomRight = 0;
            for (int i = 3+k; i >= 0; i--) {
                int j = 3+k-i;
                if (i < constants::sizeX && j < constants::sizeY && j >= 0) {
                    // Bottom-left -> top-right
                    if (currentBottomLeft == matrix[i][j] && matrix[i][j] != 0) 
                        counterBottomLeft++;
                    else {
                        counterBottomLeft = 1;
                        currentBottomLeft = matrix[i][j];
                    }
                    if (counterBottomLeft >= 4) {
                        return currentBottomLeft;
                    }
                    // Bottom-right -> top-left
                    int iRight = constants::sizeX-i-1;
                    if (currentBottomRight == matrix[iRight][j] && matrix[iRight][j] != 0) 
                        counterBottomRight++;
                    else {
                        counterBottomRight = 1;
                        currentBottomRight = matrix[iRight][j];
                    }
                    if (counterBottomRight >= 4) {
                        return currentBottomRight;
                    }
                }
            }
        }

        // No player has won yet
        return 0;
    }

    // Function to retrieve possible moves
    static std::vector<int> getPossibleMoves(const std::vector<std::vector<int>> &matrix)
    {
        std::vector<int> moves;
        int middle = constants::sizeX/2;
        for (int index = 0; index < constants::sizeX; index++)
        {
            int indexNew = middle + (index+1)/2*((index % 2 == 0) ? 1 : -1);
            if (matrix[indexNew][constants::sizeY-1] == 0)
                moves.push_back(indexNew);
        }
        return moves;
    }

};

#endif