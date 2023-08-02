#include <iostream>
#include <fstream>
#include <string>
using namespace std;

fstream booksFile;

class Book
{
private:
    string title, author, genre, available;
    float price;
    int bid;

public:
    // constructor

    Book(string title, string author, string genre, float price)
    {
        setTitle(title);
        setAuthor(author);
        setGenre(genre);
        setAvailable("available");
        setPrice(price);
    }

    void saveToFile()
    {
        fstream booksFile;
        booksFile.open("books.txt", ios::app);
        if (booksFile.is_open())
        {
            booksFile << title << "," << author << "," << genre << "," << price << "," << isAvailable() << endl;
            booksFile.close();
        }
        else
        {
            cout << "\nError: Unable to open the file for saving the book.";
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
    void setAvailable(string available)
    {
        this->available = available;
    }
    void setPrice(float price)
    {
        this->price = price;
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

    string isAvailable() const
    {
        return available;
    }

    float getPrice() const
    {
        return price;
    }
};