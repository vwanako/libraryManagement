#include <iostream>
#include <fstream>
#include <string>
#include "Book.h"
using namespace std;

fstream usersFile;

class User
{
protected:
    string name, username, password, email, filename, userType;

public:
    // constructors

    User(string name, string username, string password, string email, string userType)
    {
        setName(name);
        setUsername(username);
        setPassword(password);
        setEmail(email);
        filename = username + "_bookHistory.txt";

        setUserType(userType);
    }

    User() : name(""), username(""), password(""), email(""), userType("")
    {
    }

    void saveToFile()
    {
        fstream usersFile;

        usersFile.open("users.txt", ios::app);
        if (usersFile.is_open())
        {
            usersFile << username << "," << name << "," << password << "," << email << "," << userType << endl;
            usersFile.close();
        }
        else
        {
            cout << "\nError: Unable to open the file for savin the user information.";
        }
    }

    // setters

    void setName(string name)
    {
        this->name = name;
    }
    void setUsername(string username)
    {
        this->username = username;
    }
    void setPassword(string password)
    {
        this->password = password;
    }
    void setEmail(string email)
    {
        this->email = email;
    }

    void setUserType(string userType)
    {
        this->userType = userType;
    }

    // getters

    string getName() const
    {
        return name;
    }
    string getUsername() const
    {
        return username;
    }
    string getPassword() const
    {
        return password;
    }
    string getEmail() const
    {
        return email;
    }

    string getUserType() const
    {
        return userType;
    }
};

class regularUser : public User
{
public:
    fstream issuedBooks;
    fstream bookHistory;

    regularUser(string name, string username, string password, string email) : User(name, username, password, email, "user") // Call the base class constructor using member initializer list. Adds "user", so that when when admins create a new "user" object, they're a regularUser object.
    {
        string issuedBooksFilename = username + "_issuedBooks.txt";

        issuedBooks.open(issuedBooksFilename, std::fstream::out | std::fstream::app);
        if (!issuedBooks.is_open())
        {
            std::cerr << "Error creating/Opening file: " << issuedBooksFilename << std::endl;
        }
        issuedBooks.close();

        // Create bookHistory file for regularUser
        filename = username + "_bookHistory.txt";
        bookHistory.open(filename, std::ios::out | std::ios::app);
        if (!bookHistory.is_open())
        {
            std::cerr << "Error creating/Opening file: " << filename << std::endl;
        }
        bookHistory.close();
    }
};

class admin : public User
{
public:
    // constructor
    admin(string name, string username, string password, string email) : User(name, username, password, email, "admin") // here, we redirect users created with type "admin"
    {
    }
};

// end of class definitions
