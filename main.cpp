#include <iostream>
#include <vector>
#include "generator/board.hpp"

using std::cout;
using std::endl;
using std::vector;
using generator::Board;

int main() {
    Board board ("X OXO    ");

    board.print_board();

    cout << board.configuration;

    for (auto n : board.weights) {
        cout << n << " ";
    };
    cout << endl;

    for (auto n : board.empty_slots) {
        cout << n << " ";
    };
    cout << endl;

    /*  TO UNCOMMENT AFTER FIRST RUN.   
    vector<int> new_weights = {5, 5, 5, 5, 5, 5};
    board.weights = new_weights;
    board.update_file(); 
    */
    
}