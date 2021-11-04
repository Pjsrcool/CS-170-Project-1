#include "header.h"

unordered_set<string> history;

// check if the node is a goal state
bool isGoalState(Node n, const string & goal) {
    if (n.state[1].compare(goal) == 0)
        return true;
    return false;
}

long heuristic (SearchType S, const Node& node) {
    switch(S) {
        case UniformCost: 
            return 0; 
            break;
        case A_Star_MisplacedTile:

            break;
        case A_Star_Manhattan:
            long a = long(node.state[0].find("1"));
            // if 1 is in a recess, we need to add 1
            // to compensate for the distance
            if (a < node.state[0].length())
                return a + 1;
            else
                return long(node.state[1].find("1"));
            break;
    }
    return 0;
}

void ExpandNodeHelper(const int i, const int j, Node node, priority_queue<Node, vector<Node>, SmallerCost> & children, SearchType & S) {
    Node temp;
    string r, s;
    // cout << i << j << endl;
    // if (history.insert(node.state[0] + node.state[1] + std::to_string(i) + std::to_string(j)).second ) {
        // move left
        if (j > 0 && node.state[i][j-1] == '0') {
            r = node.state[0];
            s = node.state[1];
            temp.setState(r,s);
            temp.state[i][j-1] = temp.state[i][j];
            temp.state[i][j] = '0';
            temp.setDepth(node.depth);
            temp.setCost (temp.depth + heuristic(S, temp));
            if (history.insert(temp.state[0] + temp.state[1]).second) {
                children.push(temp);
                ExpandNodeHelper(i, j-1, temp, children, S);
            }
        }
        // move down
        if (i < node.state.size() - 1 && node.state[i+1][j] == '0') {
            r = node.state[0];
            s = node.state[1];
            s[j] = r[j];
            r[j] = '0';
            temp.setState(r,s);
            temp.setDepth(node.depth);
            temp.setCost (temp.depth + heuristic(S, temp));
            if (history.insert(temp.state[0] + temp.state[1]).second) {
                children.push(temp);
                ExpandNodeHelper(i+1, j, temp, children, S);
            }
        }
        // move up
        if (i > 0 && node.state[i-1][j] == '0') {
            r = node.state[0];
            s = node.state[1];
            r[j] = s[j];
            s[j] = '0';
            temp.setState(r,s);
            temp.setDepth(node.depth);
            temp.setCost (temp.depth + heuristic(S, temp));
            if (history.insert(temp.state[0] + temp.state[1]).second) {
                children.push(temp);
                ExpandNodeHelper(i-1, j, temp, children, S);
            }
        }
        
        // move right
        if (j < node.state[i].length() - 1 && node.state[i][j+1] == '0') {
            r = node.state[0];
            s = node.state[1];
            temp.setState(r,s);
            temp.state[i][j+1] = temp.state[i][j];
            temp.state[i][j] = '0';
            temp.setDepth(node.depth);
            temp.setCost (temp.depth + heuristic(S, temp));
            if (history.insert(temp.state[0] + temp.state[1]).second) {
                children.push(temp);
                ExpandNodeHelper(i, j+1, temp, children, S);
            }
        }
    // }
}

// expands a node and puts them into the queue
void ExpandNode(Node node, priority_queue<Node, vector<Node>, SmallerCost> & children, SearchType & S) {
    for (int i = 0; i < node.state.size(); ++i)
        for (int j = 0; j < node.state[i].length(); ++j)
            if (node.state[i][j] != '-' && node.state[i][j] != '0') {
                // cout << i << j << endl;
                Node temp;
                string r, s;
                r = node.state[0];
                s = node.state[1];
                temp.setState(r,s);
                temp.setDepth(node.depth + 1);
                temp.setCost(node.cost);
                ExpandNodeHelper(i, j, temp, children, S);
            }
}

Node Search(Node initState, SearchType search, const string& goal) {
    priority_queue<Node, vector<Node>, SmallerCost> nodes;
    Node answer;

    // initialize the queue
    nodes.push(initState);
    history.insert(initState.state[0] + initState.state[1]);

    // initialize answer to all blanks
    // we return all blanks if no goal
    // state is found
    answer.setState("no solution", "no solution");
    answer.setCost(-1);

    while (!nodes.empty()) {
        cout << "node size: " << nodes.size() << endl;
        // we grab and print the top node
        Node temp = nodes.top();
        temp.print();
        
        // check if it is the goal state
        // if it is, then return it
        if (isGoalState(temp, goal)) {
            answer.setState(temp.state[0], temp.state[1]);
            answer.setDepth(temp.depth);
            answer.setCost(temp.cost);
            return answer;
        }
        // node was not a goal state. so we
        // expand the top node, then remove it
        ExpandNode(nodes.top(), nodes, search);
        nodes.pop();
    }

    return answer;
}