#ifndef HEADER_H_
#define HEADER_H_

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>
#include <chrono>
#include <ctime>

using std::vector;
using std::queue;
using std::priority_queue;
using std::unordered_set;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::to_string;
using std::chrono::time_point;
using std::chrono::system_clock;
using std::chrono::duration;

// we use an enum to decide which type of search to perform
enum SearchType {
    UniformCost,
    A_Star_MisplacedTile,
    A_Star_Manhattan,
};

// how we will represent the node
struct Node {
    // // recesses in the trench
    // // "-" --> blocked
    // // "0" --> space
    // string recess;  
    
    // // men in the main portion of the trench
    // string state;

    vector<string> state; 

    // current depth of the node
    long depth; 
    
    // prev cost + heuristic
    long cost;

    // sets the recess and state configuration
    void setState(string r, string s) { state.clear(); state.push_back(r); state.push_back(s);}

    // sets the depth of the node
    void setDepth(long d) {depth = d;}

    // sets the depth of the node
    void setCost(long c) {cost = c;}

    // prints the state of the node and its current depth
    void print() {
        cout << state[0] << endl;
        cout << state[1] << " -->COST: " << cost << " -->Depth: " << depth << endl;
    }
};

// used to order the Node that enter the queue, 
// lowest cost on top of queue
class SmallerCost {
    public:
    bool operator() (Node l, Node r) {
        return l.cost > r.cost;
    }
};

// the generic search function
Node Search(Node initState, SearchType S, const Node& goalState);

#endif /*HEADER_H*/