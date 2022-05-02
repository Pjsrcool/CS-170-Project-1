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
#include <threads.h>

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
    MisplacedTiles,
    Manhattan_On_Sergeant,
    Count_Obstructing_Men,
    Check_Left_Man,
};

// this is how we will represent the node
struct Node {
    // this is the current configuration of the board
    // in this program, we will limit the board to 2 row
    // state[0] will be the row with recesses
    // state[1] will be either empty space, or men
    // '-' --> inaccessable
    // '0' --> empty space
    // any int --> man
    vector<string> state; 

    // current depth of the node
    int depth; 
    
    // prev cost + heuristic
    int cost;

    // sets the configuration of the recess row and state row
    void setState(string r, string s) { 
        state.clear();
        state.push_back(r);
        state.push_back(s);
    }

    // sets the depth of the node
    void setDepth(long d) {
        depth = d;
    }

    // sets the depth of the node
    void setCost(long c) {
        cost = c;
    }

    // prints the state of the node and its current depth
    void print() {
        cout << state[0] << endl;
        cout << state[1] << " -->COST: " << cost << " -->Depth: " << depth << endl;
    }
};

// Comparison object used to order 
// Nodes that enter the queue, 
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