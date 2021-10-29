#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

using std::vector;
using std::priority_queue;

struct Node {
    vector<vector<int>> state;  // current state of the board
                                // -1 --> block that no man can travel to
                                //  0 --> empty block that someone can travel to
                                //  1 --> sergeant who wishes to be in front
                                // any positive int --> block accupied by random man
    Node* parent;      // pointer to parent node

    long cost; // current weight of the node

    // vector<Node*> children;    // vector of pointers to children nodes
    
    void setState(vector<vector<int>> s) {state = s }; // initializes a node to a specific state
    
    // Node(vector<vector<int>> s, Node* p) : state(s), parent(p) {}; // Contructor that immediately assigns values to states, and assigns parent
    // void AddChild (Node* n) {children.push_back(n);}    // makes adding children look cleaner
    void print() {
        for (auto i : state) {
            for (auto j : i)
                std::cout << std::setw(3) << j << " ";
            std::cout << std::endl;
        }
    }

};

bool isGoalState(Node n) {
    for (int i = 0; i < 9; ++i)
        if (n.state[1][i] != i + 1)
            return false;
    return true;
}
Node UniformCostSearch(Node initState);
Node AStar_MisplacedTile(Node initState);
Node AStar_Manhattan(Node initState);

#endif /*HEADER_H*/