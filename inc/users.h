#ifndef USERS_H
#define USERS_H

std::fstream users_file;

class user
{
protected:
    std::string name, username, password, email, filename, user_type;

public:
    // constructors

    user(std::string name, std::string username, std::string password, std::string email, std::string user_type);

    user() : name(""), username(""), password(""), email(""), user_type("");

    void save_to_file();

    // setters

    void set_name(string name);
    void set_username(string username);
    void set_password(string password);
    void set_email(string email);
    void set_user_type(string user_type);

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

    regular_user(std::string name, std::string username, std::string password, std::string email) : user(name, username, password, email, "user");
};

class admin : public user
{
public:
    // constructor
    admin(std::string name, std::string username, std::string password, std::string email) : user(name, username, password, email, "admin");
};

#endif // USERS_H
