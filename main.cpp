#include <iostream>
#include "Users.h"

// void userMenu()
// {
//     if ()
// }

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

        cout << "\nEnter action: \n1: Login \nq: quit program" << endl;
        cin >> userInput;
        switch (userInput)
        {
        case '1':
            loggedInUser = login();
            cout << "user information: " << loggedInUser.getUsername() << "," << loggedInUser.getName() << "," << loggedInUser.getPassword() << "," << loggedInUser.getEmail();
            break;
        case 'q':
            return 0;
        }
    }

    return 0;
}