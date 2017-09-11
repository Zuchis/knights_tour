#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <cstdlib>

using std::vector;
using std::pair;
using std::make_pair;

typedef std::pair<int,int> Position;

Position operator+(const Position &p1, const Position &p2) {
    return {p1.first + p2.first, p1.second + p2.second};
}

class Node {
    public:
        vector<std::pair<Position,int>> neighbors;
        int size;
        bool visited;

        Node (Position p, int chess_size) {
            std::array<Position,8> movements = {
                Position(-2,1),
                Position(-1,2),
                Position(1,2),
                Position(2,1),
                Position(2,-1),
                Position(1,-2),
                Position(-1,-2),
                Position(-2,-1)
            };
            int order = 1;
            for (auto movement : movements) {
                auto current_position = p + movement;
                if (current_position.first < chess_size && current_position.second < chess_size) {
                    if (current_position.first > -1 && current_position.second > -1) {
                        neighbors.push_back(make_pair(current_position,order));
                    }
                }
                order++;
            }
            size = (int)neighbors.size();
            visited = false;
        }
};

int main(int argc, const char *argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << "<size of the square chess board>" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::map<Position,Node> board;

    int i, j;
    int size = atoi(argv[1]);
    int number_of_moves = (size * size) + 1;
    int neighborhood_size = 8;
    int counter = 1;

    vector<vector<int>> tour;

    for (i = 0; i < size; i++) {
        vector<int> tour_line;
        for (j = 0; j < size; j++) {
            tour_line.push_back(-1);
            Position p = Position(i,j);
            board.insert(std::make_pair(p,Node(p,size)));
        }
        tour.push_back(tour_line);
    }


    int remainder = size % 8;
    vector<vector<int>> tiebreaking_rules;
    vector<Position> swap_positions;

    switch (remainder) {
        case 0:
            tiebreaking_rules.push_back({3,4,2,6,1,5,7,8});
            tiebreaking_rules.push_back({8,7,6,4,2,1,3,5});
            tiebreaking_rules.push_back({5,1,8,6,7,3,4,2});
            tiebreaking_rules.push_back({5,1,3,4,2,6,7,8});
            tiebreaking_rules.push_back({2,1,4,3,5,6,7,8});
            swap_positions.push_back(Position(size - 1, size - 2));
            swap_positions.push_back(Position(2,2));
            swap_positions.push_back(Position(size - 8, 1));
            swap_positions.push_back(Position(7, size - 3));
            swap_positions.push_back(Position(-1,-1));
            break;
        case 1:
            tiebreaking_rules.push_back({3,4,2,6,1,5,7,8});
            tiebreaking_rules.push_back({8,7,6,4,2,1,3,5});
            tiebreaking_rules.push_back({5,1,3,2,4,6,7,8});
            tiebreaking_rules.push_back({3,2,4,8,1,7,6,5});
            swap_positions.push_back(Position(size - 1, size - 2));
            swap_positions.push_back(Position(2,2));
            swap_positions.push_back(Position(size - 6, ((size - 1) / 2) + 5));
            swap_positions.push_back(Position(-1,-1));
            break;
        case 2:
            tiebreaking_rules.push_back({3,4,2,6,1,5,7,8});
            tiebreaking_rules.push_back({8,7,6,4,2,1,3,5});
            tiebreaking_rules.push_back({5,4,1,3,2,6,7,8});
            tiebreaking_rules.push_back({5,2,4,3,1,6,7,8});
            tiebreaking_rules.push_back({8,5,6,4,7,1,2,3});
            tiebreaking_rules.push_back({1,5,7,4,6,8,2,3});
            swap_positions.push_back(Position(size - 1, size - 2));
            swap_positions.push_back(Position(size - 6, size));
            swap_positions.push_back(Position(size - 15, 4));
            swap_positions.push_back(Position(10, size - 2));
            swap_positions.push_back(Position(5, size / 2 - 3));
            swap_positions.push_back(Position(-1,-1));
            break;
        case 3:
            tiebreaking_rules.push_back({3,4,6,2,5,7,1,8});
            tiebreaking_rules.push_back({4,2,6,8,1,3,5,7});
            tiebreaking_rules.push_back({8,6,5,1,2,3,4,7});
            tiebreaking_rules.push_back({5,1,8,6,7,3,4,2});
            tiebreaking_rules.push_back({6,1,8,2,5,4,3,7});
            tiebreaking_rules.push_back({7,1,6,4,2,5,3,8});
            swap_positions.push_back(Position(size - 1, size - 2));
            swap_positions.push_back(Position(size - 6, size));
            swap_positions.push_back(Position(2, 5));
            swap_positions.push_back(Position(size - 10, 3));
            swap_positions.push_back(Position(((size - 1) / 2) + 1, size - 2));
            swap_positions.push_back(Position(-1, -1));
            break;
        case 4:
            tiebreaking_rules.push_back({3,4,2,6,1,5,7,8});
            tiebreaking_rules.push_back({8,7,6,4,2,1,3,5});
            tiebreaking_rules.push_back({5,1,8,6,7,3,4,2});
            tiebreaking_rules.push_back({5,1,3,4,2,6,7,8});
            tiebreaking_rules.push_back({8,6,7,5,3,4,2,1});
            tiebreaking_rules.push_back({7,8,5,6,3,4,2,1});
            swap_positions.push_back(Position(size - 1, size - 2));
            swap_positions.push_back(Position(2,2));
            swap_positions.push_back(Position(size - 8, 1));
            swap_positions.push_back(Position(10, size - 5));
            swap_positions.push_back(Position(13, size / 2 + 1));
            swap_positions.push_back(Position(-1,-1));
            break;
        case 5:
            tiebreaking_rules.push_back({3,4,2,6,1,5,7,8});
            tiebreaking_rules.push_back({8,7,6,4,2,1,3,5});
            tiebreaking_rules.push_back({5,1,3,2,4,6,7,8});
            tiebreaking_rules.push_back({1,5,2,3,4,6,7,8});
            swap_positions.push_back(Position(size - 1, size - 2));
            swap_positions.push_back(Position(2,2));
            swap_positions.push_back(size % 16 == 5 ? Position(size - 2, (size - 1) / 2 - 2) : Position(size - 2, (size - 1) / 2 - 6));
            swap_positions.push_back(Position(-1,-1));
            break;
        case 6:
            tiebreaking_rules.push_back({3,4,2,6,1,5,7,8});
            tiebreaking_rules.push_back({8,7,6,4,2,1,3,5});
            tiebreaking_rules.push_back({5,4,1,3,2,6,7,8});
            tiebreaking_rules.push_back({5,2,4,3,1,6,7,8});
            tiebreaking_rules.push_back({8,5,6,4,7,1,2,3});
            tiebreaking_rules.push_back({1,2,4,5,3,6,7,8});
            swap_positions.push_back(Position(6,1));
            swap_positions.push_back(Position(3,1));
            swap_positions.push_back(Position(size - 10, 1));
            swap_positions.push_back(Position(10, size - 2));
            swap_positions.push_back(Position(3, size / 2 + 4));
            swap_positions.push_back(Position(-1,-1));
            break;
        case 7:
            tiebreaking_rules.push_back({3,4,6,2,5,});
            tiebreaking_rules.push_back({8,7,6,4,2,1,3,5});
            tiebreaking_rules.push_back({5,4,1,3,2,6,7,8});
            tiebreaking_rules.push_back({5,2,4,3,1,6,7,8});
            tiebreaking_rules.push_back({8,5,6,4,7,1,2,3});
            tiebreaking_rules.push_back({1,2,4,5,3,6,7,8});
            swap_positions.push_back(Position(6,1));
            swap_positions.push_back(Position(3,1));
            swap_positions.push_back(Position(size - 10, 1));
            swap_positions.push_back(Position(10, size - 2));
            swap_positions.push_back(Position(3, size / 2 + 4));
            swap_positions.push_back(Position(-1,-1));
            break;
        default:
            std::cout << "This will never be printed lol " << std::endl;
    }

    Position current(0,0);

    tour[current.first][current.second] = counter;
    counter++;
    int it = 0;
    auto sit = swap_positions.begin();

    while (counter < number_of_moves) {
        Node* current_node = &board.at(current);
        Position next_position;
        int chosen_move = 0;
        int smallest_size = neighborhood_size + 1;

        current_node->visited = true; // Set the current to visited

        if (current == *sit && sit != swap_positions.end()) { // Check the current tiebrake
            sit++;
            it++;
        }

        for (auto neighbor : current_node->neighbors) { // Find the smallest
            Node* aux = &board.at(neighbor.first);
            if (aux->visited == true)
                continue;

            aux->size--;
            if (aux->size < smallest_size) { // Found one smaller
                smallest_size = aux->size;
                next_position = neighbor.first;
                chosen_move   = neighbor.second;
            } else if (aux->size == smallest_size) { // Tie
                auto p1 = std::find(tiebreaking_rules[it].begin(),tiebreaking_rules[it].end(),chosen_move);
                auto p2 = std::find(tiebreaking_rules[it].begin(),tiebreaking_rules[it].end(),neighbor.second);
                if (p2 < p1) {
                    smallest_size = aux->size;
                    next_position = neighbor.first;
                    chosen_move   = neighbor.second;
                }
            }
        }
        current = next_position;
        tour[current.first][current.second] = counter;
        counter++;
    }

    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            std::cout << tour[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    
    return 0;
}
