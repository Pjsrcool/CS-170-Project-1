#include "header.h"

// int main(int argc, char** argv) {
int main () {
    vector<vector<int>> puzzle;
    puzzle.push_back({-1,-1,-1,0,-1,0,-1, 0,-1, -1});
    puzzle.push_back({0,2,3,4,5,6,7,8,9,1});
    Node InitialState;
    InitialState.setState(puzzle);
    // Node* init = new Node(temp, nullptr);
    // init->print();

    Node answer = UniformCostSearch(InitialState);
    answer.print();

    std::cout << "hello world\n\n";
    return 0;
}