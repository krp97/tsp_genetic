#include "../include/menu_handler.hpp"
#include "../include/file_converter.hpp"

#include <iostream>
#include <string>

void Menu::run(const std::vector<std::string>& subtitles,
               const std::string title)
{
    handle_input(subtitles, title);
}

void Menu::draw_menu(const std::vector<std::string>& subtitles,
                     const std::string title, bool draw_params) const
{
    clear_term();
    int line_len {longest_subtitle(subtitles)};
    int total_line_len = line_len + format_chars;

    draw_title(title, total_line_len);
    draw_body(subtitles, line_len);
    std::cout << std::string(total_line_len, '-') << std::endl;
    if (draw_params)
        draw_parameters(total_line_len, subtitles.size() + 2);
}

void Menu::draw_parameters(int line_len, int lines) const
{
    gotoxy(line_len + 1, 2);
    std::cout << " >> " << tsp_api.time_limit_;
    gotoxy(line_len + 1, 3);
    std::cout << " >> " << tsp_api.cross_prob_;
    gotoxy(line_len + 1, 4);
    std::cout << " >> " << tsp_api.mutation_prob_;
    gotoxy(line_len + 1, 5);
    if (tsp_api.is_loaded)
        std::cout << " Size >> " << tsp_api.get_matrix_size();
    gotoxy(0, lines + 1);
}

void Menu::gotoxy(int x, int y) const { printf("%c[%d;%df", 0x1B, y, x); }

void Menu::clear_term() const
{
#ifdef __linux__
    system("clear");
#elif _WIN32
    system("CLS");
#endif
}

int Menu::longest_subtitle(const std::vector<std::string>& subtitles) const
{
    auto max_el = std::max_element(subtitles.begin(), subtitles.end(),
                                   [&](std::string lhs, std::string rhs) {
                                       return lhs.size() < rhs.size();
                                   });
    return (*max_el).size();
}

void Menu::draw_title(const std::string& title, const unsigned line_len) const
{
    unsigned dash_count {line_len - (unsigned)title.size() - 2};
    auto dashes {std::string((int)dash_count / 2, '-')};
    auto title_string {std::string(dashes + " " + title + " " + dashes)};

    if (dash_count % 2 == 0)
        std::cout << title_string << std::endl;
    else
        std::cout << title_string << "-" << std::endl;
}

void Menu::draw_body(const std::vector<std::string>& subtitles,
                     const unsigned max_line) const
{
    for (size_t i {1}; i <= subtitles.size(); ++i)
        std::cout << align_line(subtitles[i - 1], i, max_line);
}

std::string Menu::align_line(const std::string& line, const unsigned line_no,
                             const unsigned max_len) const
{
    return std::string("| " + std::to_string(line_no) + ") " + line +
                       std::string(max_len - line.size(), ' ') + " |\n");
}

void Menu::handle_input(const std::vector<std::string>& subtitles,
                        std::string title)
{
    int choice = 4;
    bool exit  = false;
    while (!exit)
    {
        draw_menu(subtitles, title, true);
        std::cout << " Your choice >> ";
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                secure_read_double(tsp_api.time_limit_);
                break;
            }
            case 2:
            {
                secure_read_double(tsp_api.cross_prob_);
                break;
            }
            case 3:
            {
                secure_read_double(tsp_api.mutation_prob_);
                break;
            }
            case 4:
            {
                load_from_file(get_filename());
                break;
            }
            case 5:
            {
                if (tsp_api.is_loaded)
                    algorithm_menu();
                else
                {
                    std::cout << "\n Error: No graph data.";
                    wait_for_reaction();
                }
                break;
            }
            case 6:
            {
                convert_file(get_filename());
                break;
            }
            default:
            {
                exit = true;
                break;
            }
        }
    }
}

void Menu::convert_file(const std::string& filename)
{
    auto fc = utils::file_converter();
    fc.convert(filename, "tsp");
}

void Menu::algorithm_menu()
{
    int choice                         = 4;
    bool exit                          = false;
    std::vector<std::string> subtitles = {"Order 1, Swap", "Uniform, Swap",
                                          "Order 1, Insertion",
                                          "Uniform, Insertion", "Previous"};
    while (!exit)
    {
        draw_menu(subtitles, "Algorithms", false);
        std::cout << " Your choice >> ";
        std::cin >> choice;
        switch (choice)
        {
            case 1:
            {
                clear_term();
                std::cout << tsp_api
                                 .genetic_algo(atsp_genetic::population::order1,
                                               atsp_genetic::population::swap)
                                 .to_string();
                wait_for_reaction();
                break;
            }
            case 2:
            {
                clear_term();
                std::cout << tsp_api
                                 .genetic_algo(
                                     atsp_genetic::population::uniform,
                                     atsp_genetic::population::swap)
                                 .to_string();
                wait_for_reaction();
                break;
            }
            case 3:
            {
                clear_term();
                std::cout << tsp_api
                                 .genetic_algo(
                                     atsp_genetic::population::order1,
                                     atsp_genetic::population::insertion)
                                 .to_string();
                wait_for_reaction();
                break;
            }
            case 4:
            {
                clear_term();
                std::cout << tsp_api
                                 .genetic_algo(
                                     atsp_genetic::population::uniform,
                                     atsp_genetic::population::insertion)
                                 .to_string();
                wait_for_reaction();
                break;
            }
            default:
            {
                exit = true;
                break;
            }
        }
    }
}

void Menu::load_from_file(const std::string& filename)
{
    try
    {
        tsp_api.load_from_file(filename);
    } catch (const std::invalid_argument& e)
    {
        std::cout << "\n Error >> " << e.what();
        wait_for_reaction();
    }
}

void Menu::wait_for_reaction()
{
    getchar();
    getchar();
}

std::string Menu::get_filename()
{
    std::string filename;
    std::cout << " Enter the path to a file >> ";
    std::cin >> filename;
    return filename;
}

double Menu::get_double()
{
    double amount;
    std::string input;
    std::cout << " Enter the amount >> ";
    std::cin >> input;
    amount = strtod(input.c_str(), nullptr);
    return amount;
}

void Menu::secure_read_double(double& amount)
{
    try
    {
        amount = get_double();
    } catch (const std::invalid_argument& e)
    {
        std::cout << "\n" << e.what();
    }
}