#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Book.h"
using namespace std;

class User
{
private:
    string name, username, password, email, filename;
    fstream bookHistory;

public:
    // constructor
    User(string name, string username, string password, string email)
    {
        setName(name);
        setUsername(username);
        setPassword(password);
        setEmail(email);
        string filename = username + "_bookHistory.txt";

        bookHistory.open(filename, std::fstream::out | std::fstream::app);
        if (!bookHistory.is_open())
        {
            std::cerr << "Error creating/Opening file: " << filename << std::endl;
        }
        bookHistory.close();
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

    // methods

    void addBookToHistory(const Book &book)
    {
        bookHistory.open(filename, ios::app);
        if (bookHistory.is_open())
        {
            bookHistory << book.getTitle() << endl;
            bookHistory.close();
        }
        else
        {
            cerr << "Error opening file: " << filename << endl;
        }
    }

    void removeBookFromHistory(const Book &book)
    {
        bookHistory.open(filename, ios::in | ios::out); // open files both in read and write mode.

        if (!bookHistory.is_open())
        {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        string line;
        vector<string> updatedHistory;

        while (getline(bookHistory, line))
        {
            if (line != book.getTitle())
            {
                updatedHistory.push_back(line);
            }
        }

        bookHistory.clear();
        bookHistory.seekp(0);

        for (const auto &title : updatedHistory)
        {
            bookHistory << title << "\n";
        }

        bookHistory.close();
    }
};
