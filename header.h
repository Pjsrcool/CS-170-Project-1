#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>

using std::vector;
using std::queue;

struct Node {
    vector<vector<int>> state;  // current state of the board
                                // -1 --> block that no man can travel to
                                //  0 --> empty block that someone can travel to
                                //  1 --> sergeant who wishes to be in front
                                // any positive int --> block accupied by random man
    Node* parent;      // pointer to parent node
    vector<Node*> children;    // vector of pointers to children nodes

    Node(vector<vector<int>> s, Node* p) : state(s), parent(p) {}; // Contructor that immediately assigns values to states, and assigns parent
    void AddChild (Node* n) {children.push_back(n);}    // makes adding children look cleaner
    void print() {
        for (auto i : state) {
            for (auto j : i)
                std::cout << std::setw(3) << j << " ";
            std::cout << std::endl;
        }
    }

};

Node UniformCostSearch();
Node AStar_MisplacedTile();
Node AStar_Manhattan();

#endif /*HEADER_H*/