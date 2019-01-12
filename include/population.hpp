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
    size_t size();

    // Crossover methods
    static organism order1(organism& organism1, organism& organism2,
                           Adjacency_Matrix& matrix);
    static organism uniform(organism& organism1, organism& organism2,
                            Adjacency_Matrix& matrix);

    // Mutation methods
    static void swap(population& p, Adjacency_Matrix& matrix);
    static void insertion(population& p, Adjacency_Matrix& matrix);

    std::string to_string();

   private:
    std::vector<organism> population_;
    size_t entry_size_;
    size_t organism_size_;

    // Crossover helper functions
    static void order1(organism& org, std::vector<int>& path);
    static void uniform(std::vector<int>& path, std::vector<int>::iterator it1,
                        std::vector<int>::iterator it2);
    void add_organism(organism);
    void erase_organism(organism);
    void erase_organism(size_t index);

    organism& random_organism();
    void fill_with_unique();
};
}  // namespace atsp_genetic