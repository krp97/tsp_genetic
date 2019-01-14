#include "../include/population.hpp"
#include "utils.cpp"

namespace atsp_genetic {
population::population(size_t population_size, Adjacency_Matrix& matrix)
    : entry_size_ {population_size}, organism_size_ {matrix.size() + 1}
{
    std::random_device dev;
    population_.resize(population_size);
    for (auto& o_it : population_)
        o_it = organism(matrix);
}

std::string population::to_string()
{
    auto output {std::string()};
    for (auto& p : population_)
        output += p.to_string() + "\n";
    return output;
}

size_t population::size() { return population_.size(); }

void population::expand_population(organism org) { population_.push_back(org); }

void population::shrink_to_entry_size()
{
    std::sort(population_.begin(), population_.end());
    population_.erase(population_.begin() + entry_size_, population_.end());
}

organism population::order1(organism& organism1, organism& organism2,
                            Adjacency_Matrix& matrix)
{
    size_t first  = utils::random_int(1, organism1.size() - 1);
    size_t second = utils::random_int(1, organism1.size() - 1);
    while (second == first)
        second = utils::random_int(1, organism1.size() - 1);

    auto range_copy = organism1.get_range(first, second);
    auto tmp_path   = std::vector<int>(organism1.size());
    std::copy(range_copy.begin(), range_copy.end(),
              tmp_path.begin() + std::min(first, second));
    order1_help(organism2, tmp_path);
    return organism(tmp_path, matrix);
}

void population::order1_help(organism& org, std::vector<int>& path)
{
    int index {1};
    for (auto& o_it : org)
    {
        while (path[index] != 0)
            ++index;
        if (std::end(path) == std::find(path.begin(), path.end(), o_it))
            path[index] = o_it;
    }
}

organism population::uniform(organism& organism1, organism& organism2,
                             Adjacency_Matrix& matrix)
{
    auto it_org1 {organism1.begin() + 1};
    auto it_org2 {organism2.begin() + 1};
    auto tmp_path                  = std::vector<int>(organism1.size());
    tmp_path[0]                    = 0;
    tmp_path[organism1.size() - 2] = 0;
    uniform_help(tmp_path, it_org1, it_org2);
    return organism(tmp_path, matrix);
}

void population::uniform_help(std::vector<int>& path,
                              std::vector<int>::iterator it1,
                              std::vector<int>::iterator it2)
{
    for (int index {1}; *it1 != 0 && *it2 != 0;)
    {
        std::vector<int>::iterator& rand_it =
            utils::random_double(0, 1) > 0.5 ? it1 : it2;
        if (std::end(path) == std::find(path.begin(), path.end(), *rand_it))
        {
            path[index] = *rand_it;
            ++index;
        }
        ++rand_it;
    }
}

organism& population::random_organism()
{
    int index {utils::random_int(0, population_.size() - 1)};
    return population_[index];
}

void population::swap(population& p, Adjacency_Matrix& matrix)
{
    organism& org {p.random_organism()};
    int index1 {utils::random_int(1, org.size() - 2)};
    int index2 {utils::random_int(1, org.size() - 2)};
    std::swap(org[index1], org[index2]);
    org.recalc_cost(matrix);
}

void population::insertion(population& p, Adjacency_Matrix& matrix)
{
    organism& org {p.random_organism()};
    int index1 {utils::random_int(1, org.size() - 2)};
    int index2 {utils::random_int(1, org.size() - 2)};
    int value {org[index1]};
    org.erase(index1);
    org.insert(index2, value);
    org.recalc_cost(matrix);
}
}  // namespace atsp_genetic
