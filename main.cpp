#include "header.h"

int main(int argc, char** argv) {
    Node InitialState;  // inital state of the problem
    Node goal;          // goal state of the problem
    time_point<std::chrono::system_clock> start, end; // we use this to find the run time
    Node answer;    // used to store the final state of the solution
    int preferedSearch = -1;    // the type of search we want to perform

    // initialize the Initial state of the problem with
    // commandline arguments
    InitialState.setState(argv[1], argv[2]);
    InitialState.setCost(0);
    InitialState.setDepth(0);

    // initialize the goal state with
    // commandline argumetns
    goal.setState(argv[3], argv[4]);

    // promp the user to select which search to use
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

    // record the current time and begin the search
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
    
    // after the search we record the time
    // we substract the times to find how many
    // seconds it took the search to complete
    duration<double> runTime = end - start;

    // display results
    cout << endl << "---FINAL ANSWER---" << endl;
    answer.print();
    cout << "--> Run time: " << runTime.count() << " seconds" << endl;

    return 0;
}