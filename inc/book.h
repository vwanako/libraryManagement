#ifndef BOOK_H
#define BOOK_H

std::fstream books_file;

class book
{
private:
    std::string title, author, genre, available;
    float price;

public:
    // constructor

    book(std::string title, std::string author, std::string genre, float price);
    void save_to_file();

    // setters
    void set_title(std::string title);
    void set_author(std::string author);
    void set_genre(std::string genre);
    void set_available(std::string available);
    void set_price(float price);

    // getters
    std::string get_title() const;
    std::string get_author() const;
    std::string get_genre() const;
    std::string is_available() const;
    float get_price() const;
};

#endif // BOOK_H