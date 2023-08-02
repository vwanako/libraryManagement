#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <unistd.h>
#include "Users.h"

void clearTerminal()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

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
// this function is called within the action functions to ask if the user wants to leave before finishing them, this way the result of the function won't instantly disappear when the loop repeats and the terminal is cleared.
void checkGoBack()
{
    char userInput;
    while (true)
    {
        cout << "\nPress q to go back to menu...\n";
        cin >> userInput;
        switch (userInput)
        {
        case 'q':
            return;
        default:
            cout << "\nInvalid input";
        }
    }
}

void printUsers()
{
    cout << "USERNAME | NAME | PASSWORD | EMAIL | USER TYPE\n";
    usersFile.open("users.txt", ios::in);
    if (usersFile.is_open())
    {
        string line;
        while (getline(usersFile, line))
        {
            cout << line << endl;
        }
        usersFile.close();
    }
    else
    {
        cout << "\nError opening users file.";
    }

    // waits for user input before finalizing function (explanaition in function declaration)
    checkGoBack();
}

// prints the library collection of books, all of them.
void printBooks()
{
    // shows file formatting
    cout << "TITLE | AUTHOR | GENRE | PRICE | AVAILABILITY STATUS\n";

    booksFile.open("books.txt", ios::in);
    if (booksFile.is_open())
    {
        string line;
        while (getline(booksFile, line))
        {
            cout << line << endl;
        }
        booksFile.close();
    }
    else
    {
        cout << "\nError opening book collection file.";
    }

    // waits for user input before finalizing function (explanaition in function declaration)
    checkGoBack();
}

void printBookHistory(const string &user)
{
    // concatenates the parameter with the file name
    string filename = user + "_bookHistory.txt";
    fstream bookHistory;

    // shows file formatting
    cout << "TITLE | ISSUE DATE | RETURN DATE\n";

    // opens file in read mode
    bookHistory.open(filename, ios::in);
    if (bookHistory.is_open())
    {
        // read the history line by line, printing each one
        string line;
        while (getline(bookHistory, line))
        {
            cout << line << endl;
        }
        // closes file
        bookHistory.close();
    }
    // handles errors when opening file
    else
    {
        cout << "\nError opening book history file.";
    }
}

// this function will print only the title, author and genre of the books set as "available". It will be shown in the issue function.
void printAvailableBooks()
{
    fstream booksFile;
    vector<string> availableBooks;

    booksFile.open("books.txt", ios::in);
    if (booksFile.is_open())
    {
        string line;
        while (getline(booksFile, line))
        {
            vector<string> tokens = parse(line);
            if (tokens[4] == "available")
            {
                string basicInfo = "title: " + tokens[0] + " | author: " + tokens[1] + " | genre: " + tokens[2];
                availableBooks.push_back(basicInfo);
            }
        }
        booksFile.close();
    }
    else
    {
        cout << "\nError opening books file.";
    }

    for (const string &line : availableBooks)
    {
        cout << line << endl;
    }
}

bool checkBookAvailability(const string &title)
{
    fstream booksFile;

    booksFile.open("books.txt", ios::in);
    if (booksFile.is_open())
    {
        string line;
        while (getline(booksFile, line))
        {
            vector<string> tokens = parse(line);
            if (tokens[0] == title && tokens[4] == "available")
            {
                booksFile.close();
                return true;
            }
        }
        booksFile.close();
        return false;
    }
    else
    {
        cout << "\nError opening books file.";
        return false;
    }
}

bool checkUsernameAvailability(const string &username)
{
    fstream usersFile;

    usersFile.open("users.txt", ios::in);
    if (usersFile.is_open())
    {
        string line;
        while (getline(usersFile, line))
        {
            vector<string> tokens = parse(line);
            // if the program finds the username in the users file, availability is false.
            if (tokens[0] == username)
            {
                usersFile.close();
                return false;
            }
        }
        usersFile.close();
        return true; // if the program doesnt't find the username, availability is true
    }
    else
    {
        cout << "\nError opening users file.";
        return false;
    }
}

bool checkTitleAvailability(const string &title)
{
    fstream booksFile;

    booksFile.open("books.txt", ios::in);
    if (booksFile.is_open())
    {
        string line;
        while (getline(booksFile, line))
        {
            vector<string> tokens = parse(line);
            // if the program finds the title in the books file, availability is false.
            if (tokens[0] == title)
            {
                booksFile.close();
                return false;
            }
        }
        booksFile.close();
        return true; // if the program doesnt find the title, availability is true
    }
    else
    {
        cout << "\nError opening books file.";
        return false;
    }
}

