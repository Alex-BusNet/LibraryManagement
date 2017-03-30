#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>
#include <QDebug>
#include <QDate>

struct Book
{
    QString title;
    QString author;
    int ISBN;
    QVector<int> copiesAvailable;
    bool longTerm;
    QString publisher;
    int publishYear;

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
        this->title = other.title;
        this->author = other.author;
        this->ISBN = other.ISBN;
        this->copiesAvailable = other.copiesAvailable;
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
    QDate dateDue;
    bool needsReminder;
};

#endif // DATATYPES_H
