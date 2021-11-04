#include "header.h"

// int main(int argc, char** argv) {
int main () {
    Node InitialState;
    Node goal;

    // solves in 3 depth
    // InitialState.setState("--0-0--", "0123000");
    // goal = "1230000";

    // solves in 4 depth
    // InitialState.setState("--1-2--", "0003000");
    // goal = "1230000";

    // solves in 8 depth
    InitialState.setState("--0-0--", "4123000");
    goal.setState("--0-0--", "1234000");

    // solves in 1 depth
    // InitialState.setState("--0-0--", "0000001");
    // goal = "1000000";

    // solves in 28 depth, currently 31
    // InitialState.setState("---0-0-0--", "0234567891");
    // goal.setState("---0-0-0--", "1234567890");

    InitialState.setCost(0);
    InitialState.setDepth(0);
    
    Node answer;
    int preferedSearch = -1;

    cout << "Welcome to 9 Men in a Trench solver\n";
    cout << "Select the your prefered search type:\n";
    cout << "1. Uniform Cost Search" << endl 
         << "2. A* with Missing Tile Heuristic" << endl
         << "3. A* with Manhattan Heuristic with 1" << endl;
    
    do {
        cin >> preferedSearch;
    } while (preferedSearch > 3  || preferedSearch < 1);
    preferedSearch--;

    switch (preferedSearch) {
        case UniformCost :
            answer = Search(InitialState, UniformCost, goal); 
            break;
        case A_Star_MisplacedTile : 
            answer = Search(InitialState, A_Star_MisplacedTile, goal); 
            break;
        case A_Star_Manhattan :
            answer = Search(InitialState, A_Star_Manhattan, goal);
            break;
    }
    

    cout << endl << "---FINAL ANSWER---" << endl;
    answer.print();

    return 0;
}