#include "../include/game.h"

/*
    Checks command arguments and starts the game accordinly.
*/
int main(int argc, char** argv) {

    Game game;

    if (argc > 1) {
        if (argv[1] == string("human")) {
            game = Game(true);
        }
        else if (argv[1] == string("matchbox")) {
            game = Game(false);
        };
    };

    game.start_game();

    return 0;
}