#include "board.h"

int random_number(int max_number)
{
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> distrib(0, max_number - 1);
 
    return distrib(gen);
}

vector<int> string_to_vector (string input) {
    /* 
        converts a string to a vector of integers
        meant to convert the get back weights from the file
    */

    vector<int> result;

    for (int i = 0; i < input.size(); i++) {
        int entry = input[i] - '0';
        result.push_back(entry);
    };

    return result;
};

Board::Board (string conf) {
    /* Constructor definition */

    /* Always done, even if file exists */
    configuration = conf;
    file_path = "data/board_files/" + configuration;
    set_empty_slots();

    /* Would be file */
    string path = "data/board_files/" + conf;
    fstream file;
    file.open(path);

    /* Does the file exist already? */
    string line;
    if (file.is_open()) {

        /* This pretty hacky, will certainly cause problems */
        string line, line_;
        while (getline(file, line_)) {
            if (line_ != "\n") {
                line = line_;
            }
        };
        weights = string_to_vector(line);
        file.close();
    } else {
        ofstream new_file;
        new_file.open(path);
        set_random_weights();
        update_file();
        new_file.close();
    }
}

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

void Board::set_empty_slots () {
    /*         
        locates the empty slots on the board
        the return vector contains their indices, in increasing order
    */

    for (int i = 0; i < SLOTS; i++) {
        if (configuration[i] == NONE) {
            empty_slots.push_back(i);
        };
    };
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