#include "header.h"

int main(int argc, char** argv) {
// int main () {
    Node InitialState;
    Node goal;
    time_point<std::chrono::system_clock> start, end;

    InitialState.setState(argv[1], argv[2]);
    InitialState.setCost(0);
    InitialState.setDepth(0);

    goal.setState(argv[3], argv[4]);
    
    Node answer;
    int preferedSearch = -1;

    cout << "Welcome to 9 Men in a Trench solver\n";
    cout << "Select the your prefered search type:\n";
    cout << "1. Uniform Cost Search" << endl 
         << "2. Misplaced Tiles Heuristic" << endl
         << "3. Manhattan Heuristic with Sergeant" << endl
         << "4. Count Obstructing Men Heuristic" << endl
         << "5. Check Left Man of each man in correct place" << endl;
    
    do {
        cin >> preferedSearch;
    } while (preferedSearch > 5  || preferedSearch < 1);
    preferedSearch--;

    start = system_clock::now();
    switch (preferedSearch) {
        case UniformCost :
            answer = Search(InitialState, UniformCost, goal); 
            break;
        case MisplacedTiles : 
            answer = Search(InitialState, MisplacedTiles, goal); 
            break;
        case Manhattan_On_Sergeant :
            answer = Search(InitialState, Manhattan_On_Sergeant, goal);
            break;
        case Count_Obstructing_Men :
            answer = Search(InitialState, Count_Obstructing_Men, goal);
            break;
        case Check_Left_Man :
            answer = Search(InitialState, Check_Left_Man, goal);
            break;
    }
    end = system_clock::now();
    
    duration<double> runTime = end - start;

    cout << endl << "---FINAL ANSWER---" << endl;
    answer.print();
    cout << "--> Run time: " << runTime.count() << " seconds" << endl;

    return 0;
}