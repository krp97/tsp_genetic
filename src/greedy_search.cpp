#include "../include/greedy_search.hpp"
#include <iostream>
#include <limits>

namespace atsp_genetic {
greedy_search::greedy_search(Adjacency_Matrix& matrix) : matrix_ {matrix} {}

organism greedy_search::run()
{
    organism path;
    auto visited = std::vector<bool>(matrix_.size(), false);
    path.add_to_path(0, 0);
    visited[0] = true;
    run(path, visited);
    path.add_to_path(0, matrix_[path[path.size() - 1]][0]);
    return path;
}

void greedy_search::run(organism& path, std::vector<bool>& visited)
{
    int index {0};
    for (auto it {matrix_.begin()}; !all_visited(visited);)
    {
        index = get_minimum(*it, visited);
        path.add_to_path(index, (*it)[index]);

        visited[index] = true;
        it             = matrix_.begin() + index;
    }
}

int greedy_search::get_minimum(std::vector<int>& row,
                               std::vector<bool>& visited)
{
    int min = std::numeric_limits<int>::max(), index = 0, min_index = 0;

    for (auto it {row.begin()}; it != std::end(row); ++it)
    {
        index = it - row.begin();
        if (*it < min && !visited[index])
        {
            min       = *it;
            min_index = index;
        }
    }
    return min_index;
}

bool greedy_search::all_visited(std::vector<bool>& visited)
{
    return std::find(visited.begin(), visited.end(), false) ==
           std::end(visited);
}
}  // namespace atsp_genetic
