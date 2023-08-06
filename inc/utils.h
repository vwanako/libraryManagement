#ifndef UTILS_H
#define UTILS_H
#include <vector>

#include <library.h>
#include <users.h>
#include <book.h>

void clear_terminal();
void check_go_back();
std::vector<std::string> parse(const std::string &line);
void print_users();
void print_books();
void print_book_history(const std::string &user);
void print_available_books();
bool check_book_availability(const std::string &title);
bool check_username_availability(const std::string &username);
bool check_username_exists(const std::string &username);
bool check_title_availability(const std::string &title);
bool check_in_issued(const std::string &title, const std::string &user);
void print_issued_books(const std::string &user);
struct result;
result authenticate(const std::string &username, const std::string &password);
user login();
void user_menu(const user &user);

#endif // UTILS_H