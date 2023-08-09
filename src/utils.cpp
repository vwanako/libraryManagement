#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <unistd.h>
#include <utils.h>
#include <limits>

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

bool validate_string(const std::string &word)
{
    for (int i = 0; i < word.length(); i++)
    {
        if (word[i] == ',')
        {
            return false;
        }
    }
    return true;
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

/*! \fn print_book_history(const std::string &user)
    @brief Prints the book history for a specific user.
    @param user the username whose history we'll print out
*/
void print_book_history(const std::string &user)
{
    std::string filename = "res/" + user + "_book_history.txt";
    std::fstream book_history;

    std::cout << "TITLE | ISSUE DATE | RETURN DATE\n";

    book_history.open(filename, std::ios::in);
    if (book_history.is_open())
    {
        std::string line;
        while (getline(book_history, line))
        {
            std::cout << line << std::endl;
        }
        book_history.close();
    }
    else
    {
        std::cout << "\nError opening book history file.";
    }
}

/*! \fn print_available_books()
    @brief Prints the title, author and genre of the books set as "available" in the "res/books.txt" file.
*/
void print_available_books()
{
    std::fstream books_file;
    std::vector<std::string> available_books;

    books_file.open("res/books.txt", std::ios::in);
    if (books_file.is_open())
    {
        std::string line;
        while (getline(books_file, line))
        {
            std::vector<std::string> tokens = parse(line);
            if (tokens[4] == "available")
            {
                std::string basic_info = "title: " + tokens[0] + " | author: " + tokens[1] + " | genre: " + tokens[2];
                available_books.push_back(basic_info);
            }
        }
        books_file.close();
    }
    else
    {
        std::cout << "\nError opening books file.";
    }

    for (const std::string &line : available_books)
    {
        std::cout << line << std::endl;
    }
}

/*! \fn check_book_availability(const std::string &title)
    @brief Checks if the book requested is available. Returns true if it is and false otherwise.
    The main use of this function is to avoid that a book will be issued when it's not available. It will return false if the book is set as unavailable, if the book can't be found in the database or if there's an error opening the file.
    @param title The title of the book that will be searched for in the "res/books.txt" file.
*/
bool check_book_availability(const std::string &title)
{
    books_file.open("res/books.txt", std::ios::in);
    if (books_file.is_open())
    {
        std::string line;
        while (getline(books_file, line))
        {
            std::vector<std::string> tokens = parse(line);
            if (tokens[0] == title && tokens[4] == "available")
            {
                books_file.close();
                return true;
            }
        }
        books_file.close();
        return false;
    }
    else
    {
        std::cout << "\nError opening books file.";
        return false;
    }
}

/*! \fn check_username_availability(const std::string &username)
    @brief Checks if a requested username is available or not. Returns true if the username doesn't already exist in the "res/users.txt" file and false otherwise.
    The main use of this function is to stop users from creating duplicate usernames, since many functions inside of the program depend on having unique usernames. It will return false if the username already exists or if there was an error opening the "res/users.txt" file.
    @param username The username that will be searched for in the "res/users.txt" file.
 */
bool check_username_availability(const std::string &username)
{
    users_file.open("res/users.txt", std::ios::in);
    if (users_file.is_open())
    {
        std::string line;
        while (getline(users_file, line))
        {
            std::vector<std::string> tokens = parse(line);
            // if the program finds the username in the users file, availability is false.
            if (tokens[0] == username)
            {
                users_file.close();
                return false;
            }
        }
        users_file.close();
        return true; // if the program doesnt't find the username, availability is true
    }
    else
    {
        std::cout << "\nError opening users file.";
        return false;
    }
}

bool check_username_exists(const std::string &username)
{
    users_file.open("res/users.txt", std::ios::in);
    if (users_file.is_open())
    {
        std::string line;
        while (getline(users_file, line))
        {
            std::vector<std::string> tokens = parse(line);
            if (tokens[0] == username)
            {
                users_file.close();
                return true;
            }
        }
        users_file.close();
        return false;
    }
    else
    {
        std::cout << "\nError opening users file.";
        return false;
    }
}

/*! \fn check_title_availability(const std::string &title)

The main use of this function is to stop users from creating duplicate book titles.
*/
bool check_title_availability(const std::string &title)
{
    books_file.open("res/books.txt", std::ios::in);
    if (books_file.is_open())
    {
        std::string line;
        while (getline(books_file, line))
        {
            std::vector<std::string> tokens = parse(line);
            // if the program finds the title in the books file, availability is false.
            if (tokens[0] == title)
            {
                books_file.close();
                return false;
            }
        }
        books_file.close();
        return true; // if the program doesnt find the title, availability is true
    }
    else
    {
        std::cout << "\nError opening books file.";
        return false;
    }
}

/*! \fn check_in_issued(const std::string &title, const std::string &user)
    @brief Checks if the given title is int the user's issued books list.
    Looks for the specific title in the user's issued books list, that is, the books they haven't returned yet. Stops users from returning a book that isn't in their file.
    @param title The title of the book being checked.
    @param user The user whose list is read.
 */
bool check_in_issued(const std::string &title, const std::string &user)
{
    std::fstream issued_books;
    std::string filename = "res/" + user + "_issued_books.txt";

    issued_books.open(filename, std::ios::in);
    if (issued_books.is_open())
    {
        std::string line;
        while (getline(issued_books, line))
        {
            std::vector<std::string> tokens = parse(line);
            if (tokens[0] == title)
            {
                issued_books.close();
                return true;
            }
        }
        issued_books.close();
        return false;
    }
    else
    {
        std::cout << "\nError opening issued books file.";
        return false;
    }
}

void print_issued_books(const std::string &user)
{
    std::string filename = "res/" + user + "_issued_books.txt";
    std::fstream issued_books;

    // shows file formatting
    std::cout << "TITLE | ISSUE DATE | RETURN DATE\n";

    issued_books.open(filename, std::ios::in);
    if (issued_books.is_open())
    {
        std::string line;
        while (getline(issued_books, line))
        {
            std::cout << line << std::endl;
        }
        issued_books.close();
    }
    else
    {
        std::cout << "\nError opening issued books file.";
    }
}

struct result
{
    user user;
    bool error;
};

result authenticate(const std::string &username, const std::string &password)
{
    result result;
    users_file.open("res/users.txt", std::ios::in);
    if (users_file.is_open())
    {
        std::string line;
        while (getline(users_file, line))
        {
            std::vector<std::string> tokens = parse(line);
            if (tokens[0] == username && tokens[2] == password)
            {
                users_file.close();
                result.user.set_username(tokens[0]);
                result.user.set_name(tokens[1]);
                result.user.set_password(tokens[2]);
                result.user.set_email(tokens[3]);
                result.user.set_user_type(tokens[4]);
                result.error = false;

                return result;
            }
        }
    }
    else
    {
        std::cout << "Error opening users file";
    }
    result.error = true;
    return result;
}

user login()
{
    std::string username, password, line;

    std::cout << "\nEnter username: ";
    std::cin >> username;

    while (!check_username_exists(username))
    {
        std::cout << "\nThe username " << username << " does not exist. Please try again or press q to finalize login process.\n";
        std::cin >> username;

        if (username == "q")
        {
            std::cout << "\nLogin process finalized.";
            sleep(2);
            return {};
        }
    }

    std::cout << "\nEnter password: ";
    std::cin >> password;

    while (true)
    {
        auto result = authenticate(username, password);
        if (!result.error)
        {
            std::cout << "Login sucessfull." << std::endl;
            return result.user;
        }
        std::cout << "Username or password incorrect. Try again.";

        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nEnter username: ";
        getline(std::cin, username);
        std::cout << "\nEnter password: ";
        getline(std::cin, password);
    }
}

void user_menu(const user &user)
{
    std::string usertype = user.get_user_type();
    char user_input;

    if (usertype == "user")
    {
        while (true)
        {
            clear_terminal();

            std::cout << "\nEnter action:\n1: View library collection\n2: View my currently issued books\n3: View my book history\nq: log out\n";
            std::cin >> user_input;
            switch (user_input)
            {
            case '1':
                print_books();
                break;
            case '2':
                print_issued_books(user.get_username());
                check_go_back();
                break;
            case '3':
                print_book_history(user.get_username());
                check_go_back();
                break;
            case 'q':
                return;
            default:
                std::cout << "\nInvalid input. Please try again.";
                sleep(2);
                break;
            }
        }
    }
    else if (usertype == "admin")
    {
        while (true)
        {
            clear_terminal();

            std::cout << "\nEnter action:\n1: View library collection\n2: View users\n3: Issue a book\n4: Return a book\n5: Create new user\n6: Delete existing user\n7: Create new book\n8: Delete existing book\nq: log out\n";
            std::cin >> user_input;

            switch (user_input)
            {
            case '1':
                print_books();
                break;
            case '2':
                print_users();
                break;
            case '3':
                issue_book();
                break;
            case '4':
                return_book();
                break;
            case '5':
                create_user();
                break;
            case '6':
                delete_user();
                break;
            case '7':
                create_book();
                break;
            case '8':
                delete_book();
                break;
            case 'q':
                return;
            default:
                std::cout << "\nInvalid input. Please try again.";
                sleep(2);
                break;
            }
        }
    }
}

void clear_input_buffer()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}