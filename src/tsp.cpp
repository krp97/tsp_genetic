#include "../include/tsp.hpp"

tsp::tsp(double time_limit, double mutation_prob, double cross_prob)
    : time_limit_ {time_limit},
      mutation_prob_ {mutation_prob},
      cross_prob_ {cross_prob}
{
}

int tsp::get_matrix_size() const { return matrix_.size(); }

atsp_genetic::organism tsp::genetic_algo(
    std::function<atsp_genetic::organism(
        atsp_genetic::organism&, atsp_genetic::organism&, Adjacency_Matrix&)>
        cross_fnc_,
    std::function<void(atsp_genetic::population&, Adjacency_Matrix&)>
        mutation_fnc_)
{
    auto ga = atsp_genetic::genetic_alg(matrix_, cross_fnc_, mutation_fnc_, 50);
    Timer<atsp_genetic::organism> timer = Timer<atsp_genetic::organism>(
        [&](Timer<atsp_genetic::organism>* timer) -> atsp_genetic::organism {
            return ga.run(timer, cross_prob_, mutation_prob_);
        },
        time_limit_);
    timer.run();
    return timer.get_output();
}

void tsp::load_from_file(std::string filepath)
{
    try
    {
        matrix_   = Adjacency_Matrix(filepath);
        is_loaded = true;
    } catch (const std::invalid_argument&)
    {
        throw;
    }
}