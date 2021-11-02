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
    answer = Search(InitialState, UniformCost);

    cout << endl << "---FINAL ANSWER---" << endl;
    answer.print();

    return 0;
}