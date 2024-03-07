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
The project is compiled with ```make```. Then the whole folder structure in the build cathalog is formulated, med build/debug/resources, as well as the copy of all the resources to the build-folder (in case one wants to run the game straight through the ```play.exe``` binary). After that you can execute the ```play.exe```, or via the terminal: (```./build/debug/play``` alternatively ```cd build/debug``` and ```./play```). The game window should then appear.

![](/doc/images/readme_1.PNG)

in ```include/Constants.h``` the options are setup who should be played by a player. First player means playing for green, and second player for red. 

The player places the marker by using the mouse and click on the tile where to place the marker. The marker will then fall into place, and the turn is changed.

### Game over!
The game is over either when the board is completely full, or when someone has gotten 4 in a row, either diagonally, horizontally or vertically. The outcome is displayed in the terminal as shown.
```
Game Over!
Green player has won!
```
## Minimax algorithm
The Minimax algorithm is a decision-making algorithm used in game theory and decision theory for minimizing the possible loss for a worst-case scenario. It's doing so by doing moves down to a certain depth and analyzes the outcome from there. Since the game is played by alternating between two players, the 

The algorithm can be can be activated for both the player and the computer, visaulizing the numbers below the board on the base as shown below. 
![](/doc/images/readme_minimax.PNG)
The green numbers guarantee a green win, and the red numbers a red win. The numbers displayed is before the green started its move, but since red has 3 in a row in that column, green has to act. As can be seen, this means that green should be guaranteed the win if blocking red.

### Depth
Depth is currently set to a fixed parameter, where a recommended depth would be ~9. 

### Evaluation
The easiest evaluation is if someone has won. The evaluation algorithm is evaluating the latest move in the matrix, and checks whether it can form 4 in a row in some way (diagonally, horizontally and vertically). 

If the game is not determined by the current search-depth, the current state is evaluated. This is done by summing up all the remaining possible places to win vs. to lose, and evaluated such as:

```cpp
return (amountOfMaxiWins - amountOfMiniWins) / (amountOfMaxiWins + amountOfMiniWins);
```

This will generate a ```double``` in the range of  ```[-1.0, 1.0]```, which should indicate how the player is doing.

### Alpha-beta pruning
The idea behind alpha-beta pruning is to reduce the number of nodes that need to be evaluated in the game tree by ignoring branches that are guaranteed to be less important to the final decision. This is achieved by keeping track of two values, alpha and beta, which represent the minimum score that the maximizing player is assured of and the maximum score that the minimizing player is assured of, respectively. 

The graph below describes a scenario where 2 players only have 2 possible moves. 
![](/doc/images/readme_alpha-beta.PNG)
The left sub-tree here is not really affected by the alpha-beta parameters, but if we look at the right side. There, the left option is already estimated to 1.1, while the first node on the right is estimated to 0.2. Since this is already below the other option for Maxi, and Mini will definietly not chose an even higher value than 1.1 on the right side, that section can be pruned (meaning that alpha is more than the current lowest). 

There is no alpha-beta-pruning on the first move, since this wouldn't allow us to see all the results.

### Prioritizing better moves
The pattern for the minimax algoritm is giving the middle options before the outer options. This acts as an improvement on the minimax, since this allows better moves to be evaluated first, meaning that less good moves can be pruned ahead of time.
![](/doc/images/readme_moveprio.PNG)
The figure shows the order that the moves are evaluated in. 


### Improving maximize/minimize moves
A Minimax where the goal is just to win/not to lose might create some weird scenarios. For instance, the algorithm can determine several moves early that the game is over, and end the game before the player has realised what was going on by placing a losing move. The same goes for the winning player, where the game is not ended when having the chance, and instead plays on for a while until there is nothing else to do than win. 

To improve this, the addition of how many moves are left on depth is added. If someone has won, the remaining moves are added to the score by 0.01 per move, meaning that a quicker win or slower loss is preferred. 

### Potential improvments
* Variable depth depending on moves left, since once columns are blocked out, less moves are needed.
* Evaluation is performed too often.