#include "header.h"

unordered_set<string> history; // prevents expansion of a previously visited node
unordered_set<string> movement; // prevents circular movement when expanding a node
Node goal;  // the goal state of the solution
            // we make it global to reduce overhead

long nodesExpanded = 0;

// function to check if the node is a goal state
bool isGoalState(Node n) {
    if (n.state[1].compare(goal.state[1]) == 0)
        return true;
    return false;
}

// function that returns the result of a heuristic calculation
int heuristic (SearchType S, Node& node) {
    int h;  // the heurisitc value

    switch(S) {
        // normal uniform cost search
        case UniformCost: 
            h = 0; 
            break;
        // Count and return number of misplaced tiles
        case MisplacedTiles:
            h = 0;
            for (int i = 0; i < node.state[0].length(); ++i)
                if (node.state[0][i] != '0' && goal.state[0][i] != node.state[0][i])
                    h++;

            for (int i = 0; i < node.state[1].length(); ++i)
                if (node.state[1][i] != '0' && goal.state[1][i] != node.state[1][i])
                    h++;

            break;
        // find the manhattan distance between 
        // the sergeant and position 0
        case Manhattan_On_Sergeant: 
            {
                h = 0;
                int temp = node.state[0].find('1');
                if (temp < node.state[0].length())
                    h = temp + 1;
                else
                    h = node.state[1].find('1');
            }
            break;
        // count the number of men between the sergeant
        // and position 0
        case Count_Obstructing_Men: 
            {
                h = 0;
                int sergeant = node.state[0].find('1');
                if (sergeant >= node.state[0].length())
                    sergeant = node.state[1].find('1');

                for (int i = 0; i < sergeant; ++i)
                    if (node.state[1][i] != '0')
                        h++;
            }
            break;
        // check each man that is in the correct position
        // if the man to his left is in the wrong position, 
        // increase the heuristic value
        case Check_Left_Man:
            h = 0;
            for (int i = 0; i < node.state.size(); ++i)
                for (int j = 1; j < node.state[i].length(); ++j)
                    if (node.state[i][j] != '-' && node.state[i][j] != '0' && 
                        goal.state[i][j] == node.state[i][j] && node.state[i][j-1] != goal.state[i][j-1])
                            h++;
            break;
    }

    // return the heuristic value
    return h;
}

// helper function for ExpandNodes()
// this function find alls possible moves a man at coordinate (i,j) can make using recursion
void ExpandNodeHelper(const int i, const int j, Node node, priority_queue<Node, vector<Node>, SmallerCost> & children, SearchType & S) {
    Node temp;
    string r, s;
    
    // move left
    if (j > 0 && node.state[i][j-1] == '0') {
        r = node.state[0];
        s = node.state[1];
        temp.setState(r,s);
        temp.state[i][j-1] = temp.state[i][j];
        temp.state[i][j] = '0';
        temp.setDepth(node.depth);
        temp.setCost (node.depth + heuristic(S, temp));
        // temp.setCost (node.cost + heuristic(S, temp));
        if (movement.insert(temp.state[0] + temp.state[1]).second) {
            children.push(temp);
            ExpandNodeHelper(i, j-1, temp, children, S);
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
        temp.setCost (node.depth + heuristic(S, temp));
        // temp.setCost (node.cost + heuristic(S, temp));
        if (movement.insert(temp.state[0] + temp.state[1]).second) {
            children.push(temp);
            ExpandNodeHelper(i, j+1, temp, children, S);
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
        temp.setCost (node.depth + heuristic(S, temp));
        // temp.setCost (node.cost + heuristic(S, temp));
        if (movement.insert(temp.state[0] + temp.state[1]).second) {
            children.push(temp);
            ExpandNodeHelper(i-1, j, temp, children, S);
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
        temp.setCost (node.depth + heuristic(S, temp));
        // temp.setCost (node.cost + heuristic(S, temp));
        if (movement.insert(temp.state[0] + temp.state[1]).second) {
            children.push(temp);
            ExpandNodeHelper(i+1, j, temp, children, S);
        }
    }
  
}

// function that expands a node and puts them into the queue
void ExpandNode(Node node, priority_queue<Node, vector<Node>, SmallerCost> & children, SearchType & S) {
        nodesExpanded++;
        for (int i = node.state.size() - 1; i >= 0; --i)
            for (int j = node.state[i].size() - 1; j >= 0; --j)
                if (node.state[i][j] != '-' && node.state[i][j] != '0') {
                    Node temp;
                    string r, s;
                    r = node.state[0];
                    s = node.state[1];
                    temp.setState(r,s);
                    temp.setDepth(node.depth + 1);
                    temp.setCost(node.cost + 1);

                    movement.clear();
                    ExpandNodeHelper(i, j, temp, children, S);
                }
}

// the generic search function
Node Search(Node initState, SearchType search, const Node& goalState) {
    priority_queue<Node, vector<Node>, SmallerCost> nodes; // queue of nodes to check
    Node answer;    // use this to store the answer

    goal.setState(goalState.state[0], goalState.state[1]);
    nodes.push(initState); // initialize the queue

    // initialize answer to all blanks
    // we return all blanks if no goal
    // state is found
    answer.setState("no solution", "no solution");
    answer.setCost(-1);
    
    while (!nodes.empty()) {
        // print the current queue size
        cout << "node size: " << nodes.size() << endl;

        // we grab and print the top node
        Node temp = nodes.top();
        temp.print();
        
        // check if it is the goal state
        // if it is, then return it
        if (isGoalState(temp)) {
            answer.setState(temp.state[0], temp.state[1]);
            answer.setDepth(temp.depth);
            answer.setCost(temp.cost);

            cout << endl << "nodes expanded: " << nodesExpanded << endl;

            return answer;
        }

        // node was not a goal state. so we
        // check if we have expanded it in the past
        // if not, we expand it, then remove it
        // otherwise, we simply remove it
        if (history.insert(temp.state[0] + temp.state[1]).second)
            ExpandNode(nodes.top(), nodes, search);
        
        nodes.pop();
    }

    // we return our results
    cout << "nodes expanded: " << nodesExpanded << endl;
    cout << "faoweiuhfap;wioefh;awiefa;wieofha;weif" << endl;
    return answer;
}