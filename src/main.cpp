#include <time.h>
#include <iostream>
#include <random>
#include "../include/adjacency_matrix.hpp"
#include "../include/menu_handler.hpp"
#include "../include/population.hpp"
#include "utils.cpp"

int main()
{
    srand(time(NULL));
    Menu m {Menu()};
    std::vector<std::string> subtitles = {
        "Set the time limit [ms].",
        "Set the crossover probability.",
        "Set the mutation probability.",
        "Load the graph from a file (.txt only).",
        "Run the algorithms.",
        "Convert from TSPLIB to txt.",
        "Exit"};
    m.run(subtitles, "Menu");
    return 0;
}
