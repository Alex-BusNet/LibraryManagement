#ifndef LIBRARYDB_H
#define LIBRARYDB_H

#include <QDate>
#include <QObject>
#include <QVector>
#include "userbase.h"
#include "datatypes.h"
#include "staff.h"
#include "manager.h"

class LibraryDB : public QObject
{
    Q_OBJECT
public:
    //Use LibraryDB::instance() to access these functions.
    // DO NOT make a new LibraryDB object
    static LibraryDB *instance();

    bool AddUser(UserBase *u, QString pass);
    void RemoveUser(int index);
    QVector<UserBase*> GetAllUsers();
    UserBase* GetUser(QString username);
    UserBase* GetUser(int userNumber);
    
    bool AddStaff(Staff* s);
    void RemoveStaff(int index);

    bool LogIn(const QString username, const QString pass);
    int Authenticate(UserBase *s);

    void AddBook(Book *b);
    void RemoveBook(int index);
    void EditBook(int index, Book *editedBook);

    QVector<Book *> GetBooks(const QString title = " ", const QString author = " ");
    Book* GetBookAt(int index);
    Book* GetBook(const int ISBN);
    Book* GetBook(const QString title, const QString author);
    
    QVector<Book*> GetAllBooks();

    int GetCopiesOfBook(const int ISBN);
    int GetCopiesOfBook(const QString title, const QString author);

    void ReturnBook(int ISBN);

    void CheckOutBook(UserBase *u, Book *b, bool needsReminder, bool isReservation = false);
    QVector<BookReciept*> BooksDueBy(QDate date) const;

    void ReserveBook(UserBase *u, Book *b, QDate pickupDate);
    QVector<BookReciept*> GetReservation(const int userNumber);
    void FulfillReservation(BookReciept *br);

    void SaveData();

private:
    QVector<UserBase*> registeredUsers;
    QVector<Staff*> staffMembers;

    QVector<Book*> masterList;
    QVector<BookReciept*> checkedOutBooks;
    QVector<BookReciept*> reservedBooks;

    QVector<Book*> oldBooks;

    QHash<QString, QString> memberLogins;

    void SortCheckOutBooks();


};

#endif // LIBRARYDB_H
