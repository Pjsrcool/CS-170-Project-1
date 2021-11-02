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

// we use an enum to decide which type of search to perform
enum SearchType {
    UniformCost,
    A_Star_MisplacedTile,
    A_Star_Manhattan,
};

// how we will represent the node
struct Node {
    string parent; // config of parent node
    string recess;  // recesses
                    // _ - blocked
                    // 0 - space
    string state;   // men in the trench

    long cost; // current weight of the nod
    
    // sets the parent 
    void setParent(string p) {parent = p;}

    // sets current recess and state
    void setState(string r, string s) {recess = r; state = s;}

    void setCost(long c) {cost = c;} // sets the cost of the node

    void print() {
        cout << recess << endl;
        cout << state << " -->COST: " << cost << endl;
    }
};

// used to order the Node that enter the queue
class SmallerCost {
    public:
    bool operator() (Node l, Node r) {
        return l.cost >= r.cost;
    }
};

Node Search(Node initState, SearchType S);

#endif /*HEADER_H*/