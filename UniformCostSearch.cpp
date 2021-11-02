#include "header.h"

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
            temp.setParent(node.recess + node.state);
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
            temp.setParent(node.recess + node.state);
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
            temp.setParent(node.recess + node.state);
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
        
        // move up
        if (node.recess[openState[i]] != '-' && node.recess[openState[i]] != '0' ) {
            Node temp;
            temp.recess = node.recess;
            temp.state = node.state;
            temp.cost = node.cost + 1;
            temp.recess[openState[i]] = '0';
            temp.state[openState[i]] = node.recess[openState[i]];
            temp.setParent(node.recess + node.state);
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
    }
}

Node UniformCostSearch(Node initState) {
    priority_queue<Node, vector<Node>, SmallerCost> nodes;
    Node answer;

    // initialize the queue
    nodes.push(initState);

    // initialize answer to all blanks
    // we return all blanks if no goal
    // state is found
    answer.setState(" ", " ");
    answer.setCost(-1);

    while (!nodes.empty()) {
        // we grab and print the top node
        Node temp = nodes.top();
        temp.print();
        
        // check if it is the goal state
        // if it is, then return it
        if (isGoalState(nodes.top())) {
            answer.setState(nodes.top().recess, nodes.top().state);
            answer.setCost(nodes.top().cost);
            return answer;
        }
        // node was not a goal state. so we
        // expand node, then remove it
        ExpandNode(nodes.top(), nodes);
        nodes.pop();
    }

    return answer;
}