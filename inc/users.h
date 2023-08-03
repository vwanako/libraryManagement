#ifndef USERS_H
#define USERS_H

std::fstream users_file;

class user
{
protected:
    std::string name, username, password, email, filename, user_type;

public:
    // constructors

    user(std::string name, std::string username, std::string password, std::string email, std::string user_type)
    {
        set_name(name);
        set_username(username);
        set_password(password);
        set_email(email);
        set_user_type(user_type);
    }

    user() : name(""), username(""), password(""), email(""), user_type(""){};

    void save_to_file();

    // setters

    void set_name(std::string name);
    void set_username(std::string username);
    void set_password(std::string password);
    void set_email(std::string email);
    void set_user_type(std::string user_type);

    // getters

    std::string get_name() const;
    std::string get_username() const;
    std::string get_password() const;
    std::string get_email() const;
    std::string get_user_type() const;
};

class regular_user : public user
{
public:
    std::fstream issued_books;
    std::fstream book_history;

    regular_user(std::string name, std::string username, std::string password, std::string email) : user(name, username, password, email, "user")
    {
        std::string book_history_filename = username + "_book_history.txt";
        std::string issued_books_filename = username + "_issued_books.txt";
    }
};

class admin : public user
{
public:
    // constructor
    admin(std::string name, std::string username, std::string password, std::string email) : user(name, username, password, email, "admin"){};
};

#endif // USERS_H