bool checkInIssued(const string &title, const string &user)
{
    fstream issuedBooks;
    string filename = user + "_issuedBooks.txt";

    issuedBooks.open(filename, ios::in);
    if (issuedBooks.is_open())
    {
        string line;
        while (getline(issuedBooks, line))
        {
            vector<string> tokens = parse(line);
            if (tokens[0] == title)
            {
                issuedBooks.close();
                return true;
            }
        }
        issuedBooks.close();
        return false;
    }
    else
    {
        cout << "\nError opening issued books file.";
        return false;
    }
}

void printIssuedBooks(const string &user)
{
    string filename = user + "_issuedBooks.txt";
    fstream issuedBooks;

    // shows file formatting
    cout << "TITLE | ISSUE DATE | RETURN DATE\n";

    issuedBooks.open(filename, ios::in);
    if (issuedBooks.is_open())
    {
        string line;
        while (getline(issuedBooks, line))
        {
            cout << line << endl;
        }
        issuedBooks.close();
    }
    else
    {
        cout << "\nError opening issued books file.";
    }
}

void createBook()
{
    string tempTitle, tempAuthor, tempGenre;
    float tempPrice;

    cout << "New book menu.\nTitle: ";
    cin.ignore();
    getline(cin, tempTitle);

    while (!checkTitleAvailability(tempTitle))
    {
        cout << "The book '" << tempTitle << "' already exists. Please try again or press 'q' to finalize book creation process.\n";
        getline(cin, tempTitle);
        if (tempTitle == "q")
        {
            cout << "\nBook creation process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

    cout << "Author: ";
    getline(cin, tempAuthor);
    cout << "Genre: ";
    getline(cin, tempGenre);
    cout << "Price: ";
    cin >> tempPrice;

    Book newBook(tempTitle, tempAuthor, tempGenre, tempPrice);
    newBook.saveToFile();

    cout << "\nNew book being created";
    for (int i = 0; i < 3; i++)
    {
        sleep(1);
        cout << ".";
        // this makes "New user book created..." appear on the console with a one second delay for each "."
    }

    sleep(1);
    cout << "\nNew book has been sucessfully created!" << endl;

    // waits for user input before finalizing function (explanaition in function declaration)
    checkGoBack();
}

void createUser()
{
    // we will create and store temporary varibles for each attribute our constructor asks for.

    string tempName, tempUsername, tempPassword, tempEmail, tempUserType;

    cout << "New user menu.\nName: ";
    cin.ignore();
    getline(cin, tempName);
    cout << "Username: ";
    getline(cin, tempUsername);

    while (!checkUsernameAvailability(tempUsername))
    {
        cout << "The username '" << tempUsername << "' already exists. Please try again or press 'q' to finalize user creation process.\n";
        getline(cin, tempUsername);
        if (tempUsername == "q")
        {
            cout << "\nUser creation process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

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
        transform(tempUserType.begin(), tempUserType.end(), tempUserType.begin(), ::tolower);

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
        newUser.saveToFile();
    }
    else // since the user type has already been validated, if it's not "user", it has to be "admin", so we don't need an "else if" condition, a simple "else" will be fine.
    {
        admin newAdmin(tempName, tempUsername, tempPassword, tempEmail);
        newAdmin.saveToFile();
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

    // waits for user input before finalizing function (explanaition in function declaration)
    checkGoBack();
}
struct Result
{
    User user;
    bool error;
};

Result authenticate(const string &username, const string &password)
{
    Result result;
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
                result.user.setUsername(tokens[0]);
                result.user.setName(tokens[1]);
                result.user.setPassword(tokens[2]);
                result.user.setEmail(tokens[3]);
                result.user.setUserType(tokens[4]);
                result.error = false;

                return result;
            }
        }
    }
    else
    {
        cout << "Error opening users file";
    }
    result.error = true;
    return result;
}

void issueBook()
{
    cout << "Available books:\n";
    printAvailableBooks();
    // receives input of who is getting the book from their username.
    string username;
    cout << "\nEnter the borrower's username: ";
    cin.ignore();
    getline(cin, username);

    // the user's book history is formatted as username_bookHistory.txt, here, we set the file
    string historyFilename = username + "_bookHistory.txt";
    string issuedFilename = username + "_issuedBooks.txt";
    fstream bookHistory, booksFile, issuedBooks;

    // since info will be used to manipulate three separate files, we will declare and receive it outside the conditions, so we don't need to ask for input twice.
    string title, issueDate, returnDate;
    cout << "\nEnter book title: ";
    getline(cin, title);

    while (!checkBookAvailability(title))
    {
        cout << "\nThe book '" << title << "' is not currently available or doesn't exist. Please try again or press 'q' to finalize issuing process.\n";
        getline(cin, title);
        if (title == "q")
        {
            cout << "\nIssue process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

    cout << "\nEnter issue date: ";
    getline(cin, issueDate);
    cout << "\nEnter return date: ";
    getline(cin, returnDate);

    // opens the user's book history file
    bookHistory.open(historyFilename, ios::app);
    if (bookHistory.is_open())
    {
        // inserts the formated information into the file and closes it
        bookHistory << title << "," << issueDate << "," << returnDate << endl;
        bookHistory.close();
    }
    else
    {
        cerr << "Error opening file: " << historyFilename << endl;
    }

    // does the same to the issuedBooks (the books the person issued and didn't return yet) as the bookHistory.
    issuedBooks.open(issuedFilename, ios::app);
    if (issuedBooks.is_open())
    {
        // inserts the formated information into the file and closes it
        issuedBooks << title << "," << issueDate << "," << returnDate << endl;
        issuedBooks.close();
    }
    else
    {
        cerr << "Error opening file: " << issuedFilename << endl;
    }

    // creates a vector of strings, we will use it to store all the information in the file, along with the updated line and
    vector<string> updatedLines;

    // opens the books file (where the information of the library collection is stored) in read mode
    booksFile.open("books.txt", ios::in);
    if (booksFile.is_open())
    {
        // sets the pointer to the beginning of the file
        booksFile.seekg(0);

        // creates a line variable, we will use it to read each line of the file until we find the book being issued
        string line;
        while (getline(booksFile, line))
        {
            // calls the parse function to split each information into elements of vector tokens
            vector<string> tokens = parse(line);
            // if tokens isn't empty and the element [0] is the title of the issued book
            if (!tokens.empty() && tokens[0] == title)
            {
                // changes the "is available" info to unavailable.
                tokens[4] = "unavailable";
                // creates a new line with the updated availability status without altering the other information
                string updatedLine = tokens[0] + "," + tokens[1] + "," + tokens[2] + "," + tokens[3] + "," + tokens[4];
                // stores the new line in the updated lines vector
                updatedLines.push_back(updatedLine);
            }
            // if the line isn't the book we're looking for, it will be stored in the updated lines vector without changes
            else
            {
                updatedLines.push_back(line);
            }
        }
        // closes the file
        booksFile.close();
    }
    // handling errors when opening the file fails
    else
    {
        cout << "Error opening books file.";
    }

    // opens the file again in write mode
    booksFile.open("books.txt", ios::out | ios::trunc);
    // overwrites the file using each element of the updated lines vector as a line in the file.
    for (const string &updatedLine : updatedLines)
    {
        booksFile << updatedLine << endl;
    }

    // close the file
    booksFile.close();

    // waits for user input before finalizing function (explanaition in function declaration)
    checkGoBack();
}

void returnBook()
{
    string username;
    cout << "\nEnter the borrower's username: ";
    cin.ignore();
    getline(cin, username);

    // prints the user's book history to make it easier to return books.
    cout << username << "'s book history: \n";
    printBookHistory(username);

    string issuedFilename = username + "_issuedBooks.txt";
    fstream issuedBooks;

    string title;
    cout << "\nEnter book title: ";
    getline(cin, title);
    while (!checkInIssued(title, username))
    {
        cout << "\nThe book '" << title << "' is not in " << username << "'s issued books file or doesn't exist. Please try again or press 'q' to finalize the returning process.\n";

        getline(cin, title);
        if (title == "q")
        {
            cout << "\nReturning process finalized. Redirecting to menu...";
            sleep(2);
            return;
        }
    }

    // removes the title from the currently issued books list. functions similar to the book history manipulation.
    vector<string> updatedIssueLines;
    issuedBooks.open(issuedFilename, ios::app);
    if (issuedBooks.is_open())
    {
        issuedBooks.seekg(0);

        string line;
        while (getline(issuedBooks, line))
        {
            vector<string> tokens = parse(line);

            if (tokens[0] != title)
            {
                updatedIssueLines.push_back(line);
            }
        }
        issuedBooks.close();
    }
    else
    {
        cerr << "\nError opening file: " << issuedFilename << endl;
    }

    issuedBooks.open(issuedFilename, ios::out | ios::trunc);

    for (const string &updatedIssueLine : updatedIssueLines)
    {
        issuedBooks << updatedIssueLine << endl;
    }

    issuedBooks.close();

    vector<string> updatedLines;

    // explanation is the same as the issue book function, except that it changes the token from "false" to "true"
    booksFile.open("books.txt", ios::in);
    if (booksFile.is_open())
    {
        booksFile.seekg(0);

        string line;
        while (getline(booksFile, line))
        {
            vector<string> tokens = parse(line);

            if (!tokens.empty() && tokens[0] == title)
            {
                // changes the "is available" info to available.
                tokens[4] = "available";
                string updatedLine = tokens[0] + "," + tokens[1] + "," + tokens[2] + "," + tokens[3] + "," + tokens[4];
                updatedLines.push_back(updatedLine);
            }
            else
            {
                updatedLines.push_back(line);
            }
        }
        // closes the file
        booksFile.close();
    }
    // handling errors when opening the file fails
    else
    {
        cout << "Error opening books file.";
    }

    // opens the file again in write mode
    booksFile.open("books.txt", ios::out | ios::trunc);
    // overwrites the file using each element of the updated lines vector as a line in the file.
    for (const string &updatedLine : updatedLines)
    {
        booksFile << updatedLine << endl;
    }

    // close the file
    booksFile.close();

    // waits for user input before finalizing function (explanaition in function declaration)
    checkGoBack();
}

User login()
{
    string username, password, line;

    cout << "\nEnter username: ";
    cin >> username;
    cout << "\nEnter password: ";
    cin >> password;

    while (true)
    {
        auto result = authenticate(username, password);
        if (!result.error)
        {
            cout << "Login sucessfull." << endl;
            return result.user;
        }
        cout << "Username or password incorrect. Try again.";
        cout << "Enter username: ";
        getline(cin, username);
        cout << "Enter password: ";
        getline(cin, password);
    }
}

void userMenu(const User &user)
{
    string usertype = user.getUserType();
    char userInput;

    if (usertype == "user")
    {
        while (true)
        {
            clearTerminal();

            cout << "\nEnter action:\n1: View library collection\n2: View my currently issued books\n3: View my book history\nq: log out\n";
            cin >> userInput;
            switch (userInput)
            {
            case '1':
                printBooks();
                break;
            case '2':
                printIssuedBooks(user.getUsername());
                checkGoBack();
                break;
            case '3':
                printBookHistory(user.getUsername());
                checkGoBack();
                break;
            case 'q':
                return;
            default:
                cout << "\nInvalid input. Please try again.";
                sleep(2);
                break;
            }
        }
    }
    else if (usertype == "admin")
    {
        while (true)
        {
            clearTerminal();

            cout << "\nEnter action:\n1: View library collection\n2: View users\n3: Issue a book\n4: Return a book\n5: Create new user\n6: Create new book\nq: log out\n";
            cin >> userInput;

            switch (userInput)
            {
            case '1':
                printBooks();
                break;
            case '2':
                printUsers();
                break;
            case '3':
                issueBook();
                break;
            case '4':
                returnBook();
                break;
            case '5':
                createUser();
                break;
            case '6':
                createBook();
                break;
            case 'q':
                return;
            default:
                cout << "\nInvalid input. Please try again.";
                sleep(2);
                break;
            }
        }
    }
}

int main()
{

    char userInput;
    User loggedInUser;

    while (true)
    {
        clearTerminal();
        cout << "\nEnter action:\n1: Login\nq: quit program\n";
        cin >> userInput;
        switch (userInput)
        {
        case '1':
            loggedInUser = login();
            userMenu(loggedInUser);
            break;
        case 'q':
            return 0;
        default:
            cout << "\nInvalid input. Please try again.";
            break;
        }
    }

    return 0;
}