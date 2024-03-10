#include "MiniMax.h"
#include "GameLogic.h"
#include "GameBoard.h"

MoveScore MiniMax::minimaxAll(std::vector<std::vector<int>> matrix, int depth, bool maximizingPlayer)
{
    if (constants::outputStdOut)
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

double MiniMax::minimax(std::vector<std::vector<int>> matrix, int move, bool maximizingPlayer, int depth, double alpha, double beta)
{
    // Place marker from current move
    placeMarker(matrix, move, maximizingPlayer);

    // Verify if depth is reached or game is over
    if (depth <= 0 || GameLogic::gameOver(matrix, move))
    {
        // Return evaluation score if game is over
        return evaluate(matrix, depth, move);
    }

    // Start next move
    maximizingPlayer = !maximizingPlayer;

    // Making the move based on whether player is maximizing or not
    if (maximizingPlayer)
    {
        // Sets bestEval to something smaller than reasonable
        double bestEval{-2.0};

        // Iterate through possible moves
        for (int move : GameLogic::getPossibleMoves(matrix))
        {
            // Evaluate score for the possible move recursively
            double eval = minimax(matrix, move, maximizingPlayer, depth - 1, alpha, beta);
            // Store the best possible move, which is the largest move
            bestEval = std::max(eval, bestEval);
            // Store the best move from a maximizing perspective in alpha
            alpha = std::max(alpha, eval);
            // Compare beta & alpha - if move is already determined to be pruned: break
            if (beta <= alpha)
                break;
        }
        // Return best evaluation
        return bestEval;
    }
    else
    {
        // Sets bestEval to something larger than reasonable
        double bestEval{2.0};

        // Iterate through possible moves
        for (int move : GameLogic::getPossibleMoves(matrix))
        {
            // Evaluate score for the possible move recursively
            double eval = minimax(matrix, move, maximizingPlayer, depth - 1, alpha, beta);
            // Store the best possible move, which is the smallest move
            bestEval = std::min(eval, bestEval);
            // Store the best move from a minimizing perspective in beta
            beta = std::min(beta, eval);
            // Compare beta & alpha - if move is already determined to be pruned: break
            if (beta <= alpha)
                break;
        }
        // Return best evaluation
        return bestEval;
    }
}

double MiniMax::evaluate(const std::vector<std::vector<int>> &matrix, int turnsLeft, int lastMove)
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

double MiniMax::evaluateScore(const std::vector<std::vector<int>> &matrix)
{
    int amountOfMaxiWins = findAmountOfWins(true, matrix);
    int amountOfMiniWins = findAmountOfWins(false, matrix);

    if (amountOfMaxiWins + amountOfMiniWins != 0)
        return static_cast<double>(amountOfMaxiWins - amountOfMiniWins) / (amountOfMaxiWins + amountOfMiniWins);
    else
        return 0.0;
}

int MiniMax::findAmountOfWins(bool maximizingPlayer, const std::vector<std::vector<int>> &matrix)
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

void MiniMax::placeMarker(std::vector<std::vector<int>> &matrix, int column, bool maximizingPlayer)
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

MoveScore::MoveScore(double evaluation, int move) : evaluation(evaluation), move(move)
{
    evaluationVector.resize(constants::sizeX, 0.0);
}