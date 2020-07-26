#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <stdlib.h>
#include <time.h>

int random_number(int max_number) {

    srand(time(NULL));

    return rand() % max_number + 1;
};

#endif // RANDOM_HPP