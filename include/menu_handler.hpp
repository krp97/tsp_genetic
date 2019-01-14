#pragma once

#include "adjacency_matrix.hpp"
#include "organism.hpp"
#include "population.hpp"
#include "timer.hpp"
#include "tsp.hpp"

#include <fstream>
#include <string>
#include <vector>

class Menu
{
   public:
    Menu()        = default;
    Menu& operator=(const Menu& rhs) = delete;

    ~Menu() = default;

    void run(const std::vector<std::string>& subtitles,
             const std::string title);

   private:
    const int format_chars = 7;  // = | 1) "..." |
    tsp tsp_api;

    void gotoxy(int x, int y) const;
    void draw_menu(const std::vector<std::string>& subtitles,
                   const std::string title, bool draw_params) const;
    void draw_title(const std::string& title, const unsigned max_line) const;
    void draw_body(const std::vector<std::string>& subtitles,
                   const unsigned max_line) const;
    std::string align_line(const std::string& line, const unsigned line_no,
                           const unsigned max_len) const;
    void draw_parameters(int line_len, int lines) const;
    void clear_term() const;
    int longest_subtitle(const std::vector<std::string>& subtitles) const;

    void handle_input(const std::vector<std::string>& subtitles,
                      std::string title);
    void draw_all_files();
    std::string get_filename();
    double get_double();
    void secure_read_double(double&);
    void convert_file(const std::string& filename);
    void load_from_file(const std::string& filename);
    void wait_for_reaction();

    void algorithm_menu();
};