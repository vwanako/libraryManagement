#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unistd.h>
#include "Book.h"
using namespace std;

fstream usersFile;

vector<string> parse(const string &line)
{
    // each text between ","
    vector<string> tokens;
    string tempLine;

    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ',')
        {
            tokens.push_back(tempLine);
            tempLine.clear();
            continue;
        }

        tempLine += line[i];
    }

    tokens.push_back(tempLine);
    return tokens;
}

class User
{
protected:
    string name, username, password, email, filename, userType;
    bool isLoggedin;
    fstream bookHistory;

public:
    // constructors

    User(string name, string username, string password, string email, string userType)
    {
        setName(name);
        setUsername(username);
        setPassword(password);
        setEmail(email);
        setLogin(false);
        filename = username + "_bookHistory.txt";

        setUserType(userType);

        // append user information to the users.txt file
        usersFile.open("users.txt", ios::app);
        if (usersFile.is_open())
        {
            usersFile << username << "," << name << "," << password << "," << email << "," << userType << endl;
            usersFile.close();
        }
        else
        {
            std::cerr << "Error creating/opening file: users.txt" << std::endl;
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

    void setLogin(bool isLoggedIn)
    {
        this->isLoggedin = isLoggedIn;
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

    bool getLogin() const
    {
        return isLoggedin;
    }

    // methods

    void addBookToHistory(const Book &book)
    {
        bookHistory.open(filename, ios::app);
        if (bookHistory.is_open())
        {
            bookHistory << "Title: " << book.getTitle() << "Issue date: " << endl;
            bookHistory.close();
        }
        else
        {
            cerr << "Error opening file: " << filename << endl;
        }
    }

    void removeBookFromHistory(const Book &book)
    {
        bookHistory.open(filename, ios::in); // open file in read mode.

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

        bookHistory.close();

        bookHistory.open(filename, ios::out); // open file in write mode.
        if (!bookHistory.is_open())
        {
            cerr << "Error opening file for writing: " << filename << endl;
            return;
        }

        for (const auto &title : updatedHistory)
        {
            bookHistory << title << "\n";
        }

        bookHistory.close();
    }

    void login()
    {
        string username, password, line;
        string lineUsername, lineName, linePassword, lineEmail;

        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);

        while (!authenticate(username, password))
        {
            cout << "Username or password incorrect. Try again.";
            cout << "Enter username: ";
            getline(cin, username);
            cout << "Enter password: ";
            getline(cin, password);
        }

        cout << "Login sucessfull." << endl;
        setLogin(true);
    }

    bool authenticate(const string &username, const string &password)
    {
        usersFile.open("users.txt", ios::in);
        if (usersFile.is_open())
        {
            string line;
            while (getline(usersFile, line))
            {
                vector<string> tokens = parse(line);
                if (tokens[0] == username && tokens[2] == password)
                {
                    usersFile.close();
                    return true;
                }
            }
        }
        return false;
    }
};

class regularUser : public User
{
private:
    fstream issuedBooks;
    fstream bookHistory;

public:
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

    void viewBooks()
    {
    }
    void myBooks()
    {
        string line;

        bookHistory.open(filename, ios::in);
        if (!bookHistory.is_open())
        {
            cerr << "Error opening book history." << endl;
            return;
        }

        while (getline(bookHistory, line))
        {
            cout << line << endl;
        }
    }
};

class admin : public User
{
private:
    // we will add any private attributes for the admin class here.
public:
    // constructor
    admin(string name, string username, string password, string email) : User(name, username, password, email, "admin") // here, we redirect users created with type "admin"
    {
    }

    // methods

    void createUser()
    {
        // we will create and store temporary varibles for each attribute our constructor asks for.

        string tempName, tempUsername, tempPassword, tempEmail, tempUserType;

        cout << "New user menu.\nName: ";
        getline(cin, tempName);
        cout << "Username: ";
        getline(cin, tempUsername);
        cout << "Password: ";
        getline(cin, tempPassword);
        cout << "Email: ";
        getline(cin, tempEmail);

        // the user type variable can only be two things: 'admin' or 'user'. we will use this loop to validate the input, making sure to only accept those values.
        while (true)
        {
            cout << "\nUser type [user/admin]: " << endl;
            cin >> tempUserType;

            // convert the input to lowercase to make the validation case-insensitive
            transform(userType.begin(), userType.end(), userType.begin(), ::tolower);

            if (tempUserType == "user" || tempUserType == "admin")
            {
                break;
                // leaves the loop if appropriate input is received.
            }
            else
            {
                cout << "\nInvalid user type. Please enter 'user' or 'admin'." << endl;
            }
        }

        if (tempUserType == "user")
        {
            regularUser newUser(tempName, tempUsername, tempPassword, tempEmail);
        }
        else // since the user type has already been validated, if it's not "user", it has to be "admin", so we don't need an else if condition, only and else will be fine.
        {
            admin newAdmin(tempName, tempUsername, tempPassword, tempEmail);
        }

        cout << "\nNew user being created";
        for (int i = 0; i < 3; i++)
        {
            sleep(1);
            cout << ".";
            // this makes "New user being created..." appear on the console with a one second delay for each "."
        }

        sleep(1);
        cout << "\nNew user has been sucessfully created!" << endl;
    }

    void createBook()
    {
        string tempTitle, tempAuthor, tempGenre;
        float tempPrice;

        cout << "New book menu.\nTitle: ";
        getline(cin, tempTitle);
        cout << "Author: ";
        getline(cin, tempAuthor);
        cout << "Genre: ";
        getline(cin, tempGenre);
        cout << "Price: ";
        cin >> tempPrice;

        Book newBook(tempTitle, tempAuthor, tempGenre, tempPrice);

        cout << "\nNew book being created";
        for (int i = 0; i < 3; i++)
        {
            sleep(1);
            cout << ".";
            // this makes "New user book created..." appear on the console with a one second delay for each "."
        }

        sleep(1);
        cout << "\nNew book has been sucessfully created!" << endl;
    }
};