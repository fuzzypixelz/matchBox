#ifndef GAME_H
#define GAME_H

#include "board.h"

/*
    Represents the state of the game board.
    I borrow the term used in filmmaking.
*/
struct Scene {
    /* 
        The board recorded in this scene. 
    */
    Board board;
    /* 
        The index of the move taken on the board. 
    */
    int move;
    /* 
        Specifies the player, uniquely determined by their mark. 
    */
    char mark;
};

/*  
    The human plays with the O mark.
*/
const char human_mark = O;
/*  
    The matchBox plays with the X mark.
*/
const char matchbox_mark = X;
/*
    Reward for winning a game.
*/
const int VICTORY_NUDGE = 2;
/*
    Reward for loosing a game.
*/
const int DEFEAT_NUDGE = -1;
/*
    Reward for ending with a draw.
*/
const int DRAW_NUDGE = 1;   

/*
    A model of a TIC-TAC-TOE game using a sequence of Scenes.
*/
class Game {
    private:
        /*
            This serves as a record of the entire game.
            Again, think of the game as a film.
        */
        vector<Scene> sequence;
        /*  
            Tracks player turns.
            Evaluates to true when it's the human's turn to play.
        */
        bool human_turn;
        /*
            Returns the last board in the recorded sequence.
        */
        Board get_latest_board ();
        /*
            Checks if the human player has won.
        */
        bool human_wins ();
        /*
            Checks if the matchbox has won.
        */
        bool matchbox_wins ();
        /*
            Checks if the game came to a draw.
            Technically, it checks draws and eventual victories, but this behaviour is OK.
        */
        bool is_draw ();
        /*
            Checks if the game is over.
        */
        bool is_over ();
        /*
            Switches the turns between the human and matchbox players.
        */
        void change_turns ();
        /*
            Decides the matchbox's move and adds a corresponding board to sequence.
        */
        void matchbox_play ();
        /*
            Takes the player's choice and adds a corresponding board to the sequence.
        */
        void human_play ();
        /*
            Figures out whose turn it is and makes them play.
        */
        void play ();
        /*
            Adds amount to all the weights of the moves played by matchbox.
        */
        void alter_sequence (int);
        /*
            Only execute this when game.is_over.
            Changes the weights in the played board based on the outcome of the game.
        */
        void adjust_weights ();

    public:
        /*
                            THE CONSTRUCTOR
            Takes no arguments, and randomly decides who plays first.
        */
        Game ();
        /*
            Overloaded version of the constructor, allows control over who plays first.
        */
        Game (bool);
        /*
            Keeps the game going until we have a winner.
        */
        void start_game ();
};

#endif // GAME_H