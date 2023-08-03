#include <vector>
#include <string>
#include <iostream>
#include <utils.h>

void clear_terminal()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void check_go_back()
{
    char user_input;
    while (true)
    {
        std::cout << "\nPress q to go back to menu...\n";
        std::cin >> user_input;
        switch (user_input)
        {
        case 'q':
            return;
        default:
            std::cout << "\nInvalid input";
        }
    }
}

std::vector<std::string> parse(const std::string &line)
{
    // each text between ","
    std::vector<std::string> tokens;
    std::string temp_line;

    for (unsigned int i = 0; i < line.size(); i++)
    {
        if (line[i] == ',')
        {
            tokens.push_back(temp_line);
            temp_line.clear();
            continue;
        }

        temp_line += line[i];
    }

    tokens.push_back(temp_line);
    return tokens;
}