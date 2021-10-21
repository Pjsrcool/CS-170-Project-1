#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <queue>
#include <vector>

using std::vector, std::queue;

vector<vector<int>> UniformCostSearch();
vector<vector<int>> AStar_MisplacedTile();
vector<vector<int>> AStar_Manhattan();

#endif /*HEADER_H*/