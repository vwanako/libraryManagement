#ifndef UTILS_H
#define UTILS_H

/*! \fn clear_terminal()
    @brief Clears terminal to improve readability.
    Used inside of the menus. Clears the terminal after executing a function inside of the switch case options.
 */
void clear_terminal();

/*! \fn check_go_back()
    @brief Used with other functions so that the terminal is not instantly cleared when a function finishes executing.
    Inside the menu loops, the terminal is cleared automatically when a certain action finishes executing. This function is used to avoid that it clears before the user is done reading the result of another function.
 */
void check_go_back();

/*! \fn parse(const std::string &line)
    @brief Used for splitting the info in txt files' lines into vector elements.
    This function reads the lines in a txt file and splits them into separate elements of a vector every time it finds a ",". With it, we can get the information from the txt databases and use them in the code in different ways, depending on what info we're looking for.
    @param line The line it's currently reading and splitting into the vector. Usually, this is inside of a while(getline(filename, line)) loop, so it's the line of the current loop iteration.
 */
std::vector<std::string> parse(const std::string &line);

#endif // UTILS_H