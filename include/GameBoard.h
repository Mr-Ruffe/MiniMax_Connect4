#ifndef GAME_BOARD_H
#define GAME_BOARD_H

#include "Common.h"
#include "Constants.h"

#include <iostream>

class GameBoard
{
public:
    GameBoard(const common::SetupParameter parameter) : parameter(parameter) {
        
    }

    // Function to print the matrix
    void printMatrix() {
        for (int j = constants::sizeY-1; j >= 0; --j) {
            for (int i = 0; i < constants::sizeX; ++i) {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    // Find a suitable tile to place a marker at
    int peekMarker(int index) {
        for (int row = 0; row < constants::sizeY; row++) {
            if (matrix[index][row] == 0) {
                return row;
            }
        }
        return -1;
    }

    // Place a marker at index. If full, return -1, else return row and switch turn
    int placeMarker(int index) {
        int row = peekMarker(index);
        if (row != -1) {
            if (turn == common::Turn::firstPlayer)
                matrix[index][row] = 1;
            else
                matrix[index][row] = 2;
            changeTurn();
            printMatrix();
            return row;
        }
        return row;
    }

    bool placeMinMaxMarker(int &col, int &row) {
        col = 5;
        row = placeMarker(col);
        return (row != -1);
    }

    // Changes the turns between player 1 and player 2
    void changeTurn() {
        turn = (turn == common::Turn::firstPlayer) ? common::Turn::secondPlayer : common::Turn::firstPlayer;
    }

    // Returns whose turn it is
    common::Turn getTurn() const {
        return turn;
    }

    // Returns true if the current turn is supposed to be performed by a player
    bool isPlayer() const {
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

private:
    // Indicates who is a player, and who is played by the computer
    const common::SetupParameter parameter;

    // Indicates whose turn it is
    common::Turn turn = common::Turn::firstPlayer;

    // GameBoard
    int matrix[constants::sizeX][constants::sizeY] = {0};

};

#endif