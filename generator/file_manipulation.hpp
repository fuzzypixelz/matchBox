#ifndef FILE_MANIPULATION_HPP
#define FILE_MANIPULATION_HPP

#include <fstream>

using std::fstream;
using std::ios_base;

void goto_last_line(fstream &file) {
    /* 
        This assumes that the file 
        has only one newline!
        LOOK INTO WHY file SHOULD BE PASSED BY REFERENCE! 
    */

    file.seekg(-2, ios_base::end);
}

#endif // FILE_MANIPULATION_HPP