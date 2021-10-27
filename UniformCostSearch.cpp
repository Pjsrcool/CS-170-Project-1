#include "header.h"

class SmallerCost {
    public:
    bool operator() (Node l, Node r) {
        return l.cost <= r.cost;
    }
};

Node UniformCostSearch(Node initState) {
    priority_queue<Node, vector<Node>, SmallerCost> nodes;

    nodes.push(initState);
    while (!nodes.empty()) {

    }
}