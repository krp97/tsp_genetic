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
    while (!timer->is_finished())
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
    int index1 {utils::random_int(0, population_size_)};
    int index2 {utils::random_int(0, population_size_)};
    auto org = cross_fnc_(population_[index1], population_[index2], matrix_);
    population_.expand_population(org);
}

std::pair<organism, organism> genetic_alg::roulette_wheel()
{
    auto probabilities {
        std::vector<std::pair<double, size_t>>(population_.size())};
    calc_rw_probabilities(probabilities);
    std::sort(probabilities.begin(), probabilities.end(), sort_pairs());
    auto output = {population_[probabilities[0].second],
                   population_[probabilities[1].second]};
}

void genetic_alg::calc_rw_probabilities(
    std::vector<std::pair<double, size_t>>& prob)
{
    int cost_sum {0};
    std::for_each(population_.begin(), population_.end(),
                  [&](organism& o) { cost_sum += o.get_cost(); });

    for (size_t i {0}; i < prob.size(); ++i)
    {
        prob[i].first  = 1 - (population_[i].get_cost() / cost_sum);
        prob[i].second = i;
    }
}
}  // namespace atsp_genetic