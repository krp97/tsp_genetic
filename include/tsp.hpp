#pragma once

#include <string>

#include <functional>
#include "adjacency_matrix.hpp"
#include "genetic_algorithm.hpp"
#include "organism.hpp"

class tsp
{
   public:
    double time_limit_;
    double mutation_prob_;
    double cross_prob_;

    tsp()  = default;
    ~tsp() = default;

    tsp(const tsp&) = default;
    tsp(tsp&&)      = default;

    tsp& operator=(const tsp&) = default;
    tsp& operator=(tsp&&) = default;

    tsp(double time_limit, double temp_start, double temp_factor);

    void load_from_file(std::string);
    int get_matrix_size() const;

    atsp_genetic::organism genetic_algo(
        std::function<atsp_genetic::organism(atsp_genetic::organism&,
                                             atsp_genetic::organism&,
                                             Adjacency_Matrix&)>
            cross_fnc_,
        std::function<void(atsp_genetic::population&, Adjacency_Matrix&)>
            mutation_fnc_);

    bool is_loaded = false;

   private:
    Adjacency_Matrix matrix_;
};