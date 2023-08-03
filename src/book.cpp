#include <iostream>
#include <fstream>
#include <string>
#include <book.h>

extern std::fstream books_file;

book::book(std::string title, std::string author, std::string genre, float price)
{
    set_title(title);
    set_author(author);
    set_genre(genre);
    set_available("available");
    set_price(price);
}

void book::save_to_file()
{
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

void book::set_title(std::string title)
{
    this->title = title;
}
void book::set_author(std::string author)
{
    this->author = author;
}
void book::set_genre(std::string genre)
{
    this->genre = genre;
}
void book::set_available(std::string available)
{
    this->available = available;
}
void book::set_price(float price)
{
    this->price = price;
}

// getters

std::string book::get_title() const
{
    return title;
}

std::string book::get_author() const
{
    return author;
}

std::string book::get_genre() const
{
    return genre;
}

std::string book::is_available() const
{
    return available;
}

float book::get_price() const
{
    return price;
}
