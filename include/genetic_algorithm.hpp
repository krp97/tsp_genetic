#pragma once

#include <functional>
#include <numeric>
#include "adjacency_matrix.hpp"
#include "organism.hpp"
#include "population.hpp"
#include "timer.hpp"

namespace atsp_genetic {

class genetic_alg
{
   public:
    genetic_alg() = default;
    genetic_alg(
        Adjacency_Matrix&,
        std::function<organism(organism&, organism&, Adjacency_Matrix&)>
            cross_fnc_,
        std::function<void(population&, Adjacency_Matrix&)> mutation_fnc_,
        size_t population_size);

    genetic_alg(const genetic_alg& rhs) = default;
    genetic_alg& operator=(const genetic_alg& rhs) = default;
    genetic_alg(genetic_alg&& rhs) noexcept        = default;
    genetic_alg& operator=(genetic_alg&& rhs) noexcept = default;
    ~genetic_alg()                                     = default;

    organism run(Timer<organism>* timer, double crossover_prob,
                 double mutation_prob);

   private:
    Adjacency_Matrix& matrix_;
    std::function<organism(organism&, organism&, Adjacency_Matrix&)> cross_fnc_;
    std::function<void(population&, Adjacency_Matrix&)> mutation_fnc_;
    size_t population_size_;
    population population_;
    size_t iterations = 10;

    void crossover();
    std::pair<organism, organism> roulette_wheel();
    long get_fitness_sum();
    long get_inverted_sum(int fitness_sum);
    std::vector<double> get_probabilities(int inverted_sum, int fitness_sum);
    size_t spin_roulette(std::vector<double>& probabilities,
                         size_t ignore_index = -1);

    struct sort_pairs
    {
        bool operator()(const std::pair<double, size_t>& a,
                        const std::pair<double, size_t>& b)
        {
            return (a.first > b.first);
        }
    };
};
}  // namespace atsp_genetic