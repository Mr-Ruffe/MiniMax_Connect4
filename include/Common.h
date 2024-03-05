#ifndef COMMON_H
#define COMMON_H

/// @brief Common pre-definitions used by multiple instances in interfaces.
namespace common
{
    /// @brief Indicates which player is currently playing.
    enum class Turn
    {
        firstPlayer,
        secondPlayer
    };

    /// @brief Indicates if a player is played by the computer or by a player.
    enum class SetupParameter
    {
        firstPlayer,
        secondPlayer,
        bothPlayer,
        noPlayer
    };

};

#endif