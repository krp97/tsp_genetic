#include "../include/file_handler.hpp"

File_Handler::File_Handler(Adjacency_Matrix& matrix, std::string filepath)
    : matrix_ {matrix}, filepath_ {filepath}
{
}

bool File_Handler::run()
{
    std::fstream file;
    file.exceptions(std::fstream::failbit | std::fstream::badbit);
    try
    {
        file.open(filepath_);
        matrix_.load_from_file(file);
    } catch (const std::ios_base::failure&)
    {
        error_ = "Blad otwierania pliku.";
        return false;
    } catch (const std::invalid_argument&)
    {
        error_ = "Blad wczytywania danych z pliku.";
        return false;
    }
    return true;
}

std::string File_Handler::what() const { return error_; }