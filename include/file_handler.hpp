#pragma once

#include "../include/adjacency_matrix.hpp"

#include <fstream>
#include <string>

class File_Handler
{
   public:
    File_Handler() = delete;

    File_Handler(Adjacency_Matrix& matrix, std::string filepath);

    File_Handler& operator=(const File_Handler& rhs) = default;
    ~File_Handler()                                  = default;

    bool run();
    std::string what() const;

   private:
    Adjacency_Matrix& matrix_;
    std::string filepath_;
    std::string error_;
};