#include "../include/organism.hpp"

organism::organism() : organism_ {std::vector<int>()}, cost_ {0} {}

organism::organism(std::vector<int> organism, const int cost,
                   const std::string& algo_name)
    : organism_ {organism}, cost_ {cost}, algo_name_ {algo_name}
{
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

std::string organism::to_string()
{
    std::string organism {get_organism_str()};
    std::string cost {get_cost_str()};
    std::string output {organism + "\n\n" + cost};
    return output;
}

std::string organism::get_organism_str()
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

std::string organism::get_cost_str()
{
    return std::string("Cost >> " + std::to_string(cost_));
}
