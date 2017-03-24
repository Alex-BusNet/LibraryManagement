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
    static int memberNumber = 000000000;
    if(memberLogins.contains(u->GetUsername()))
    {
        return false;
    }
    memberNumber++;
    u->SetCardNumber(memberNumber);
    qDebug() << u->GetUsername() << memberNumber;
    registeredUsers.push_back(u);
    memberLogins.insert(u->GetUsername(), pass);

    return true;
}

void LibraryDB::RemoveUser(UserBase *u)
{

}

QVector<UserBase *> LibraryDB::GetAllUsers()
{
    return this->registeredUsers;
}

UserBase *LibraryDB::GetUser(QString username)
{
    foreach(UserBase* u, registeredUsers)
    {
        if(u->GetUsername() == username)
            return u;
    }

    return NULL;
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
 * Returns false if passwords do not match OR
 * username is not in list of registered users.
 */
bool LibraryDB::LogIn(const QString username, const QString pass)
{
    if(!memberLogins.contains(username))
        return false;

    QString storedPass = memberLogins.value(username);

    if(storedPass == pass)
        return true;

    return false;
}

/*
 * Authenticate takes in user object and checks to see
 * if they are in the staff member list.
 *
 * Returns false if non-existent.
 */
int LibraryDB::Authenticate(UserBase *s)
{
    qDebug() << s->GetName() << "is a staff object:" << Staff::instanceof(s);
    if(Staff::instanceof(s))
    {
        qDebug() << s->GetName() << "is a registered staff member:" << staffMembers.contains(static_cast<Staff*>(s));
        if(staffMembers.contains(static_cast<Staff*>(s)))
        {
            if(Manager::instanceof(s))
            {
                //Manager level access
                return 2;
            }

            //Staff level access
            return 1;
        }
    }

    //User level access
    return 0;
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
    return Book{"", "", 0, QVector<int>{0}};
}

Book LibraryDB::GetBook(const QString title, const QString author) const
{
    return Book{"", "", 0, QVector<int>{0}};
}

QVector<Book> LibraryDB::GetAllBooks()
{
    return this->masterList;
}

int LibraryDB::GetCopiesOfBook(const int ISBN)
{
    return 0;
}

int LibraryDB::GetCopiesOfBook(const QString title, const QString author)
{
    return 0;
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

