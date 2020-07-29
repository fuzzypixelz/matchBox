#include "../include/game.h"

using std::cin;
using std::cout;
using std::max;
using std::min;

bool  is_winconfig (const string conf, const char mark) {
    /*  
        The argument mark is either 'X' or 'O'.
        The conf string records the marks on the board left to right,
            and top to bottom.
    */
    const string winconfig = string(3, mark);

    /* Trick to combine multiple char's into a string */
    const string s = string();

    const vector<string> substrings_tocheck = {
        /* 
            0 1 2
            3 4 5   Ugly code.
            6 7 8
        */
        s + conf[0] + conf[1] + conf[2],
        s + conf[3] + conf[4] + conf[5],
        s + conf[6] + conf[7] + conf[8],
        s + conf[0] + conf[3] + conf[6],
        s + conf[1] + conf[4] + conf[7],
        s + conf[2] + conf[5] + conf[8],
        s + conf[0] + conf[4] + conf[8],
        s + conf[2] + conf[4] + conf[6]
   };

    for (const auto &substring: substrings_tocheck) {
        if (substring == winconfig) {
            return true;
        }
    };

    /* You failed the test! */
    return false;
};

Scene get_next_scene (const string current_conf, const int next_move, const char mark) {
    /* 
        Constructs the next Scene using the next move and the next board, 
        for the player using mark. 
    */

    /* The next configuration. */
    const string next_conf = current_conf.substr(0, next_move)
                             + mark                
                             + current_conf.substr(next_move + 1, 9);

    /* The next board. */
    const Board next_board = Board(next_conf);

    /* The next scene. */
    Scene next_scene;
    next_scene.board = next_board;
    next_scene.move = next_move;
    next_scene.mark = mark;

    return next_scene;
};

Board Game::get_latest_board () {
    /*
        Returns the last board in the recorded sequence.
    */

    return sequence.back().board;
};

Game::Game () {
    /*
        Sets human_turn randomly.
    */

    const int r = random_number(2); // random number between 0 and 1
    human_turn = (r == 0);

    /* The sequence starts with an empty board. */
    Scene scene;
    sequence.push_back(scene);
};

Game::Game (bool human_starts) {
    /*
        This constructor decides who shall start, with input from the user.
    */

    human_turn = human_starts;

    /* The sequence starts with an empty board. */
    Scene scene;
    sequence.push_back(scene);
};

bool Game::human_wins () {
    /* 
        Checks if the human player has won. 
    */

    return is_winconfig(get_latest_board().configuration, human_mark);
};

bool Game::matchbox_wins () {
    /* 
        Checks if the matchbox has won. 
    */

    return is_winconfig(get_latest_board().configuration, matchbox_mark);
};

bool Game::is_draw () {
    /*
        Checks if the game came to a draw.
        Technically, it checks draws and eventual victories, but this behaviour is OK.
    */

    /* Get current configuration. */
    string current_conf = get_latest_board().configuration;

    /* Scans the board for empty slots. */
    for (auto c : current_conf) {
        if (c == NONE) {
            return false;
        };
    };
    return true;
}

bool Game::is_over () {
    /*
        Checks if the game is over.
    */

    bool human_won = human_wins();
    bool matchbox_won = matchbox_wins();
    bool was_draw = is_draw(); 

    if (human_won) {
        cout << "Congratulations! Human!" << endl;
    }
    else if (matchbox_won) {
        cout << "Congratulations matchBox!" << endl;
    }
    else if (was_draw) {
        cout << "It's a draw!" << endl;
    }

    return (human_won || matchbox_won || was_draw);
};

void Game::change_turns () {
    /* 
        Switches the turns between the human and matchbox players.
    */

    human_turn = !human_turn;
};

void Game::matchbox_play () {
    /*
        Decides the matchbox's move and adds a corresponding board to sequence.
    */

    /* Collects all information about the current board. */
    Board current_board = get_latest_board();
    const string current_conf = current_board.configuration;
 
    const int next_move = current_board.next_move();

    /* Appends the next scene to the sequence. */
    sequence.push_back(get_next_scene(current_conf, next_move, matchbox_mark));

    /* Print the resulting board. */
    cout << endl;
    cout << "Well played matchBox!" << endl;
    cout << endl;
    get_latest_board().print_board();
};

void Game::human_play () {
    /*
        Takes the player's choice and adds a corresponding board to the sequence.
    */

    /* Prompt the player for their move. */
    int next_move;
    cout << "You may chose a move on the board." << endl;
    cin >> next_move;

    /* The current configuration. */
    const Board board = get_latest_board();
    const string current_conf = board.configuration;
    
    /* Append the next scene to the sequence. */
    sequence.push_back(get_next_scene(current_conf, next_move, human_mark));

    /* Print the resulting board. */
    cout << endl;
    cout << "You're fine, for a human." << endl;
    cout << endl;
    get_latest_board().print_board();
};

void Game::play () {
    /* 
        Figures out whose turn it is and makes them play.
    */

    /* Simple enough. */
    if (human_turn) {
        human_play();
    } else {
        matchbox_play();
    };

    /* Swtich turns! */
    change_turns();
};

void Game::alter_sequence(int amount) {
    /*
        Adds amount to all the weights of the moves played by matchbox.
    */

    for (auto &scene : sequence) {
        /* Unmovable block of bad data structure. */
        Board &board = scene.board;
        vector<int> &weights = board.weights;
        vector<int> empty_slots = board.empty_slots;
        int move = board.next_move();

        for (int i = 0; i < weights.size(); i++) {
            /* Don't make a copy of w! */
            /* Only change the weight of moves by matchBox! */
            if ((empty_slots[i] == move) && (scene.mark == human_mark)) {
                /* This one will probably blow up. */
                int &weight = weights[i];
                int new_weight = weight + amount;

                if (new_weight >= 0) {
                    weight = min(MAX_WEIGHT-1, new_weight);
                } else {
                    weight = 0;
                }
            }
        };
        scene.board.update_file();
    };
};

void Game::adjust_weights () {
    /*
        Only execute this when game.is_over.
        It changes the weights in the played board based on the outcome of the game.
    */

    bool human_won = human_wins();
    bool matchbox_won = matchbox_wins();

    /* These are all the cases. */
    if ((!human_won) && (!matchbox_won)) {
        alter_sequence(DRAW_NUDGE);
    } 
    else if (human_won) {
        alter_sequence(DEFEAT_NUDGE);
    }
    else if (matchbox_won) {
        alter_sequence(VICTORY_NUDGE);
    };
};

void Game::start_game () {
    /* 
        Keeps the game going until we have a winner. 
    */

    /* Little introduction. */
    cout << "Welcome to TIC-TAC-TOE ! (It's not Noughts + Crosses silly!)" << endl;
    cout << "Your opponent shall be a sentient collection of matchboxes." << endl;
    get_latest_board().print_board();

    /* Gaming loop. */
    while (!is_over()) {
        play();
    };

    /* Most important part of the program. */
    adjust_weights();
};
