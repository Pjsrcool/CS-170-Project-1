#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <unordered_set>
#include <string>

using std::vector;
using std::priority_queue;
using std::unordered_set;
using std::string;
using std::cout;
using std::endl;

struct Node {
    string parent; // config of parent node
    string recess;  // recesses
                    // _ - blocked
                    // 0 - space
    string state;   // men in the trench

    long cost; // current weight of the nod
    
    void setState(string r, string s) {recess = r; state = s;}

    void setCost(long c) {cost = c;} // sets the cost of the node

    void print() {
        cout << recess << endl;
        cout << state << " " << cost << endl;
    }

};

Node UniformCostSearch(Node initState);
Node AStar_MisplacedTile(Node initState);
Node AStar_Manhattan(Node initState);

#endif /*HEADER_H*/