#include <time.h>
#include <iostream>
#include <random>
#include "../include/adjacency_matrix.hpp"
#include "../include/population.hpp"

int main()
{
    auto matrix {Adjacency_Matrix("../data/tsp_48.txt")};
    std::random_device g;
    auto org1 {organism(matrix, g)};
    auto org2 {organism(matrix, g)};
    getchar();
    return 0;
}
