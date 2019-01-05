#pragma once

#include <string>

#include "adjacency_matrix.hpp"
#include "path.hpp"

class tsp
{
   public:
    double time_limit_;
    double temp_factor_;

    tsp()  = default;
    ~tsp() = default;

    tsp(const tsp&) = default;
    tsp(tsp&&)      = default;

    tsp& operator=(const tsp&) = default;
    tsp& operator=(tsp&&) = default;

    void load_from_file(std::string);
    bool is_loaded = false;

   private:
    Adjacency_Matrix matrix_;
};