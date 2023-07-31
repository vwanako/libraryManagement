#include <iostream>
#include <fstream>
#include <string>
using namespace std;

fstream booksFile;

class Book
{
private:
    string title, author, genre;
    float price;
    int bid;
    bool available;

public:
    // constructor

    Book(string title, string author, string genre, float price)
    {
        setTitle(title);
        setAuthor(author);
        setGenre(genre);
        setAvailable(true);

        booksFile.open("books.txt", ios::app);
        if (booksFile.is_open())
        {
            booksFile << title << "," << author << "," << genre << "," << price << "," << isAvailable() << endl;
        }
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