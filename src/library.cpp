#include <iostream>
#include <fstream>
#include <unistd.h>
#include <algorithm>
#include <vector>
#include <cstdio>

#include <library.h>

extern std::fstream users_file;
extern std::fstream books_file;

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

void delete_user()
{
    std::string username;
    std::cout << "\nType the username you want to delete: ";
    std::cin >> username;

    std::string issued_filename = "res/" + username + "_issued_books.txt", history_filename = "res/" + username + "_book_history.txt";

    std::vector<std::string> updated_file;

    users_file.open("res/users.txt", std::ios::in);
    if (users_file.is_open())
    {
        std::string line;
        while (getline(users_file, line))
        {
            std::vector<std::string> tokens = parse(line);

            if (tokens[0] != username)
            {
                updated_file.push_back(line);
            }
        }
        users_file.close();
    }
    else
    {
        std::cerr << "\nError opening file." << std::endl;
    }

    users_file.open("res/users.txt", std::ios::out | std::ios::trunc);
    for (const std::string &updated_line : updated_file)
    {
        users_file << updated_line << std::endl;
    }

    std::remove(issued_filename.c_str());
    std::remove(history_filename.c_str());

    std::cout << "\nUser deleted sucessfully." << std::endl;
    sleep(2);
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

void delete_book()
{
    std::string title;
    std::cout << "\nType the book title you want to delete: ";
    std::cin >> title;

    std::vector<std::string> updated_file;

    books_file.open("res/books.txt", std::ios::in);
    if (books_file.is_open())
    {
        std::string line;
        while (getline(books_file, line))
        {
            std::vector<std::string> tokens = parse(line);
            if (tokens[0] != title)
            {
                updated_file.push_back(line);
            }
        }
        books_file.close();
    }
    else
    {
        std::cout << "\nError opening file." << std::endl;
    }

    books_file.open("res/books.txt", std::ios::out | std::ios::trunc);

    for (const std::string &updated_line : updated_file)
    {
        books_file << updated_line << std::endl;
    }
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

    while (!check_username_exists(username))
    {
        std::cout << "\nThe username " << username << " does not exist. Please try again or press q to finalize issuing process.\n";
        getline(std::cin, username);
        if (username == "q")
        {
            std::cout << "\nIssue process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

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