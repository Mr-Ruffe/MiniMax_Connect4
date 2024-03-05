#ifndef MINI_MAXI_H
#define MINI_MAXI_H

#include "Common.h"
#include "Constants.h"

#include <vector>

/// @brief The struct containing information on what move is preferred and not.
struct MoveScore
{
    /// @brief Constructor for the MoveScore.
    /// @param evaluation A score between -2.0 and 2.0 giving an idea on how good the suggested move is.
    /// @param move The column index of the current index.
    MoveScore(double evaluation, int move);

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
    static MoveScore minimaxAll(std::vector<std::vector<int>> matrix, int depth, bool maximizingPlayer);

    /// @brief Recursive minimax function with added alpha-beta-pruning.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param move The column index of the current index.
    /// @param maximizingPlayer Indicator if the player is 1 or -1 (true or false).
    /// @param depth The reamaining depth of the current search.
    /// @param alpha Alpha parameter for pruning.
    /// @param beta Beta parameter for pruning.
    /// @return The evaluation of the current move.
    static double minimax(std::vector<std::vector<int>> matrix, int move, bool maximizingPlayer, int depth, double alpha, double beta);

private:
    /// @brief Main method for evaluating the outcome of the planned move.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param turnsLeft How many turns are left with the current evaluation.
    /// @param lastMove Column index of the last move.
    /// @return A float indicating the score of the chosen move.
    static double evaluate(const std::vector<std::vector<int>> &matrix, int turnsLeft, int lastMove);

    /// @brief Gives a score on the status of the matrix when it's not decided based on amount of possible wins.
    /// @param matrix Reference to the raw integer gameboard.
    /// @return A float indicating the score of the chosen move.
    static double evaluateScore(const std::vector<std::vector<int>> &matrix);

    /// @brief Finds the amount of possible wins for chosen player.
    /// @param maximizingPlayer Indicator if the player is 1 or -1 (true or false).
    /// @param matrix Reference to the raw integer gameboard.
    /// @return The amount of possible wins for the chosen player.
    static int findAmountOfWins(bool maximizingPlayer, const std::vector<std::vector<int>> &matrix);

    /// @brief Places a marker on the chosen column by the indicated player.
    /// @param matrix Reference to the raw integer gameboard.
    /// @param column Column index of the chosen move.
    /// @param maximizingPlayer Indicator if the player is 1 or -1 (true or false).
    static void placeMarker(std::vector<std::vector<int>> &matrix, int column, bool maximizingPlayer);
};

#endif