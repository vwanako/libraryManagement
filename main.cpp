#include <iostream>
#include "Users.h"

int main()
{
    Book book1("The Picture of Dorian Gray", "Oscar Wilde", "Horror", true);
    User user1("Victor", "vwanako", "123", "victor@gmail.com");
    User user2("Athena", "athena", "123", "athena@gmail.com");

    user1.addBookToHistory(book1);
    return 0;
}