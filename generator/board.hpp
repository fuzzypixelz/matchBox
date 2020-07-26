#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "random.hpp"
#include "string_vector.hpp"
#include "file_manipulation.hpp"

// using statements
using std::string;
using std::vector;
using std::fstream;
using std::endl;

namespace generator {

    /* Class definition */
    class Board {
        /* 
        This class is a model for a TIC-TAC-TOE board.
        This class also provides the weights assigned to each playable move.
        */

        private:
            /* all possible moves */
            const char X    = 'X';
            const char O    = 'O';
            const char NONE = ' ';

            /* this needs organizing */
            const int SLOTS = 9;
            const string file_path = "storage/" + configuration;
            const int MAX_WEIGHT = 20;

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
            Board (string configuration_);

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
                --Every programmer ever.
            */
            vector<int> empty_slots;

            void update_file ();

            void print_board ();
    };

    Board::Board (string configuration_) {
        /* Constructor definition */

        /* would be file */
        string path = "storage/" + configuration_;
        fstream file;
        file.open(path);

        if (file.is_open()) {
            goto_last_line(file);
            string line;
            getline(file, line);

            /* finally set the weights */
            weights = string_to_vector(line);
        } else {
            configuration = configuration_;
            set_random_weights();
        }

        set_empty_slots();

    };

    void Board::set_random_weights () {
        /* 
            this will set up the random weights vector
            which is a class constant, and represents the 
        */

        int length = empty_slots.size();

        for (int i = 0; i < length; i++) {
            weights.push_back(random_number(MAX_WEIGHT));
        };
    };

    void Board::set_empty_slots () {
        /*         
            locates the empty slots on the board
            the return vector contains their indices, in increasing order
        */

        for (int i = 0; i < SLOTS; i++) {
            if (configuration[i] == ' ') {
                empty_slots.push_back(i);
            };
        };
    };

    void Board::update_file () {
        /* 
            update the assigned file
            with the new wights
            TRICKY!
        */

        using std::ios;

        fstream file;
        file.open(file_path, ios::app);
        
        for (auto n : weights) {
            file << n;
        };
        file << endl;
    };

    void Board::print_board () {
        /* 
            temporary visual representation of the board
        */

        using std::cout;

        for (int i = 0; i < SLOTS; i++) {
            cout << configuration[i] << " ";
            if (i == 2 || i == 5 || i == 8) {
                cout << endl;
            };
        };
    };
}

#endif // BOARD_HPP