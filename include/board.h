#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <random>

// using statements
using std::string;
using std::vector;
using std::fstream;
using std::ofstream;
using std::ios;
using std::ios_base;
using std::endl;

class Board {
    private:
        /* all possible moves */
        const char X    = 'X';
        const char O    = 'O';
        const char NONE = '-';

        /* this needs organizing */
        const int SLOTS = 9;
        const int MAX_WEIGHT = 10;
        string file_path;

        void set_empty_slots ();
        void set_random_weights ();
    public:
        /*
                            THE CONSTRUCTOR    
        1. if there is a corresponding file, only load the weights from it.
        2. otherwise, create an associated file and set arbitrary weights

        No board can be initialized without:
            configuration, weights, empty_slots
        */
        Board (string);


        void print_board ();

        void update_file ();

        /*
        records the board state from top to bottom and left to right
        it has 9 chars each of which is either an 'X', 'O', or ' '.
        */
        string configuration;

        /*             
        weights of each move on the board
        its length is the same is the size of empty_slots
        and follows its order
        */
        vector<int> weights;

        /* 
        pretty self-explanatory 
        */
        vector<int> empty_slots;
};

#endif // BOARD_H