#include "../include/organism.hpp"
#include <random>

organism::organism() : organism_ {std::vector<int>()}, cost_ {0} {}

organism::organism(Adjacency_Matrix& matrix, std::random_device& dev)
{
    organism_ = std::vector<int>(matrix.size() + 1);
    std::iota(organism_.begin(), organism_.end() - 1, 0);
    organism_[matrix.size()] = 0;
    std::shuffle(organism_.begin() + 1, organism_.end() - 1,
                 std::mt19937 {dev()});
    recalc_cost(matrix);
}

organism::organism(std::vector<int> path, Adjacency_Matrix& matrix)
{
    organism_ = path;
    recalc_cost(matrix);
}

void organism::recalc_cost(Adjacency_Matrix& matrix)
{
    cost_ = 0;
    for (size_t i {0}; i < organism_.size() - 1; ++i)
        cost_ += matrix[organism_[i]][organism_[i + 1]];
}

void organism::erase(size_t index)
{
    organism_.erase(std::begin(organism_) + index);
}

void organism::insert(size_t index, int value)
{
    organism_.insert(std::begin(organism_) + index, value);
}

std::string organism::to_string() const
{
    std::string organism {get_organism_str()};
    std::string cost {get_cost_str()};
    std::string output {organism + "\n\n" + cost};
    return output;
}

std::string organism::get_organism_str() const
{
    auto output {std::string("organism >> ")};
    for (size_t i {0}; i < organism_.size(); ++i)
    {
        output += std::to_string(organism_[i]);
        if (i < organism_.size() - 1)
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
    return std::vector<int>(organism_.begin() + a, organism_.begin() + b);
}
