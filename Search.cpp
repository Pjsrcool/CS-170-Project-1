#include "header.h"

// check if the node is a goal state
bool isGoalState(Node n, const string & goal) {
    if (n.state.compare(goal) == 0)
        return true;
    return false;
}

long heuristic (SearchType S, const Node& node) {
    switch(S) {
        case UniformCost: 
            return 0; 
            break;
        case A_Star_MisplacedTile:
            // vector<int> openRecess;
            // vector<int> openState;
    
            // // find the open spaces in recesses and the main path
            // for (int i = 0; i < node.recess.length(); ++i) {
            //     if (node.recess[i] == '0')
            //         openRecess.push_back(i);
            // }
            // for (int i = 0; i < node.state.length(); ++i) {
            //     if (node.state[i] == '0')
            //         openState.push_back(i);
            // }



            break;
        case A_Star_Manhattan:
            long a = long(node.recess.find("1"));
            // if 1 is in a recess, we need to add 1
            // to compensate for the distance
            if (a < node.recess.length())
                return a + 1;
            else
                return long(node.state.find("1"));
            break;
    }
    return 0;
}

// expands a node and puts them into the queue
void ExpandNode(const Node node, priority_queue<Node, vector<Node>, SmallerCost> & children, SearchType S) {
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
            temp.setDepth(node.depth + 1);
            
            // we change the node to the next state
            temp.recess[openRecess[i]] = node.state[openRecess[i]];
            temp.state[openRecess[i]] = '0';

            temp.setCost(temp.depth + heuristic(S, temp));
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
            temp.setDepth(node.depth + 1);

            temp.state[openState[i]] = node.state[openState[i] - 1];
            temp.state[openState[i] - 1] = '0';

            temp.setCost(temp.depth + heuristic(S, temp));
            temp.setParent(node.recess + node.state);
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
        
        // move right
        if (openState[i] < node.state.length() - 1 && node.state[openState[i] + 1] != '0') {
            Node temp;
            temp.recess = node.recess;
            temp.state = node.state;
            temp.setDepth(node.depth + 1);
            
            temp.state[openState[i]] = node.state[openState[i] + 1];
            temp.state[openState[i] + 1] = '0';

            temp.setCost(temp.depth + heuristic(S, temp));
            temp.setParent(node.recess + node.state);
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
        
        // move up
        if (node.recess[openState[i]] != '-' && node.recess[openState[i]] != '0' ) {
            Node temp;
            temp.recess = node.recess;
            temp.state = node.state;
            temp.setDepth(node.depth + 1);

            temp.state[openState[i]] = node.recess[openState[i]];
            temp.recess[openState[i]] = '0';

            temp.setCost(temp.depth + heuristic(S, temp));
            temp.setParent(node.recess + node.state);
            if (node.parent != temp.recess + temp.state)
                children.push(temp);
        }
    }
}

Node Search(Node initState, SearchType search, const string& goal) {
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
        if (isGoalState(nodes.top(), goal)) {
            answer.setState(nodes.top().recess, nodes.top().state);
            answer.setDepth(nodes.top().depth);
            answer.setCost(nodes.top().cost);
            return answer;
        }
        // node was not a goal state. so we
        // expand the top node, then remove it
        ExpandNode(nodes.top(), nodes, search);
        nodes.pop();
    }

    return answer;
}