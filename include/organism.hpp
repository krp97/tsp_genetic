#pragma once
#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include "adjacency_matrix.hpp"

namespace atsp_genetic {
class organism
{
   public:
    organism();
    organism(Adjacency_Matrix&);
    organism(std::vector<int> path, Adjacency_Matrix& matrix);
    organism(const organism& rhs) = default;
    organism& operator=(const organism& rhs) = default;
    organism(organism&& rhs) noexcept        = default;
    organism& operator=(organism&& rhs) noexcept = default;
    ~organism()                                  = default;

    int& operator[](int index) { return path_[index]; };
    bool operator<(const organism& rhs) { return this->cost_ < rhs.cost_; };
    bool operator>(const organism& rhs) { return !(*this < rhs); };
    bool operator==(const organism& rhs) { return path_ == rhs.path_; };
    bool operator!=(const organism& rhs) { return !(*this == rhs); }

    std::vector<int>::iterator begin() { return path_.begin(); };
    std::vector<int>::iterator end() { return path_.end(); };

    std::string to_string() const;
    std::vector<int>& get_organism() { return path_; };
    int get_cost() const { return cost_; };
    size_t size() const { return path_.size(); };
    std::vector<int> get_range(int a, int b) const;

    void erase(size_t index);
    void insert(size_t index, int value);
    void recalc_cost(Adjacency_Matrix& matrix);

   protected:
    std::vector<int> path_;
    int cost_;

    std::string get_path_str() const;
    std::string get_cost_str() const;
};
}  // namespace atsp_genetic