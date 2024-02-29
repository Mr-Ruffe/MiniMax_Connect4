#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "Common.h"

#include <string>

namespace constants
{
    //gResPath-contains the relative path to your resources.
    const std::string gResPath = "./resources/";

    const int sizeX = 7;
    const int sizeY = 6;

    const int searchDepth = 9;

    const bool visualizeMinimax = true;

    const common::SetupParameter playerParamater = common::SetupParameter::firstPlayer;
}

#endif