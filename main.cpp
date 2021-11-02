#include "header.h"

// int main(int argc, char** argv) {
int main () {
    Node InitialState;
    InitialState.recess = "__0_0__";
    // InitialState.state = "0123000";
    InitialState.state = "0203010";
    // InitialState.state = "0003000";
    InitialState.parent = " ";
    InitialState.setCost(0);
    
    Node answer = UniformCostSearch(InitialState);
    // cout<<isGoalState(InitialState) << endl;
    // InitialState.print();
    answer.print();

    cout << "done\n\n";
    return 0;
}