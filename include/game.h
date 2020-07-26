#include "board.h"

/* 
    1. A game is a sequence of boards and the matchBox move 
       better implemented as std::vector<{Board, int move}> called game.record
       move will be associated with a position on the configuration
                This is the most important property in the object's lifetime
    2. Some of the (other) private properties it will have:
        - bool game.is_over() == bool game.human_wins() || bool game.matchbox_wins()
        - string turn, which is either "human" or "matchbox"
    3. Some of the public methods it will have:
        - Game (constructor) takes no argument and decided who plays first:
            initializing game.turn
        - void game.start_game() Keeps printing the board 
            and prompting the player for their move, until game.is_over
    4 Some of the private methods it will have:
        - void game.change_turns()
        - void game.matchbox_play() 
            (This move will be determined by the weights of the Board)
        - void game.human_play(int move) 
            (Where move will be provided by the player)
        - void game.play() This looks up who's turn 
            and executes either one of the above methods
        - void game.adjust_weights() This updates the weights in each played Board
            and updates the corresponding file, according to following:
                a. If game.human_wins, decrease all weights of moves played by 1, 
                    unless one of them is 0.
                b. If game.matchbox_wins, increase all weights of moves played by 2
                c If it's a draw, increase all weights of moves played by 1
            (This is meant to be executed after game.is_over)
    5. The basic idea of the game.start_game() method is:
        while (!game.is_over) {
            game.play();
        }
        game.adjust_weights();
*/