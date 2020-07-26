#ifndef STRING_VECTOR_HPP
#define STRING_VECTOR_HPP

#include <vector>
#include <string>

using std::vector;
using std::string;

vector<int> string_to_vector (string input) {
    /* 
        converts a string to a vector of integers
        meant to convert the get back weights from the file
    */

    vector<int> result;

    for (int i = 0; i < input.size(); i++) {
        result.push_back(input[i]);
    };

    return result;
};

#endif // STRING_VECTOR_HPP