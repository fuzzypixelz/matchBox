#include <string>
#include <vector>
using std::string;
using std::vector;

class Board {
    public:
        Board () {
            // set configuration and weights
        }
        string configuration;
        vector<int> weights;
        void save_to_file ();
};