#include "../include/game.h"

int main(int argc, char** argv) {
    /* Neat and tidy. */

    Game game;

    if (argv[0] == "human") {
        game = Game(true);
    }
    else if (argv[0] == "matchbox") {
        game = Game(false);
    };

    game.start_game();

    return 0;
}