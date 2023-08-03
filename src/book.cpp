#include <iostream>
#include <fstream>
#include <string>

std::fstream books_file;

class book
{
private:
    std::string title, author, genre, available;
    float price;

public:
    // constructor

    book(std::string title, std::string author, std::string genre, float price)
    {
        set_title(title);
        set_author(author);
        set_genre(genre);
        set_available("available");
        set_price(price);
    }

    void save_to_file()
    {
        std::fstream books_file;
        books_file.open("books.txt", std::ios::app);
        if (books_file.is_open())
        {
            books_file << title << "," << author << "," << genre << "," << price << "," << is_available() << std::endl;
            books_file.close();
        }
        else
        {
            std::cout << "\nError: Unable to open the file for saving the book.";
        }
    }

    // setters

    void set_title(std::string title)
    {
        this->title = title;
    }
    void set_author(std::string author)
    {
        this->author = author;
    }
    void set_genre(std::string genre)
    {
        this->genre = genre;
    }
    void set_available(std::string available)
    {
        this->available = available;
    }
    void set_price(float price)
    {
        this->price = price;
    }

    // getters

    std::string get_title() const
    {
        return title;
    }

    std::string get_author() const
    {
        return author;
    }

    std::string get_genre() const
    {
        return genre;
    }

    std::string is_available() const
    {
        return available;
    }

    float get_price() const
    {
        return price;
    }
};