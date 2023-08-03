// libraries used
#include <iostream>
#include <string>

// header files used
#include <users.h>
#include <utils.h>
#include <book.h>
#include <library.h>

std::fstream users_file;
std::fstream books_file;

int main()
{

    char user_input;
    user logged_in_user;

    while (true)
    {
        clear_terminal();
        std::cout << "\nEnter action:\n1: Login\nq: quit program\n";
        std::cin >> user_input;
        switch (user_input)
        {
        case '1':
            logged_in_user = login();
            user_menu(logged_in_user);
            break;
        case 'q':
            return 0;
        default:
            std::cout << "\nInvalid input. Please try again.";
            break;
        }
    }

    return 0;
}