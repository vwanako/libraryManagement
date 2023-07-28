#include <iostream>
#include "Users.h"

// void userMenu()
// {
//     if ()
// }

int main()
{
    // admin newAdmin("john doe", "johndoeadmin", "1234", "johndoe@mail.com");

    // newAdmin.createUser();

    char userInput;
    User emptyUser;

    while (true)
    {

        cout << "Enter action: \n1: Login \nq: quit program" << endl;
        switch (userInput)
        {
        case '1':
            break;
        case 'q':
            return 0;
        }
    }

    return 0;
}