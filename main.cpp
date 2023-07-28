#include <iostream>
#include "Users.h"

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
            cout << "\nEnter action:\n1: View library collection\n2: View users\n3: View issued books\n4: Issue a book\n5: Return a book\n6: Create new user\n7: Create new book\nq: quit program";
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
                result.error = false;

                return result;
            }
        }
    }
    result.error = true;
    return result;
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

int main()
{

    char userInput;
    User loggedInUser;

    while (true)
    {

        cout << "\nEnter action:\n1: Login\nq: quit program";
        cin >> userInput;
        switch (userInput)
        {
        case '1':
            loggedInUser = login();
            cout << "user information: " << loggedInUser.getUsername() << "," << loggedInUser.getName() << "," << loggedInUser.getPassword() << "," << loggedInUser.getEmail();
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