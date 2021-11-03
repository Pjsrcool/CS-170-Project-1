#include "header.h"

// int main(int argc, char** argv) {
int main () {
    Node InitialState;
    InitialState.recess = "--0-0--";
    // InitialState.state = "0123000";
    InitialState.state = "0123000";
    // InitialState.state = "0003000";
    InitialState.setParent(" ");
    InitialState.setCost(0);
    
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
            answer = Search(InitialState, UniformCost); 
            break;
        case A_Star_MisplacedTile : 
            answer = Search(InitialState, A_Star_MisplacedTile); 
            break;
        case A_Star_Manhattan :
            answer = Search(InitialState, A_Star_Manhattan);
            break;
    }
    

    cout << endl << "---FINAL ANSWER---" << endl;
    answer.print();

    return 0;
}