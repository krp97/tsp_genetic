#include "../include/organism.hpp"
#include <chrono>
#include <random>

namespace atsp_genetic {
organism::organism() : path_ {std::vector<int>()}, cost_ {0} {}

organism::organism(Adjacency_Matrix& matrix)
    : path_ {std::vector<int>(matrix.size() + 1)}
{
    std::iota(path_.begin(), path_.end() - 1, 0);
    path_[matrix.size()] = 0;
    std::shuffle(
        path_.begin() + 1, path_.end() - 1,
        std::mt19937(
            std::chrono::steady_clock::now().time_since_epoch().count()));
    recalc_cost(matrix);
}

organism::organism(std::vector<int> path, Adjacency_Matrix& matrix)
{
    path_ = path;
    recalc_cost(matrix);
}

void organism::recalc_cost(Adjacency_Matrix& matrix)
{
    cost_ = 0;
    for (size_t i {0}; i < path_.size() - 1; ++i)
        cost_ += matrix[path_[i]][path_[i + 1]];
}

void organism::erase(size_t index) { path_.erase(std::begin(path_) + index); }

void organism::insert(size_t index, int value)
{
    path_.insert(std::begin(path_) + index, value);
}

std::string organism::to_string() const
{
    std::string organism {get_path_str()};
    std::string cost {get_cost_str()};
    std::string output {organism + "\n\n" + cost};
    return output;
}

std::string organism::get_path_str() const
{
    auto output {std::string("organism >> ")};
    for (size_t i {0}; i < path_.size(); ++i)
    {
        output += std::to_string(path_[i]);
        if (i < path_.size() - 1)
            output += "->";
    }
    return output;
}

std::string organism::get_cost_str() const
{
    return std::string("Cost >> " + std::to_string(cost_));
}

std::vector<int> organism::get_range(int a, int b) const
{
    return std::vector<int>(path_.begin() + std::min(a, b), path_.begin() + std::max(a, b));
}
}  // namespace atsp_genetic
