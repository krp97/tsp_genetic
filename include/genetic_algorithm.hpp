#include <functional>

#include "adjacency_matrix.hpp"
#include "organism.hpp"
#include "population.hpp"
#include "timer.hpp"

namespace atsp_genetic {

class genetic_alg
{
   public:
    genetic_alg() = delete;
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
    population population_;
    size_t population_size_;
    std::random_device r;
    const size_t iterations = 5;

    void crossover();
    std::pair<organism, organism> roulette_wheel();
    void calc_rw_probabilities(std::vector<std::pair<double, size_t>>& prob);

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