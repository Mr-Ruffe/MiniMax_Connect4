#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Common.h"

#include <string>

/// @brief Constants and settings used by the objects.
namespace constants
{
    // gResPath-contains the relative path to your resources.
    const std::string gResPath = "./resources/";

    // Size of the board in X and Y tiles.
    const int sizeX = 7;
    const int sizeY = 6;

    // The chosen search-depth when using the minimax algorithm.
    const int searchDepth = 9;

    // Option to visualize the minimax-output in the window.
    const bool visualizeMinimax = true;

    // Option to output information in the stdout window (terminal).
    const bool outputStdOut = false;

    // Option to select which colors to be played by a player.
    const common::SetupParameter playerParamater = common::SetupParameter::secondPlayer;
}

#endif