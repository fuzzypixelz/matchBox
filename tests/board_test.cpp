#include "../src/generator/board.h"

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main() {
    string conf = "XO--O----";

    Board board (conf);

    board.print_board();

    cout << board.configuration << endl;

    for (auto n : board.weights) {
        cout << n << " ";
    };
    cout << endl;

    for (auto n : board.empty_slots) {
        cout << n << " ";
    };
    cout << endl;
   
    /*
    // uncomment after first run
    vector<int> new_weights = {5, 5, 5, 5, 5, 5};
    board.weights = new_weights;
    board.update_file();  
    */
    
};