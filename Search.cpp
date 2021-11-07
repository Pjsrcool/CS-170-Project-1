#include "header.h"

unordered_set<string> history; // prevents expansion of a previously visited node
unordered_set<string> movement; // prevents circular movement when expanding a node
int misplaceTileHelper;
Node goal;

// check if the node is a goal state
bool isGoalState(Node n) {
    if (n.state[1].compare(goal.state[1]) == 0)
        return true;
    return false;
}

int heuristic (SearchType S, Node& node) {
    int h;

    switch(S) {
        case UniformCost: 
            h = 0; 
            break;
        case MisplacedTiles:
            h = 0;
            for (int i = 0; i < node.state[0].length(); ++i)
                if (node.state[0][i] != '0' && goal.state[0][i] != node.state[0][i])
                    h++;

            for (int i = 0; i < node.state[1].length(); ++i)
                if (node.state[1][i] != '0' && goal.state[1][i] != node.state[1][i])
                    h++;

            break;
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
        case Check_Left_Man:
            h = 0;
            for (int i = 0; i < node.state.size(); ++i)
                for (int j = 1; j < node.state[i].length(); ++j)
                    if (node.state[i][j] != '-' && node.state[i][j] != '0' && 
                        goal.state[i][j] == node.state[i][j] && node.state[i][j-1] != goal.state[i][j-1])
                            h++;
            break;
    }
    // node.print();
    // cout << "heuristic: " << h << endl;
    return h;
}

// maybe try bfs instead of dfs
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

// expands a node and puts them into the queue
void ExpandNode(Node node, priority_queue<Node, vector<Node>, SmallerCost> & children, SearchType & S) {
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

Node Search(Node initState, SearchType search, const Node& goalState) {
    priority_queue<Node, vector<Node>, SmallerCost> nodes;
    Node answer;
    goal.setState(goalState.state[0], goalState.state[1]);
    // initialize the queue
    nodes.push(initState);
    // history.insert(initState.state[0] + initState.state[1]);

    // where to begin searching for 0's in the 
    // missing tile heuristic
    misplaceTileHelper = goal.state[1].find('0');

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
        if (isGoalState(temp)) {
            answer.setState(temp.state[0], temp.state[1]);
            answer.setDepth(temp.depth);
            answer.setCost(temp.cost);
            return answer;
        }
        // node was not a goal state. so we
        // expand the top node, then remove it
        if (history.insert(temp.state[0] + temp.state[1]).second)
            ExpandNode(nodes.top(), nodes, search);
        
        nodes.pop();
    }

    return answer;
}