#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>
#include <algorithm>

/* Never do using namespace std ! */
using std::string;
using std::vector;
using std::fstream;
using std::ofstream;
using std::ios;
using std::ios_base;
using std::endl;
using std::max_element;

/*
    Represents a cross. 
*/
const char X    = 'X';
/*
    Represents a nought. 
*/
const char O    = 'O';
/*
    Represents the absence of a mark. 
*/
const char NONE = '-';
/* 
    Number of slots on the board. 
*/
const int SLOTS = 9;
/* 
    Maximum weight possible, strictly. 
*/
const int MAX_WEIGHT = 10;
/*
    A model of a TIC-TAC-TOE board which includes weights for each possible move on it.
    The weights are numbers that determine the next move to be taken by matchBox.
*/
class Board {
    private:
        /*
            The path to the file associated with the Board.
        */
        string file_path;
        /*  
            Locates and stores the empty slots on the board,
            the return vector contains their indices, in increasing order.
        */
        void set_empty_slots ();
        /*  
            Generates the weights vector using random values.
        */
        void set_random_weights ();
    public:
        /*
                                    THE CONSTRUCTOR    
            Initializes the configuration, file_path, empty_slots and generates
            a file containing weights if there isn't any, otherwise it loads weights from it.
        */
        Board (string);
        /*
            Default constructor for Board, uses an empty configuration.
        */
        Board () : Board("---------") {};
        /*
            Temporary visual representation of the board.
        */
        void print_board ();
        /*  
            Update the assigned file with new weights.
        */
        void update_file ();
        /*
            Calculates the next move to be taken.
        */
        int next_move ();
        /*
            Records the board state from top to bottom and left to right
            it has 9 chars each of which is either an X, O, or NONE.
        */
        string configuration;
        /*             
            Records the weights of each possible move on the board, 
            in the same order as empty_slots.
        */
        vector<int> weights;
        /* 
            Records the empty slots on the board, in the same order as weights. 
        */
        vector<int> empty_slots;
};
/* 
    Returns a random integer strictly less than max_number
*/
int random_number(int);

#endif // BOARD_H