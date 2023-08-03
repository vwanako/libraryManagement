// libraries used
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unistd.h>

// header files used
#include <users.h>
#include <utils.h>
#include <book.h>

extern std::fstream users_file;
extern std::fstream books_file;

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
    std::fstream books_file;

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
    std::fstream users_file;

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

/*! \fn check_title_availability(const std::string &title)

The main use of this function is to stop users from creating duplicate book titles.
*/
bool check_title_availability(const std::string &title)
{
    std::fstream books_file;

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

void create_book()
{
    std::string temp_title, temp_author, temp_genre;
    float temp_price;

    std::cout << "New book menu.\nTitle: ";
    std::cin.ignore();
    getline(std::cin, temp_title);

    while (!check_title_availability(temp_title))
    {
        std::cout << "The book '" << temp_title << "' already exists. Please try again or press 'q' to finalize book creation process.\n";
        getline(std::cin, temp_title);
        if (temp_title == "q")
        {
            std::cout << "\nBook creation process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

    std::cout << "Author: ";
    getline(std::cin, temp_author);
    std::cout << "Genre: ";
    getline(std::cin, temp_genre);
    std::cout << "Price: ";
    std::cin >> temp_price;

    book new_book(temp_title, temp_author, temp_genre, temp_price);
    new_book.save_to_file();

    std::cout << "\nNew book being created";
    for (int i = 0; i < 3; i++)
    {
        sleep(1);
        std::cout << ".";
        // this makes "New user book created..." appear on the console with a one second delay for each "."
    }

    sleep(1);
    std::cout << "\nNew book has been sucessfully created!" << std::endl;

    // waits for user input before finalizing function (explanaition in function declaration)
    check_go_back();
}

void create_user()
{
    // we will create and store temporary varibles for each attribute our constructor asks for.

    std::string temp_name, temp_username, temp_password, temp_email, temp_user_type;

    std::cout << "New user menu.\nName: ";
    std::cin.ignore();
    getline(std::cin, temp_name);
    std::cout << "Username: ";
    getline(std::cin, temp_username);

    while (!check_username_availability(temp_username))
    {
        std::cout << "The username '" << temp_username << "' already exists. Please try again or press 'q' to finalize user creation process.\n";
        getline(std::cin, temp_username);
        if (temp_username == "q")
        {
            std::cout << "\nUser creation process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

    std::cout << "Password: ";
    getline(std::cin, temp_password);
    std::cout << "Email: ";
    getline(std::cin, temp_email);

    // the user type variable can only be two things: 'admin' or 'user'. we will use this loop to validate the input, making sure to only accept those values.
    while (true)
    {
        std::cout << "\nUser type [user/admin]: " << std::endl;
        std::cin >> temp_user_type;

        // convert the input to lowercase to make the validation case-insensitive
        transform(temp_user_type.begin(), temp_user_type.end(), temp_user_type.begin(), ::tolower);

        if (temp_user_type == "user" || temp_user_type == "admin")
        {
            break;
            // leaves the loop if appropriate input is received.
        }
        else
        {
            std::cout << "\nInvalid user type. Please enter 'user' or 'admin'." << std::endl;
        }
    }

    if (temp_user_type == "user")
    {
        regular_user new_user(temp_name, temp_username, temp_password, temp_email);
        new_user.save_to_file();
    }
    else // since the user type has already been validated, if it's not "user", it has to be "admin", so we don't need an "else if" condition, a simple "else" will be fine.
    {
        admin new_admin(temp_name, temp_username, temp_password, temp_email);
        new_admin.save_to_file();
    }

    std::cout << "\nNew user being created";
    for (int i = 0; i < 3; i++)
    {
        sleep(1);
        std::cout << ".";
        // this makes "New user being created..." appear on the console with a one second delay for each "."
    }

    sleep(1);
    std::cout << "\nNew user has been sucessfully created!" << std::endl;

    // waits for user input before finalizing function (explanaition in function declaration)
    check_go_back();
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

void issue_book()
{
    std::cout << "Available books:\n";
    print_available_books();
    // receives input of who is getting the book from their username.
    std::string username;
    std::cout << "\nEnter the borrower's username: ";
    std::cin.ignore();
    getline(std::cin, username);

    // the user's book history is formatted as username_bookHistory.txt, here, we set the file
    std::string history_filename = "res/" + username + "_book_history.txt";
    std::string issued_filename = "res/" + username + "_issued_books.txt";
    std::fstream book_history, books_file, issued_books;

    // since info will be used to manipulate three separate files, we will declare and receive it outside the conditions, so we don't need to ask for input twice.
    std::string title, issue_date, return_date;
    std::cout << "\nEnter book title: ";
    getline(std::cin, title);

    while (!check_book_availability(title))
    {
        std::cout << "\nThe book '" << title << "' is not currently available or doesn't exist. Please try again or press 'q' to finalize issuing process.\n";
        getline(std::cin, title);
        if (title == "q")
        {
            std::cout << "\nIssue process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

    std::cout << "\nEnter issue date: ";
    getline(std::cin, issue_date);
    std::cout << "\nEnter return date: ";
    getline(std::cin, return_date);

    // opens the user's book history file
    book_history.open(history_filename, std::ios::app);
    if (book_history.is_open())
    {
        // inserts the formated information into the file and closes it
        book_history << title << "," << issue_date << "," << return_date << std::endl;
        book_history.close();
    }
    else
    {
        std::cerr << "Error opening file: " << history_filename << std::endl;
    }

    // does the same to the issued_books (the books the person issued and didn't return yet) as the book_history.
    issued_books.open(issued_filename, std::ios::app);
    if (issued_books.is_open())
    {
        // inserts the formated information into the file and closes it
        issued_books << title << "," << issue_date << "," << return_date << std::endl;
        issued_books.close();
    }
    else
    {
        std::cerr << "Error opening file: " << issued_filename << std::endl;
    }

    // creates a std::vector of strings, we will use it to store all the information in the file, along with the updated line and
    std::vector<std::string> updated_lines;

    // opens the books file (where the information of the library collection is stored) in read mode
    books_file.open("res/books.txt", std::ios::in);
    if (books_file.is_open())
    {
        // sets the pointer to the beginning of the file
        books_file.seekg(0);

        // creates a line variable, we will use it to read each line of the file until we find the book being issued
        std::string line;
        while (getline(books_file, line))
        {
            // calls the parse function to split each information into elements of std::vector tokens
            std::vector<std::string> tokens = parse(line);
            // if tokens isn't empty and the element [0] is the title of the issued book
            if (!tokens.empty() && tokens[0] == title)
            {
                // changes the "is available" info to unavailable.
                tokens[4] = "unavailable";
                // creates a new line with the updated availability status without altering the other information
                std::string updated_line = tokens[0] + "," + tokens[1] + "," + tokens[2] + "," + tokens[3] + "," + tokens[4];
                // stores the new line in the updated lines std::vector
                updated_lines.push_back(updated_line);
            }
            // if the line isn't the book we're looking for, it will be stored in the updated lines std::vector without changes
            else
            {
                updated_lines.push_back(line);
            }
        }
        // closes the file
        books_file.close();
    }
    // handling errors when opening the file fails
    else
    {
        std::cout << "Error opening books file.";
    }

    // opens the file again in write mode
    books_file.open("res/books.txt", std::ios::out | std::ios::trunc);
    // overwrites the file using each element of the updated lines std::vector as a line in the file.
    for (const std::string &updated_line : updated_lines)
    {
        books_file << updated_line << std::endl;
    }

    // close the file
    books_file.close();

    // waits for user input before finalizing function (explanaition in function declaration)
    check_go_back();
}

void return_book()
{
    std::string username;
    std::cout << "\nEnter the borrower's username: ";
    std::cin.ignore();
    getline(std::cin, username);

    // prints the user's book history to make it easier to return books.
    std::cout << username << "'s book history: \n";
    print_book_history(username);

    std::string issued_filename = "res/" + username + "_issued_books.txt";
    std::fstream issued_books;

    std::string title;
    std::cout << "\nEnter book title: ";
    getline(std::cin, title);
    while (!check_in_issued(title, username))
    {
        std::cout << "\nThe book '" << title << "' is not in " << username << "'s issued books file or doesn't exist. Please try again or press 'q' to finalize the returning process.\n";

        getline(std::cin, title);
        if (title == "q")
        {
            std::cout << "\nReturning process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

    // removes the title from the currently issued books list. functions similar to the book history manipulation.
    std::vector<std::string> updated_issue_lines;
    issued_books.open(issued_filename, std::ios::in);
    if (issued_books.is_open())
    {
        issued_books.seekg(0);

        std::string line;
        while (getline(issued_books, line))
        {
            std::vector<std::string> tokens = parse(line);

            if (tokens[0] != title)
            {
                updated_issue_lines.push_back(line);
            }
        }
        issued_books.close();
    }
    else
    {
        std::cerr << "\nError opening file: " << issued_filename << std::endl;
    }

    issued_books.open(issued_filename, std::ios::out | std::ios::trunc);

    for (const std::string &updated_issue_line : updated_issue_lines)
    {
        issued_books << updated_issue_line << std::endl;
    }

    issued_books.close();

    std::vector<std::string> updated_lines;

    // explanation is the same as the issue book function, except that it changes the token from "false" to "true"
    books_file.open("res/books.txt", std::ios::in);
    if (books_file.is_open())
    {
        books_file.seekg(0);

        std::string line;
        while (getline(books_file, line))
        {
            std::vector<std::string> tokens = parse(line);

            if (!tokens.empty() && tokens[0] == title)
            {
                // changes the "is available" info to available.
                tokens[4] = "available";
                std::string updated_line = tokens[0] + "," + tokens[1] + "," + tokens[2] + "," + tokens[3] + "," + tokens[4];
                updated_lines.push_back(updated_line);
            }
            else
            {
                updated_lines.push_back(line);
            }
        }
        // closes the file
        books_file.close();
    }
    // handling errors when opening the file fails
    else
    {
        std::cout << "Error opening books file.";
    }

    // opens the file again in write mode
    books_file.open("res/books.txt", std::ios::out | std::ios::trunc);
    // overwrites the file using each element of the updated lines std::vector as a line in the file.
    for (const std::string &updated_line : updated_lines)
    {
        books_file << updated_line << std::endl;
    }

    // close the file
    books_file.close();

    // waits for user input before finalizing function (explanaition in function declaration)
    check_go_back();
}

user login()
{
    std::string username, password, line;

    std::cout << "\nEnter username: ";
    std::cin >> username;
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
        std::cout << "Enter username: ";
        getline(std::cin, username);
        std::cout << "Enter password: ";
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

            std::cout << "\nEnter action:\n1: View library collection\n2: View users\n3: Issue a book\n4: Return a book\n5: Create new user\n6: Create new book\nq: log out\n";
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
                create_book();
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

int main()
{

    char user_input;
    user logged_in_user;

    while (true)
    {
        clear_terminal();
        std::cout << "\nEnter action:\n1: Login\nq: quit program\n";
        std::cin >> user_input;
        switch (user_input)
        {
        case '1':
            logged_in_user = login();
            user_menu(logged_in_user);
            break;
        case 'q':
            return 0;
        default:
            std::cout << "\nInvalid input. Please try again.";
            break;
        }
    }

    return 0;
}