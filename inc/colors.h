/**
 * @file colors.h
 * @author Tales Oliveira (tales.olivera@estudante.ifb.edu.br)
 * @brief a header to change colors and letters in the terminal
 */
#ifndef COLORS_H
#define COLORS_H

#define clear_win_screen() system("cls")    // Clear the terminal screen on windows
#define clear_unix_screen() system("clear") // Clear the terminal screen on linux or mac

void print_color(const std::string &text, const std::string &color);
void println_color(const std::string &text, const std::string &color);

// CHAR SETTINGS
#define RESET "\x1B[0m" // Reset to the original colors

#define BOLD "\x1b[1m"    // Bold the letter
#define FAINT "\x1b[2m"   // Faint the letter
#define ITALIC "\x1b[3m"  // Italic the letter
#define UNDER "\x1b[4m"   // Underline the letter
#define BLINK "\x1b[5m"   // Blink the letter
#define C6 "\x1b[6m"      //
#define INVERSE "\x1b[7m" // Inverse BG color with the letter
#define HIDE "\x1b[8m"    // Hide the letter in the terminal
#define STRIKE "\x1b[9m"  // Strike through the letter

// REGULAR LETTERS
#define BLACK "\x1b[0;30m"   // Black
#define RED "\x1b[0;31m"     // Red
#define GREEN "\x1b[0;32m"   // Green
#define YELLOW "\x1b[0;33m"  // Yellow
#define BLUE "\x1b[0;34m"    // Blue
#define MAGENTA "\x1b[0;35m" // Magenta
#define CYAN "\x1b[0;36m"    // Cyan
#define WHITE "\x1b[0;37m"   // White

// STRONG LETTERS
#define BLACK_BOLD "\x1b[1;30m"    // Black
#define RED_BOLD "\x1b[1;31m"      // Red
#define GRENN_BOLD "\x1b[1;32m"    // Green
#define YELLOW_BOLD "\x1b[1;33m"   // Yellow
#define BLUE_BOLD "\x1b[1;34m"     // Blue
#define MAGENTA__BOLD "\x1b[1;35m" // Magenta
#define CYAN__BOLD "\x1b[1;36m"    // Cyan
#define WHITE_BOLD "\x1b[1;37m"    // White

// BACKGROUND COLOR
#define BLACK_BG "\x1b[1;40m"   // Black
#define RED_BG "\x1b[1;41m"     // Red
#define GREEN_BG "\x1b[1;42m"   // Green
#define YELLOW_BG "\x1b[1;43m"  // Yellow
#define BLUE_BG "\x1b[1;44m"    // Blue
#define MAGENTA_BG "\x1b[1;45m" // Magenta
#define CYAN_BG "\x1b[1;46m"    // Cyan
#define WHIE_BG "\x1b[1;47m"    // White

#endif // COLORS_H