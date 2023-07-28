#include <iostream>
#include "Users.h"

// void userMenu()
// {
//     if ()
// }

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