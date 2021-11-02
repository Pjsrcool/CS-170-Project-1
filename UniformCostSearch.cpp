#include "header.h"

// unordered_set<string> history;

class SmallerCost {
    public:
    bool operator() (Node l, Node r) {
        return l.cost >= r.cost;
    }
};

bool isGoalState(Node n) {
    if (n.state == "1230000")
        return true;
    return false;
}

void ExpandNode(const Node node, priority_queue<Node, vector<Node>, SmallerCost> & children) {
    vector<int> openRecess;
    vector<int> openState;
    
    // find the open spaces in recesses and the main path
    for (int i = 0; i < node.recess.length(); ++i) {
        if (node.recess[i] == '0')
            openRecess.push_back(i);
    }
    for (int i = 0; i < node.state.length(); ++i) {
        if (node.state[i] == '0')
            openState.push_back(i);
    }
    
    // create new nodes
    // spaces in recesses can only move down, so we only check 
    // for moving the space down
    for (int i = 0; i < openRecess.size(); ++i) {
        if (node.state[openRecess[i]] != '0') {
            Node temp;
            temp.recess = node.recess;
            temp.state = node.state;
            temp.cost = node.cost + 1;
            temp.recess[openRecess[i]] = node.state[openRecess[i]];
            temp.state[openRecess[i]] = '0';
            temp.parent = node.recess + node.state;
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
    }
    
    // spaces in row can move left, right and up
    for (int i = 0; i < openState.size(); ++i) {
        // move left
        if (openState[i] > 0 && node.state[openState[i] - 1] != '0') {
            Node temp;
            temp.recess = node.recess;
            temp.state = node.state;
            temp.cost = node.cost + 1;
            temp.state[openState[i]] = node.state[openState[i] - 1];
            temp.state[openState[i] - 1] = '0';
            temp.parent = node.recess + node.state;
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
        
        // move right
        if (openState[i] < node.state.length() - 1 && node.state[openState[i] + 1] != '0') {
            Node temp;
            temp.recess = node.recess;
            temp.state = node.state;
            temp.cost = node.cost + 1;
            temp.state[openState[i]] = node.state[openState[i] + 1];
            temp.state[openState[i] + 1] = '0';
            temp.parent = node.recess + node.state;
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
        
        // move up
        if (node.recess[openState[i]] != '_' && node.recess[openState[i]] != '0' ) {
            Node temp;
            temp.recess = node.recess;
            temp.state = node.state;
            temp.cost = node.cost + 1;
            temp.recess[openState[i]] = '0';
            temp.state[openState[i]] = node.recess[openState[i]];
            temp.parent = node.recess + node.state;
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
    }
}

Node UniformCostSearch(Node initState) {
    priority_queue<Node, vector<Node>, SmallerCost> nodes;
    Node answer;

    nodes.push(initState);
    answer.setState(nodes.top().recess, nodes.top().state);
    answer.setCost(nodes.top().cost);
    // ExpandNode(nodes.top(), nodes);
    // // while (!nodes.empty())  {
    // for (int a = 0; a < 4; ++a) {
    //     Node temp = nodes.top();
    //     temp.print();
    //     cout << endl;

    //     ExpandNode(nodes.top(), nodes);
    //     nodes.pop();
    // }

    while (!nodes.empty()) {
        Node temp = nodes.top();
        temp.print();
        
        if (isGoalState(nodes.top())) {
            answer.setState(nodes.top().recess, nodes.top().state);
            answer.setCost(nodes.top().cost);
            return answer;
        }

        // expand node, then remove the old node
        ExpandNode(nodes.top(), nodes);
        nodes.pop();
    }

    return answer;
}