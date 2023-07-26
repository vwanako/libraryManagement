#include <iostream>
#include "Users.h"

int main()
{

    admin testUser("John Doe", "johndoebooks", "1234", "johndoe@gmail.com");

    testUser.createUser();

    return 0;
}