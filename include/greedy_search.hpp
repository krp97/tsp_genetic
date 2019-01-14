#pragma once
#include "adjacency_matrix.hpp"
#include "organism.hpp"

namespace atsp_genetic {

class greedy_search
{
   public:
    greedy_search() = delete;

    greedy_search(const greedy_search&) = default;
    ~greedy_search()                    = default;

    greedy_search(Adjacency_Matrix& matrix);

    organism run();

   private:
    Adjacency_Matrix& matrix_;
    void run(organism&, std::vector<bool>& visited);
    int get_minimum(std::vector<int>& row, std::vector<bool>& visited);
    bool all_visited(std::vector<bool>& visited);
};
}  // namespace atsp_genetic