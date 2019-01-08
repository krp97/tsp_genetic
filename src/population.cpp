#include "../include/population.hpp"
namespace atsp_genetic {
population::population(size_t population_size, Adjacency_Matrix& matrix)
    : entry_size_ {population_size}
{
    std::random_device dev;
    population_.resize(population_size);
    for (auto& o_it : population_)
        o_it = organism(matrix, dev);
}

std::string population::to_string()
{
    auto output {std::string()};
    for (auto& p : population_)
        output += p.to_string() + "\n";
    return output;
}

void population::expand_population(organism org) { population_.push_back(org); }

void population::shrink_to_entry_size()
{
    std::sort(population_.begin(), population_.end());
    population_.erase(population_.begin() + entry_size_, population_.end());
}

organism population::order1(organism& organism1, organism& organism2,
                            Adjacency_Matrix& matrix)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<size_t> uni(1, organism1.size() - 1);
    size_t first  = uni(rng);
    size_t second = uni(rng);
    auto range_copy {organism1.get_range(first, second)};

    auto tmp_path {std::vector<int>(organism1.size())};
    std::copy(range_copy.begin(), range_copy.end(), tmp_path.begin() + first);

    int index {0};
    for (auto& o_it : organism2)
    {
        if (std::end(tmp_path) ==
            std::find(tmp_path.begin(), tmp_path.end(), o_it))
        {
            tmp_path.insert(tmp_path.begin() + index, o_it);
        }
        ++index;
    }
    return organism(tmp_path, matrix);
}

organism population::uniform(organism& organism1, organism& organism2) {}

}  // namespace atsp_genetic
