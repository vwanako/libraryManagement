#include <iostream>
#include "Users.h"

void clearTerminal()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// this function is called within the action functions to ask if the user wants to leave before finishing them, this way the result of the function won't instantly disappear when the loop repeats and the terminal is cleared.
void checkGoBack()
{
    char userInput;
    while (true)
    {
        cout << "\nPress q to go back to menu...";
        cin >> userInput;
        switch (userInput)
        {
        case 'q':
            return;
        default:
            cout << "Invalid input";
        }
    }
}

void printUsers()
{
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

    checkGoBack();
}

// prints the library collection of books, all of them.
void printBooks()
{
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

    checkGoBack();
}

struct Result
{
    User user;
    bool error;
};

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
    result.error = true;
    return result;
}

void issueBook()
{
    // receives input of who is getting the book from their username.
    string username;
    cout << "\nEnter the borrower's username: ";
    cin.ignore();
    getline(cin, username);

    // the user's book history is formatted as username_bookHistory.txt, here, we set the file
    string filename = username + "_bookHistory.txt";
    fstream bookHistory, booksFile;

    // since book title will be used to manipulate two separate files, we will declare and receive it outside the conditions, so we don't need to ask for input twice.
    string title;
    cout << "Enter book title: ";
    getline(cin, title);

    // opens the user's book history file
    bookHistory.open(filename, ios::app);
    if (bookHistory.is_open())
    {
        string issueDate, returnDate;

        // receives issue date and return date
        cout << "Enter issue date: ";
        getline(cin, issueDate);

        cout << "Enter return date: ";
        getline(cin, returnDate);

        // inserts the formated information into the file and closes it
        bookHistory << "Title: " << title << " Issue date: " << issueDate << " Return date: " << returnDate << endl;
        bookHistory.close();
    }
    else
    {
        cerr << "Error opening file: " << filename << endl;
    }

    // creates a vector of strings, we will use it to store all the information in the file, along with the updated line and
    vector<string> updatedLines;

    // opens the books file (where the information of the library collection is stored) in read mode
    booksFile.open("books.txt", ios::in);

    // if
    if (booksFile.is_open())
    {
        booksFile.seekg(0);

        string line;
        while (getline(booksFile, line))
        {
            vector<string> tokens = parse(line);
            if (!tokens.empty() && tokens[0] == title)
            {
                tokens[4] = "false";
                string updatedLine = tokens[0] + "," + tokens[1] + "," + tokens[2] + "," + tokens[3] + "," + tokens[4];
                updatedLines.push_back(updatedLine);
            }
            else
            {
                updatedLines.push_back(line);
            }
        }

        booksFile.close();
    }
    else
    {
        cout << "Error opening books file.";
    }

    booksFile.open("books.txt", ios::out | ios::trunc);

    for (const string &updatedLine : updatedLines)
    {
        booksFile << updatedLine << endl;
    }

    booksFile.close();

    checkGoBack();
}

void returnBook()
{
    string username;
    cout << "\nEnter the borrower's username: ";
    cin.ignore();
    getline(cin, username);

    cout << username << "'s book history: ";
    printBookHistory(username);

    string filename = username + "_bookHistory.txt";
    fstream bookHistory;

    bookHistory.open(filename, ios::app);
    if (bookHistory.is_open())
    {
        string title, returnDate;
        cout << "\nEnter book title: ";
        getline(cin, title);

        cout << "\nEnter return date: ";
        getline(cin, returnDate);

        bookHistory << "Title: " << title << " Return date: " << returnDate << endl;
        bookHistory.close();
    }
    else
    {
        cerr << "\nError opening file: " << filename << endl;
    }

    checkGoBack();
}

User login()
{
    string username, password, line;
    string lineUsername, lineName, linePassword, lineEmail;

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
            cout << "\nEnter action:\n1: View library collection\n2: View my currently issued books\n3: View my book history\nq: quit program";
            cin >> userInput;
            switch (userInput)
            {
            case '1':
                break;
            case '2':
                break;
            case 'q':
                return;
            default:
                cout << "\nInvalid input. Please try again.";
                break;
            }
        }
    }
    else if (usertype == "admin")
    {
        while (true)
        {
            clearTerminal();

            cout << "\nEnter action:\n1: View library collection\n2: View users\n3: View issued books\n4: Issue a book\n5: Return a book\n6: Create new user\n7: Create new book\nq: log out\n";
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
                break;
            case '4':
                issueBook();
                break;
            case '5':
                break;
            case '6':
                createUser();
                break;
            case '7':
                createBook();
                break;
            case 'q':
                return;
            default:
                cout << "\nInvalid input. Please try again.";
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