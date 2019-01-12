#include <time.h>
#include <iostream>
#include <random>
#include "../include/adjacency_matrix.hpp"
#include "../include/population.hpp"
#include "utils.cpp"
int main()
{
    srand(time(NULL));
    auto matrix {Adjacency_Matrix("../data/tsp_6_2.txt")};
    auto pop = atsp_genetic::population(10, matrix);

    std::cout << " ----------------------RODZICE:\n";
    std::cout << pop[1].to_string() << std::endl;
    std::cout << pop[2].to_string() << std::endl;
    std::cout << "-----------------------DZIECKO:\n";
    std::cout
        << atsp_genetic::population::uniform(pop[1], pop[2], matrix).to_string();
    return 0;
}
