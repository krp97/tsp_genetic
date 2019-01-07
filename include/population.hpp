#include <algorithm>
#include <vector>
#include "organism.hpp"

namespace atsp_genetic {

class population
{
   public:
    population() = default;
    population(size_t amount);
    population(const population& rhs) = default;
    population& operator=(const population& rhs) = default;
    population(population&& rhs) noexcept        = default;
    population& operator=(population&& rhs) noexcept = default;
    ~population()                                    = default;

   private:
    std::vector<organism> population_;
    size_t entry_size_;
};
}  // namespace atsp_genetic