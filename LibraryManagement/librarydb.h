#ifndef LIBRARYDB_H
#define LIBRARYDB_H

#include <QDate>
#include <QObject>
#include <QVector>
#include "user.h"
#include "datatypes.h"
#include "staff.h"

class LibraryDB : public QObject
{
    Q_OBJECT
public:
    //Use LibraryDB::instance() to access these functions.
    // DO NOT make a new LibraryDB object
    static LibraryDB *instance();

    bool AddUser(UserBase *u, QString pass);
    void RemoveUser(UserBase *u);
    QVector<UserBase*> GetAllUsers();
    
    bool AddStaff(Staff* s);
    void RemoveStaff(Staff* s);

    bool LogIn(const QString username, const QString pass);
    int Authenticate(UserBase *s);

    void AddBook(Book b);
    void RemoveBook(Book b);
    void EditBook(int targetISBN, Book editedBook);

    QVector<Book> GetBooks(const QString title = " ", const QString author = " ");
    Book GetBook(const int ISBN);
    Book GetBook(const QString title, const QString author) const;
    
    QVector<Book> GetAllBooks();

    int GetCopiesOfBook(const int ISBN);
    int GetCopiesOfBook(const QString title, const QString author);

    void CheckOutBook(const User u, const Book b);
    void BooksDueBy(QDate date, const QVector<Book> booksDue);

    void SaveData();

private:
    QVector<Book> masterList;
    QVector<UserBase*> registeredUsers;
    QVector<Staff*> staffMembers;
    QVector<BookReciept> checkedOutBooks;

    QHash<QString, QString> memberLogins;


};

#endif // LIBRARYDB_H
