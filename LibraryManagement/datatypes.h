#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>

struct Book
{
    QString title;
    QString author;
    int ISBN;
    int copies;
    bool longTerm;

    bool operator==(const Book& other) { return (ISBN == other.ISBN); }
    bool operator==(const int& i) { return (ISBN == i); }
    Book operator=(const Book& other) { return other; }
    Book operator=(const int& i) { if(i == 0) { Book b; b.title.clear(); b.author.clear(); b.ISBN = 0; b.copies = 0; return b; } }
    bool operator!=(const Book& other) { return (other.ISBN != ISBN); }
    bool operator!=(const int& i) { return (ISBN != i); }
};

struct BookReciept
{
    int userNo;
    int ISBN;
};

#endif // DATATYPES_H
