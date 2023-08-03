#include <vector>
#include <string>
#include <iostream>
#include <utils.h>

extern std::fstream users_file;
extern std::fstream books_file;

/*! \fn clear_terminal()
    @brief Clears terminal to improve readability.
    Used inside of the menus. Clears the terminal after executing a function inside of the switch case options.
 */
void clear_terminal()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*! \fn check_go_back()
    @brief Used with other functions so that the terminal is not instantly cleared when a function finishes executing.
    Inside the menu loops, the terminal is cleared automatically when a certain action finishes executing. This function is used to avoid that it clears before the user is done reading the result of another function.
 */
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

/*! \fn parse(const std::string &line)
    @brief Used for splitting the info in txt files' lines into vector elements.
    This function reads the lines in a txt file and splits them into separate elements of a vector every time it finds a ",". With it, we can get the information from the txt databases and use them in the code in different ways, depending on what info we're looking for.
    @param line The line it's currently reading and splitting into the vector. Usually, this is inside of a while(getline(filename, line)) loop, so it's the line of the current loop iteration.
 */
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

/*! \fn print_users()
    @brief Prints all the users in the "res/users.txt" file and their information
*/
void print_users()
{
    std::cout << "USERNAME | NAME | PASSWORD | EMAIL | USER TYPE\n";
    users_file.open("res/users.txt", std::ios::in);
    if (users_file.is_open())
    {
        std::string line;
        while (getline(users_file, line))
        {
            std::cout << line << std::endl;
        }
        users_file.close();
    }
    else
    {
        std::cout << "\nError opening users file.";
    }
    check_go_back();
}

/*! \fn print_books()
    @brief Prints all the books in the "res/books.txt" file and their information
*/
void print_books()
{
    std::cout << "TITLE | AUTHOR | GENRE | PRICE | AVAILABILITY STATUS\n";

    books_file.open("res/books.txt", std::ios::in);
    if (books_file.is_open())
    {
        std::string line;
        while (getline(books_file, line))
        {
            std::cout << line << std::endl;
        }
        books_file.close();
    }
    else
    {
        std::cout << "\nError opening book collection file.";
    }
    check_go_back();
}
