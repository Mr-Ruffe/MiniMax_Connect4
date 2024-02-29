#ifndef MINI_MAXI_H
#define MINI_MAXI_H

#include "Common.h"
#include "Constants.h"
#include "GameBoard.h"
#include "GameLogic.h"

#include <vector>

struct MoveScore {
    MoveScore(double evaluation, int move) : evaluation(evaluation), move(move) {
        evaluationVector.resize(constants::sizeX, 0.0);
    }
    double evaluation;
    int move;
    std::vector<double> evaluationVector; 
};

class MiniMax
{
public:
    static MoveScore minimaxAll(std::vector<std::vector<int>> matrix, int depth, bool maximizingPlayer) {
        // TODO: include alpha-beta?
        GameLogic::printMatrix(matrix);
        MoveScore bestEval{2.0*(maximizingPlayer ? -1 : 1), 0};
        for (int move : GameLogic::getPossibleMoves(matrix))
            {
                double eval = minimax(placeMarker(matrix, move, maximizingPlayer), depth-1, -2.0, 2.0, !maximizingPlayer);
                bestEval.evaluationVector[move] = eval;
                if (eval > bestEval.evaluation && maximizingPlayer || eval < bestEval.evaluation && !maximizingPlayer) {
                    bestEval.evaluation = eval;
                    bestEval.move = move;
                }
            }
        return bestEval;
    }

    static double minimax(std::vector<std::vector<int>> matrix, int depth, double alpha, double beta, bool maximizingPlayer)
    {
        //printMatrix(matrix);
        if (depth == 0 || GameLogic::gameOver(matrix))
        {
            return evaluate(matrix);
        }

        if (maximizingPlayer)
        {
            double bestEval{-2.0};
            for (int move : GameLogic::getPossibleMoves(matrix))
            {
                double eval = minimax(placeMarker(matrix, move, maximizingPlayer), depth - 1, alpha, beta, false);
                bestEval = std::max(eval, bestEval);
                alpha = std::max(alpha, eval);
                if (beta <= alpha) 
                    break;
            }
            return bestEval;
        }
        else
        {
            double bestEval{2.0};
            for (int move : GameLogic::getPossibleMoves(matrix))
            {
                double eval = minimax(placeMarker(matrix, move, maximizingPlayer), depth - 1, alpha, beta, true);
                bestEval = std::min(eval, bestEval);
                beta = std::min(beta, eval);
                if (beta <= alpha)
                    break;
            }
            return bestEval;
        }
    }

private:
    static double evaluate(const std::vector<std::vector<int>> &matrix)
    {
        int win = GameLogic::checkWin(matrix);
        if (win == 1)
            return 1.0;
        else if (win == -1)
            return -1.0;
        else 
            return evaluateScore(matrix);
    }

    static double evaluateScore(const std::vector<std::vector<int>> &matrix) {
        double score = 0.0;
        
        // Check horizontally
        for (int j = 0; j < constants::sizeY; j++)
        {
            int counter = 0;
            int current = 0;
            bool freeBefore = false;
            bool freeAfter = false;
            for (int i = 0; i < constants::sizeX; i++)
            {
                if (current == matrix[i][j] && matrix[i][j] != 0) 
                    counter++;
                else {
                    if (counter >= 2)
                        score += calculateScore(counter, current, freeBefore, matrix[i][j]==0);
                    counter = 1;
                    current = matrix[i][j];
                    if (matrix[i][j] == 0)
                        freeBefore = true;
                    else
                        freeBefore = false;
                }
            }
        }

        // Check vertically
        for (int i = 0; i < constants::sizeX; i++)
        {
            int counter = 0;
            int current = 0;
            bool freeBefore = false;
            bool freeAfter = false;
            for (int j = 0; j < constants::sizeY; j++)
            {
                if (current == matrix[i][j] && matrix[i][j] != 0) 
                    counter++;
                else {
                    if (counter >= 2)
                        score += calculateScore(counter, current, freeBefore, matrix[i][j]==0);
                    counter = 1;
                    current = matrix[i][j];
                    if (matrix[i][j] == 0)
                        freeBefore = true;
                    else
                        freeBefore = false;
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
            for (int i = 3+k; i > 0; i--) {
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
                    int iRight = constants::sizeX-i;
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
        return score;
    }

    static double calculateScore(int counter, int current, bool freeBefore, bool freeAfter) {
        // Free 3s (+0.05 per side)
        // Free 3s (-0.05 per side)
        // Free 2s (+0.02 per side)
        // Free 2s (-0.02 per side)
        double free = 0.02;
        if (counter > 2)
            free = 0.05;
        return free*current*((freeBefore && freeAfter) ? 1 : 2);
    }

    static std::vector<std::vector<int>> placeMarker(std::vector<std::vector<int>> matrix, int column, bool maximizingPlayer) {
        
        for (int row = 0; row < constants::sizeY; row++) {
            if (matrix[column][row] == 0) {
                if (maximizingPlayer)
                    matrix[column][row] = 1;
                else
                    matrix[column][row] = -1;
                break;
            }
        }
        return matrix;
    }
};

#endif