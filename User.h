#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User
{
private:
    string name, username, password, email;
    fstream bookHistory;

public:
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
        bookHistory.open(getUsername() + "_bookHistory.txt", ios::app);
        if (bookHistory.is_open())
        {
            bookHistory << book.getTitle() << endl;
            bookHistory.close();
        }
    }

    void removeBookFromHistory(const Book &book)
    {
        bookHistory.open(getUsername() + "_bookHistory.txt", ios::in | ios::out); // open files both in read and write mode.
        string line, vector<string> updatedHistory;

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
}
