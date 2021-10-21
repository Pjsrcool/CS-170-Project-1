#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <queue>
#include <vector>

using std::vector;
using std::queue;

struct Node {
    vector<vector<int>> state;  // current state of the board
    Node* parent;               // pointer to parent node
    vector<Node*>   children;    // list of pointers to children nodes

    Node(vector<vector<int>> s, Node* p) : state(s), parent(p) {}; // Contructor that immediately assigns values to states, and assigns parent
    void AddChild (Node* n) {children.push_back(n);}    // makes adding children look cleaner
};

Node UniformCostSearch();
Node AStar_MisplacedTile();
Node AStar_Manhattan();

#endif /*HEADER_H*/