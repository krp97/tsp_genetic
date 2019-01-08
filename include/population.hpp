#include <algorithm>
#include <functional>
#include <random>
#include <vector>
#include "organism.hpp"

namespace atsp_genetic {

class population
{
   public:
    population() = default;
    population(size_t population_size, Adjacency_Matrix& matrix);
    population(const population& rhs) = default;
    population& operator=(const population& rhs) = default;
    population(population&& rhs) noexcept        = default;
    population& operator=(population&& rhs) noexcept = default;
    ~population()                                    = default;
    organism& operator[](int index) { return population_[index]; };

    std::vector<organism>::iterator begin() { return population_.begin(); };
    std::vector<organism>::iterator end() { return population_.end(); };

    void expand_population(organism);

    // Steady State approach with an elitist selection of organisms.
    void shrink_to_entry_size();

    // Crossover methods
    static organism order1(organism& organism1, organism& organism2,
                           Adjacency_Matrix& matrix);
    static organism uniform(organism& organism1, organism& organism2);

    // Mutation methods
    static void swap();
    static void insertion();

    std::string to_string();

   private:
    std::vector<organism> population_;
    size_t entry_size_;

    void add_organism(organism);
    void erase_organism(organism);
    void erase_organism(size_t index);

    static void copy_range(size_t a, size_t b, std::vector<int>&);
    static void fill_with_unique();
};
}  // namespace atsp_genetic