#pragma once
#include <algorithm>
#include <functional>
#include <numeric>
#include <random>
#include <string>
#include <vector>
#include "adjacency_matrix.hpp"

class organism
{
   public:
    organism();
    organism(Adjacency_Matrix&, std::random_device& dev);
    organism(std::vector<int> path, Adjacency_Matrix& matrix);
    organism(const organism& rhs) = default;
    organism& operator=(const organism& rhs) = default;
    organism(organism&& rhs) noexcept        = default;
    organism& operator=(organism&& rhs) noexcept = default;
    virtual ~organism()                          = default;

    int& operator[](int index) { return organism_[index]; };
    bool operator<(const organism& rhs) { return this->cost_ < rhs.cost_; };
    bool operator>(const organism& rhs) { return !(*this < rhs); };
    bool operator==(const organism& rhs) { return organism_ == rhs.organism_; };
    bool operator!=(const organism& rhs) { return !(*this == rhs); }

    std::vector<int>::iterator begin() { return organism_.begin(); };
    std::vector<int>::iterator end() { return organism_.end(); };

    std::string to_string() const;
    std::vector<int>& get_organism() { return organism_; };
    int get_cost() const { return cost_; };
    size_t size() const { return organism_.size(); };
    std::vector<int> get_range(int a, int b) const;

    void erase(size_t index);
    void insert(size_t index, int value);
    void recalc_cost(Adjacency_Matrix& matrix);

   protected:
    std::vector<int> organism_;
    int cost_;

    std::string get_organism_str() const;
    std::string get_cost_str() const;
};