#include "header.h"

// int main(int argc, char** argv) {
int main () {
    vector<vector<int>> temp;
    temp.push_back({-1,-1,-1,0,-1,0,-1, 0,-1, -1});
    temp.push_back({0,2,3,4,5,6,7,8,9,1});

    Node* init = new Node(temp, nullptr);
    init->print();

    

    std::cout << "hello world\n\n";
    return 0;
}