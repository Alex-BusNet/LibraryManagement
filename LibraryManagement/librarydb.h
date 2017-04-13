#ifndef LIBRARYDB_H
#define LIBRARYDB_H

#include <QDate>
#include <QJsonArray>
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
    void RemoveUser(int userNumber);
    QVector<UserBase*> GetAllUsers();

    UserBase* GetUser(QString username);
    UserBase* GetUser(int userNumber);
    int GetNumberOfUsers();
    void UpdateUser(int userNo, UserBase *ub, bool isStaff);

    bool AddStaff(Staff* s);
    void RemoveStaff(Staff *s);

    int LogIn(const QString username, const QString pass);
    int Authenticate(UserBase *s);

    void AddBook(Book *b);
    void RemoveBook(long long ISBN);
    void EditBook(long long isbn, Book *editedBook);

    QVector<Book *> GetBooks(const QString title = " ", const QString author = " ");
    Book* GetBookAt(int index);
    Book* GetBook(const long long ISBN);
    Book* GetBook(const QString title, const QString author);
    
    QVector<Book*> GetAllBooks();

    int GetCopiesOfBook(const long long ISBN);
    int GetCopiesOfBook(const QString title, const QString author);

    void ReturnBook(long long ISBN);

    void CheckOutBook(UserBase *u, Book *b, bool needsReminder, bool isReservation = false);
    QVector<BookReciept*> BooksDueBy(QDate date) const;
    QVector<BookReciept*> GetAllCheckedOutBooks();
    void ReserveBook(UserBase *u, Book *b, QDate pickupDate);
    QVector<BookReciept*> GetReservation(const int userNumber);
    void FulfillReservation(BookReciept *br);

    QVector<BookReciept*> GetAllReservations();

    void SaveData();
    void ParseDBJson();

    void LoadSecondaryData();

    int GetActiveUser();
    QString GetPass(QString username);

private:
    QVector<UserBase*> registeredUsers;
    QVector<Staff*> staffMembers;

    QVector<Book*> masterList;
    QVector<BookReciept*> checkedOutBooks;
    QVector<BookReciept*> reservedBooks;

    QVector<Book*> oldBooks;

    QHash<QString, QString> memberLogins;

    void SortCheckOutBooks();

    int memberNumber = 00000000;
    int loggedInUser;

    void ParseBookData();
    void ParseUserData();

    void ParseReserved();
    void ParseOld();
    void ParseCheckedOut();

    QJsonArray masterArr, oldArr;
};

#endif // LIBRARYDB_H
