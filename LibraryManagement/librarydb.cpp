#include "librarydb.h"
#include <QDebug>

Q_GLOBAL_STATIC(LibraryDB, libDb)

LibraryDB *LibraryDB::instance()
{
    return libDb;
}


/*
 * AddUser takes in a user object and a passwork.
 * If the username already exists, AddUser returns false.
 * else the function return true;
 */
bool LibraryDB::AddUser(UserBase *u, QString pass)
{
    if(memberLogins.contains(u->GetUsername()))
    {
        return false;
    }

    registeredUsers.push_back(u);
    memberLogins.insert(u->GetUsername(), pass);

    return true;
}

void LibraryDB::RemoveUser(UserBase *u)
{

}

bool LibraryDB::AddStaff(Staff* s)
{
    if(registeredUsers.contains(s))
    {
        staffMembers.push_back(s);
    }
}

void LibraryDB::RemoveStaff(Staff *s)
{

}

/*
 * LogIn takes in a username and password and
 * checks if they are registered in the system.
 */
bool LibraryDB::LogIn(const QString username, const QString pass)
{
    QString storedPass = memberLogins.value(username);

    if(storedPass == pass)
    {
        return true;
    }

    return false;
}

/*
 * Authenticate takes in user object and checks to see
 * if they are in the staff member list.
 *
 * Returns false if non-existent.
 */
bool LibraryDB::Authenticate(UserBase *s)
{
    if(Staff::instanceof(s))
    {
        if(staffMembers.contains(static_cast<Staff*>(s)))
        {
            return true;
        }
    }
    return false;
}

void LibraryDB::AddBook(Book b)
{
    masterList.push_back(b);
}

void LibraryDB::RemoveBook(Book b)
{

}

void LibraryDB::EditBook(int targetISBN, Book editedBook)
{

}

QVector<Book> LibraryDB::GetBooks(const QString title, const QString author)
{
    QVector<Book> results = {};
    if(title.trimmed() == "")
    {
        if(author.trimmed() != "")
        {
            //Search by author
        }
    }
    else if(author.trimmed() == "")
    {
        if(title.trimmed() != "")
        {
            //Search by title
        }
    }
    else
    {
        results.push_back(GetBook(title, author));
    }

    return results;
}

Book LibraryDB::GetBook(const int ISBN)
{

}

Book LibraryDB::GetBook(const QString title, const QString author) const
{

}

int LibraryDB::GetCopiesOfBook(const int ISBN)
{

}

int LibraryDB::GetCopiesOfBook(const QString title, const QString author)
{

}

void LibraryDB::CheckOutBook(const User u, const Book b)
{

}

void LibraryDB::BooksDueBy(QDate date, const QVector<Book> booksDue)
{

}

void LibraryDB::SaveData()
{

}

