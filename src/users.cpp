#include <iostream>
#include <fstream>
#include <string>
#include <users.h>

user::user(std::string name, std::string username, std::string password, std::string email, std::string user_type)
{
    set_name(name);
    set_username(username);
    set_password(password);
    set_email(email);
    set_user_type(user_type);
}

user::user() : name(""), username(""), password(""), email(""), user_type(""){};

void user::save_to_file()
{
    std::fstream users_file;

    users_file.open("users.txt", std::ios::app);
    if (users_file.is_open())
    {
        users_file << username << "," << name << "," << password << "," << email << "," << user_type << std::endl;
        users_file.close();
    }
    else
    {
        std::cout << "\nError: Unable to open the file for savin the user information.";
    }
}

// setters

void user::set_name(std::string name)
{
    this->name = name;
}
void user::set_username(std::string username)
{
    this->username = username;
}
void user::set_password(std::string password)
{
    this->password = password;
}
void user::set_email(std::string email)
{
    this->email = email;
}

void user::set_user_type(std::string user_type)
{
    this->user_type = user_type;
}

// getters

std::string user::get_name() const
{
    return name;
}
std::string user::get_username() const
{
    return username;
}
std::string user::get_password() const
{
    return password;
}
std::string user::get_email() const
{
    return email;
}

std::string user::get_user_type() const
{
    return user_type;
}

regular_user::regular_user(std::string name, std::string username, std::string password, std::string email) : user(name, username, password, email, "user") // Call the base class constructor using member initializer list. Adds "user", so that when when admins create a new "user" object, they're a regular_user object.
{
    std::string issued_books_filename = username + "_issued_books.txt";

    issued_books.open(issued_books_filename, std::fstream::out | std::fstream::app);
    if (!issued_books.is_open())
    {
        std::cerr << "Error creating/opening file: " << issued_books_filename << std::endl;
    }
    issued_books.close();

    // Create book_history file for regular_user
    std::string book_history_filename = username + "_book_history.txt";

    book_history.open(book_history_filename, std::ios::out | std::ios::app);
    if (!book_history.is_open())
    {
        std::cerr << "Error creating/opening file: " << book_history_filename << std::endl;
    }
    book_history.close();
}

admin::admin(std::string name, std::string username, std::string password, std::string email)
    : user(name, username, password, email, "admin") // here, we redirect users created with type "admin"
{
}

// end of class definitions
