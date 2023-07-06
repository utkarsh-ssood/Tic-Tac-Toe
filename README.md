# Unbeatable Tic-Tac-Toe AI using Minimax Backtracking Algorithm

This project features a Tic-Tac-Toe AI program implemented in C++ that never loses to the human player. It utilizes the minimax algorithm to efficiently search through the game tree and make optimal moves.

## Usage        

To use this program, ensure you have a C++ compiler supporting C++14. Simply compile and run the source code to start playing against the unbeatable AI.

## Algorithm Details

The minimax algorithm is a recursive decision-making algorithm commonly used in two-player games. In this implementation, each game state is associated with a value indicating its desirability for a player. The algorithm evaluates all possible moves and selects the best move by maximizing the minimum value of the resulting positions from the opponent's moves.

## Key principles of the tic-tac-toe variant of the minimax algorithm are as follows:

* If the AI can win in one move, it chooses the winning move.
* If the opponent can win in one move, it blocks the opponent's winning move.
* Otherwise, it selects the move that maximizes the minimum value of the resulting positions.

## Pseudocode
The pseudocode for the minimax algorithm is as follows:

```
function minimax(node, isMaximizingPlayer):
    if node is a terminal node:
        return value of the node
        
    if isMaximizingPlayer:
        bestVal = -INFINITY 
        for each child node:
            value = minimax(childNode, false)
            bestVal = max(bestVal, value) 
        return bestVal
    else:
        bestVal = +INFINITY 
        for each child node:
            value = minimax(childNode, true)
            bestVal = min(bestVal, value) 
        return bestVal

```
To initiate the algorithm, call the minimax function with the initial parameters:
```
minimax(initialNode, true)
```

## Minimax Algorithm Visualization
![Image](https://github.com/utkarsh-ssood/Tic-Tac-Toe/assets/122226447/495e0827-1727-40ae-88f0-332116af29e6)

## Conclusion
This tic-tac-toe AI program demonstrates the effectiveness of the minimax algorithm in creating an unbeatable opponent. \
For more information on the minimax algorithm and Tic-Tac-Toe game, you can refer to the following resources:\
[Tic-Tac-Toe Introduction](https://en.wikipedia.org/wiki/Tic-tac-toe)\
[Introduction to the Minimax Algorithm](https://www.geeksforgeeks.org/minimax-algorithm-in-game-theory-set-1-introduction/)\
[Understanding the Minimax Algorithm](https://www.freecodecamp.org/news/minimax-algorithm-guide-how-to-create-an-unbeatable-ai/)
