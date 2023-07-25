#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book
{
private:
    string title, author, genre;
    bool available;

public:
    // constructor

    Book(string title, string author, string genre, bool available)
    {
        setTitle(title);
        setAuthor(author);
        setGenre(genre);
        setAvailable(available);
    }

    // setters

    void setTitle(string title)
    {
        this->title = title;
    }
    void setAuthor(string author)
    {
        this->author = author;
    }
    void setGenre(string genre)
    {
        this->genre = genre;
    }
    void setAvailable(bool available)
    {
        this->available = available;
    }

    // getters

    string getTitle() const
    {
        return title;
    }

    string getAuthor() const
    {
        return author;
    }

    string getGenre() const
    {
        return genre;
    }

    bool isAvailable() const
    {
        return available;
    }
};