#pragma once

#include <string>

#include "adjacency_matrix.hpp"
#include "organism.hpp"

class atsp
{
   public:
    double time_limit_;
    double temp_factor_;

    atsp()  = default;
    ~atsp() = default;

    atsp(const atsp&) = default;
    atsp(atsp&&)      = default;

    atsp& operator=(const atsp&) = default;
    atsp& operator=(atsp&&) = default;

    void load_from_file(std::string);
    bool is_loaded = false;

   private:
    Adjacency_Matrix matrix_;
};