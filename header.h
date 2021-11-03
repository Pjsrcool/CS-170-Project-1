#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <string>
#include <unordered_set>

using std::vector;
using std::priority_queue;
using std::unordered_set;
using std::string;
using std::cout;
using std::cin;
using std::endl;

// we use an enum to decide which type of search to perform
enum SearchType {
    UniformCost,
    A_Star_MisplacedTile,
    A_Star_Manhattan,
};

// how we will represent the node
struct Node {
    // config of parent node, prevents searching backwards
    string parent; 

    // recesses in the trench
    // "-" --> blocked
    // "0" --> space
    string recess;  
    
    // men in the main portion of the trench
    string state;   

    // current depth of the node
    long depth; 
    
    // depth + heuristic
    long cost;

    // sets the parent configuration
    void setParent(string p) {parent = p;}

    // sets the recess and state configuration
    void setState(string r, string s) {recess = r; state = s;}

    // sets the depth of the node
    void setDepth(long d) {depth = d;}

    // sets the depth of the node
    void setCost(long c) {cost = c;}

    // prints the state of the node and its current depth
    void print() {
        cout << recess << endl;
        cout << state << " -->COST: " << cost << " -->Depth: " << depth << endl;
    }
};

// used to order the Node that enter the queue
class SmallerCost {
    public:
    bool operator() (Node l, Node r) {
        return l.cost > r.cost;
    }
};

// the generic search function
Node Search(Node initState, SearchType S, const string& goal);

#endif /*HEADER_H*/