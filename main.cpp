#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using std::vector;

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << "<size of the square chess board>" << std::endl;
        exit(EXIT_FAILURE);
    }

    int i, j;
    int size = atoi(argv[1]);

    vector<vector<bool>> board;
    vector<vector<int>> tour;

    for (i = 0; i < size; i++) {
        vector<bool> board_line;
        vector<int> tour_line;
        for (j = 0; j < size; j++) {
            board_line.push_back(false);
            tour_line.push_back(-1);
        }
        board.push_back(board_line);
        tour.push_back(tour_line);
    }
    
    return 0;
}
