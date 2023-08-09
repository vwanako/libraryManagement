/**
 * @file colors.c
 * @author Tales Oliveira (tales.olivera@estudante.ifb.edu.br)
 * @brief a source to change colors and letters in the terminal
 */

#include <iostream>
#include <colors.h>

/**
 * \fn void print_color
 * @brief A source to change colors and letters in the terminal (CPP). Need to include <iostream>
 *
 * @param text The message to print
 * @param color The color to display in the terminal
 */
void print_color(const std::string &text, const std::string &color)
{
    std::cout << color << text << RESET;
}

void println_color(const std::string &text, const std::string &color)
{
    std::cout << color << text << RESET << std::endl;
}