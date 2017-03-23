#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>
#include <QDebug>

struct Book
{
    QString title;
    QString author;
    int ISBN;
    int copies;
    bool longTerm;

    bool operator ==(const Book& other) const
    {
        return (this->ISBN == other.ISBN);
    }

    bool operator !=(const Book& other) const
    {
        return (this->ISBN != other.ISBN);
    }

    void operator =(const Book& other)
    {
        qDebug() << "Book Operator=";
        this->title = other.title;
        this->author = other.author;
        this->ISBN = other.ISBN;
        this->copies = other.copies;
        this->longTerm = other.longTerm;
    }

    bool operator ==(const int& i)
    {
        return (ISBN == i);
    }

    void operator =(const int& i)
    {
        this->ISBN = i;
    }

    bool operator !=(const int& i)
    {
        return (ISBN != i);
    }
};

struct BookReciept
{
    int userNo;
    int ISBN;
};

#endif // DATATYPES_H
