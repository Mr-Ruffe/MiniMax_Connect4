# Minimax algorithm for Connect-4

This is a course-assignment with the goal to implement a minimax algoritm on a simple game. The chosen game is Connect-4, since it is a simple and fun game with interesting logics.

## Requirements
  * C++ 17
  * MinGW64 GCC
  * SDL2
    * SDL_image
    * SDL_ttf
    * SDL_mixer

## How to play

## Minimax algorithm

### Alpha-beta pruning

### Prioritizing better moves
The pattern for the minimax algoritm is giving the middle options before the outer options. This acts as an improvement on the minimax, since this allows better moves to be evaluated first, meaning that less good moves can be pruned ahead of time.

### Improving maximize/minimize moves