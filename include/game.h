#ifndef GAME_H
#define GAME_H

#include "board.h"

/*
    Represents the state of the game board.
    I borrow the term used in filmmaking.
*/
struct Scene {
    /* A board object */
    Board board;

    /* The index of the move in board.configuration */
    int move;

    /* Specifies the player, uniquely determined by their mark. */
    char mark;
};

/*  
    We will always consider that matchBox plays with the X mark.
*/
const char human_mark = O;
const char matchbox_mark = X;

const int VICTORY_NUDGE = 2;
const int DEFEAT_NUDGE = -1;
const int DRAW_NUDGE = 1;

bool is_winconfig(const string, const char);

Scene next_scene(const string, const int);   

class Game {
    private:
        /*
            This serves as a record of the entire game.
            Again, think of the game as a film.
        */
        vector<Scene> sequence;

        /*  
            This boolean tracks turns.
            It is true when it's the human's turn to play.
        */
        bool human_turn;

        Board get_latest_board ();
        bool human_wins ();
        bool matchbox_wins ();
        bool is_draw ();
        bool is_over ();
        void change_turns ();
        void matchbox_play ();
        void human_play ();
        void play ();
        void alter_sequence (int);
        void adjust_weights ();

    public:
        /*
                            THE CONSTRUCTOR
            Takes no arguments, and randomly decides who plays first.
        */
        Game ();
        Game (bool);
        void start_game ();
        void test ();
};

#endif // GAME_H