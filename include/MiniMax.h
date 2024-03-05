#ifndef MINI_MAXI_H
#define MINI_MAXI_H

#include "Common.h"
#include "Constants.h"
#include "GameBoard.h"
#include "GameLogic.h"

#include <vector>

/// @brief The struct containing information on what move is preferred and not.
struct MoveScore
{
    /// @brief Constructor for the MoveScore.
    /// @param evaluation A score between -2.0 and 2.0 giving an idea on how good the suggested move is.
    /// @param move The column index of the current index.
    MoveScore(double evaluation, int move) : evaluation(evaluation), move(move)
    {
        evaluationVector.resize(constants::sizeX, 0.0);
    }

    // The score of the current move (-2.0, 2.0).
    double evaluation;

    // The column index of the current best move index.
    int move;

    // The evaluation vector containing information of all potential moves.
    std::vector<double> evaluationVector;
};

/// @brief The static MiniMax methods used for determining good/bad moves.
class MiniMax
{
public:
    /// @brief Minimax function that initializes the MoveScore displayed in the window.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param depth The reamaining depth of the current search.
    /// @param maximizingPlayer Indicator if the player is 1 or -1 (true or false).
    /// @return MoveScore containing evaluation on all the different moves.
    static MoveScore minimaxAll(std::vector<std::vector<int>> matrix, int depth, bool maximizingPlayer)
    {
        GameLogic::printMatrix(matrix);
        MoveScore bestEval{2.0 * (maximizingPlayer ? -1 : 1), 0};
        for (int move : GameLogic::getPossibleMoves(matrix))
        {
            double eval = minimax(matrix, move, maximizingPlayer, depth - 1, -2.0, 2.0);
            bestEval.evaluationVector[move] = eval;
            if ((eval > bestEval.evaluation && maximizingPlayer) || (eval < bestEval.evaluation && !maximizingPlayer))
            {
                bestEval.evaluation = eval;
                bestEval.move = move;
            }
        }
        return bestEval;
    }

    /// @brief Recursive minimax function with added alpha-beta-pruning.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param move The column index of the current index.
    /// @param maximizingPlayer Indicator if the player is 1 or -1 (true or false).
    /// @param depth The reamaining depth of the current search.
    /// @param alpha Alpha parameter for pruning.
    /// @param beta Beta parameter for pruning.
    /// @return The evaluation of the current move.
    static double minimax(std::vector<std::vector<int>> matrix, int move, bool maximizingPlayer, int depth, double alpha, double beta)
    {
        placeMarker(matrix, move, maximizingPlayer);
        if (depth <= 0 || GameLogic::gameOver(matrix, move))
        {
            return evaluate(matrix, depth, move);
        }

        if (!maximizingPlayer)
        {
            double bestEval{-2.0};
            for (int move : GameLogic::getPossibleMoves(matrix))
            {
                double eval = minimax(matrix, move, !maximizingPlayer, depth - 1, alpha, beta);
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
                double eval = minimax(matrix, move, !maximizingPlayer, depth - 1, alpha, beta);
                bestEval = std::min(eval, bestEval);
                beta = std::min(beta, eval);
                if (beta <= alpha)
                    break;
            }
            return bestEval;
        }
    }

private:
    /// @brief Main method for evaluating the outcome of the planned move.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param turnsLeft How many turns are left with the current evaluation.
    /// @param lastMove Column index of the last move.
    /// @return A float indicating the score of the chosen move.
    static double evaluate(const std::vector<std::vector<int>> &matrix, int turnsLeft, int lastMove)
    {
        int win = GameLogic::checkWin(matrix, lastMove);
        if (win == 1)
            return 1.0 * (1.0 + static_cast<double>(turnsLeft) / 100.0);
        else if (win == -1)
            return -1.0 * (1.0 + static_cast<double>(turnsLeft) / 100.0);
        else if (GameLogic::checkBoardFull(matrix))
            return 0.0;
        else
            return evaluateScore(matrix);
    }

    /// @brief Gives a score on the status of the matrix when it's not decided based on amount of possible wins.
    /// @param matrix Reference to the raw integer gameboard.
    /// @return A float indicating the score of the chosen move.
    static double evaluateScore(const std::vector<std::vector<int>> &matrix)
    {
        int amountOfMaxiWins = findAmountOfWins(true, matrix);
        int amountOfMiniWins = findAmountOfWins(false, matrix);

        if (amountOfMaxiWins + amountOfMiniWins != 0)
            return static_cast<double>(amountOfMaxiWins - amountOfMiniWins) / (amountOfMaxiWins + amountOfMiniWins);
        else
            return 0.0;
    }

    /// @brief Finds the amount of possible wins for chosen player.
    /// @param maximizingPlayer Indicator if the player is 1 or -1 (true or false).
    /// @param matrix Reference to the raw integer gameboard.
    /// @return The amount of possible wins for the chosen player.
    static int findAmountOfWins(bool maximizingPlayer, const std::vector<std::vector<int>> &matrix)
    {
        // Check horizontally
        int amountOfWins = 0;
        for (int j = 0; j < constants::sizeY; j++)
        {
            int counter = 0;
            for (int i = 0; i < constants::sizeX; i++)
            {
                if (matrix[i][j] != (maximizingPlayer ? -1 : 1))
                    counter++;
                else
                {
                    counter = 1;
                }
                if (counter >= 4)
                {
                    amountOfWins++;
                }
            }
        }

        // Check vertically
        for (int i = 0; i < constants::sizeX; i++)
        {
            int counter = 0;
            for (int j = 0; j < constants::sizeY; j++)
            {
                if (matrix[i][j] != (maximizingPlayer ? -1 : 1))
                    counter++;
                else
                {
                    counter = 1;
                }
                if (counter >= 4)
                {
                    amountOfWins++;
                }
            }
        }

        // Check diagonally
        int diagonalMaxIndex = (constants::sizeX - 4) + (constants::sizeY - 4);

        for (int k = 0; k < diagonalMaxIndex; k++)
        {
            int counterBottomLeft = 0;
            int counterBottomRight = 0;
            for (int i = 3 + k; i >= 0; i--)
            {
                int j = 3 + k - i;
                if (i < constants::sizeX && j < constants::sizeY && j >= 0)
                {
                    // Bottom-left -> top-right
                    if (matrix[i][j] != (maximizingPlayer ? -1 : 1))
                        counterBottomLeft++;
                    else
                    {
                        counterBottomLeft = 1;
                    }
                    if (counterBottomLeft >= 4)
                    {
                        amountOfWins++;
                    }
                    // Bottom-right -> top-left
                    int iRight = constants::sizeX - i - 1;
                    if (matrix[iRight][j] != (maximizingPlayer ? -1 : 1))
                        counterBottomRight++;
                    else
                    {
                        counterBottomRight = 1;
                    }
                    if (counterBottomRight >= 4)
                    {
                        amountOfWins++;
                    }
                }
            }
        }
        return amountOfWins;
    }

    /// @brief Places a marker on the chosen column by the indicated player.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param column Column index of the chosen move.
    /// @param maximizingPlayer Indicator if the player is 1 or -1 (true or false).
    static void placeMarker(std::vector<std::vector<int>> &matrix, int column, bool maximizingPlayer)
    {
        for (int row = 0; row < constants::sizeY; row++)
        {
            if (matrix[column][row] == 0)
            {
                if (maximizingPlayer)
                    matrix[column][row] = 1;
                else
                    matrix[column][row] = -1;
                break;
            }
        }
    }
};

#endif