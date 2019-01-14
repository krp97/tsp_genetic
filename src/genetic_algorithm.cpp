#include "../include/genetic_algorithm.hpp"
#include "utils.cpp"

namespace atsp_genetic {

genetic_alg::genetic_alg(
    Adjacency_Matrix& matrix,
    std::function<organism(organism&, organism&, Adjacency_Matrix&)> cross_fnc,
    std::function<void(population&, Adjacency_Matrix&)> mutation_fnc,
    size_t population_size)
    : matrix_ {matrix},
      cross_fnc_ {cross_fnc},
      mutation_fnc_ {mutation_fnc},
      population_size_ {population_size},
      population_ {population(population_size_, matrix_)}
{
}

organism genetic_alg::run(Timer<organism>* timer, double crossover_prob,
                          double mutation_prob)
{
    while (timer->is_finished())
    {
        for (int i {0}; i < iterations; ++i)
        {
            if (utils::random_double(0.0, 1.0) < crossover_prob)
                crossover();
            if (utils::random_double(0.0, 1.0) < mutation_prob)
                mutation_fnc_(population_, matrix_);
        }
        population_.shrink_to_entry_size();
    }
    return *std::min_element(population_.begin(), population_.end());
}

void genetic_alg::crossover()
{
    auto parents {roulette_wheel()};
    auto org = cross_fnc_(parents.first, parents.second, matrix_);
    population_.expand_population(org);
}

std::pair<organism, organism> genetic_alg::roulette_wheel()
{
    int overall_fit {get_fitness_sum()};
    int inverted_fit {get_inverted_sum(overall_fit)};
    auto probabilities {get_probabilities(inverted_fit, overall_fit)};
    size_t first  = spin_roulette(probabilities);
    size_t second = spin_roulette(probabilities, first);
    return {population_[first], population_[second]};
}

long genetic_alg::get_fitness_sum()
{
    long cost_sum {0};
    std::for_each(population_.begin(), population_.end(),
                  [&](organism& o) { cost_sum += o.get_cost(); });
    return cost_sum;
}

long genetic_alg::get_inverted_sum(int fitness_sum)
{
    long inverted_sum {0};
    std::for_each(population_.begin(), population_.end(), [&](organism& o) {
        inverted_sum += fitness_sum - o.get_cost();
    });
    return inverted_sum;
}

std::vector<double> genetic_alg::get_probabilities(int inverted_sum,
                                                   int fitness_sum)
{
    auto probabilities {std::vector<double>(population_.size())};
    double prev_prob {0.0};
    for (size_t it {0}; it < population_.size(); ++it)
    {
        probabilities[it] = (fitness_sum - population_[it].get_cost()) /
                            static_cast<double>(inverted_sum);
        probabilities[it] += static_cast<double>(prev_prob);
        prev_prob = probabilities[it];
    }
    return probabilities;
}

size_t genetic_alg::spin_roulette(std::vector<double>& probabilities,
                                  size_t ignore_index)
{
    double rand_prob {utils::random_double(0, 1)};
    auto it      = std::find_if(probabilities.begin(), probabilities.end(),
                           [&](double prob) { return rand_prob < prob; });
    size_t index = it - probabilities.begin();
    if (index == probabilities.size())
        index = probabilities.size() - 1;
    return index == ignore_index ? spin_roulette(probabilities, ignore_index)
                                 : index;
}
}  // namespace atsp_genetic