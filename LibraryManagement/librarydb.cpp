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

    registeredUsers.push_back(u);
    memberLogins.insert(u->GetUsername(), pass);

    return true;
}

void LibraryDB::RemoveUser(int index)
{
    if(index < registeredUsers.size())
    {
        registeredUsers.removeAt(index);
    }
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

UserBase *LibraryDB::GetUser(int userNumber)
{
    foreach(UserBase* u, registeredUsers)
    {
        if(u->GetCardNumber() == userNumber)
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

/*
 * Removes the staff member at the specified index from the
 * staffMembers QVector. This fuction does not remove them from
 * the registered users vector.
 *
 * index is found by taking the row number from the QTableWidget
 * in the manager's GUI.
 */
void LibraryDB::RemoveStaff(int index)
{
    if(index < staffMembers.size())
    {
        staffMembers.removeAt(index);
    }
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

void LibraryDB::AddBook(Book *b)
{
    masterList.push_back(b);
}

/*
 * Removed the book at the selected book from the masterList.
 * This function removes a book completely from the master list.
 * To remove a copy of a book, use the EditBook( ) function
 *
 * index is found by taking the row number from the QTableWidget
 * in the manager's GUI.
 */
void LibraryDB::RemoveBook(int index)
{
    if(index < masterList.size())
    {
        //Keep a copy of any removed books in case
        // book was accidentally removed
        oldBooks.push_back(masterList.at(index));
        masterList.removeAt(index);
    }
}

/*
 * Edit book takes in the index of the book to be edited,
 * and a book object that is to replace the existing struct.
 *
 * index is found by taking the row number from the QTableWidget
 * in the manager's GUI.
 */
void LibraryDB::EditBook(int index, Book *editedBook)
{
    if(index < masterList.size())
    {
        masterList[index] = editedBook;
    }
}

QVector<Book*> LibraryDB::GetBooks(const QString title, const QString author)
{
    QVector<Book*> results = {};
    if(title.trimmed() == "")
    {
        if(author.trimmed() != "")
        {
            foreach(Book* b, masterList)
            {
                if(b->author == author)
                    results.push_back(b);
            }
        }
    }
    else if(author.trimmed() == "")
    {
        if(title.trimmed() != "")
        {
            foreach(Book *b, masterList)
            {
                if(b->title == title)
                    results.push_back(b);
            }
        }
    }
    else
    {
        results.push_back(GetBook(title, author));
    }

    return results;
}

Book* LibraryDB::GetBook(const int ISBN)
{
    foreach(Book* b, masterList)
    {
        if(b->ISBN == ISBN)
            return b;
    }

    return new Book{"", "", 0, QVector<int>{0}, false};
}

Book* LibraryDB::GetBook(const QString title, const QString author)
{
    foreach(Book* b, masterList)
    {
        if((b->title == title) && (b->author == author))
            return b;
    }

    return new Book{"", "", 0, QVector<int>{0}, false};
}

QVector<Book*> LibraryDB::GetAllBooks()
{
    return this->masterList;
}

int LibraryDB::GetCopiesOfBook(const int ISBN)
{
    Book* b = GetBook(ISBN);
    int count = 0;

    if(b->ISBN != 0)
    {
        foreach(int i, b->copiesAvailable)
        {
            if(i == -1)
            {
                count++;
            }
        }
    }

    return count;
}

int LibraryDB::GetCopiesOfBook(const QString title, const QString author)
{
    Book* b = GetBook(title, author);
    int count = 0;

    if(b->ISBN != 0)
    {
        foreach(int i, b->copiesAvailable)
        {
            if(i == -1)
            {
                count++;
            }
        }
    }

    return count;
}

void LibraryDB::ReturnBook(int ISBN)
{
    foreach(BookReciept *br, checkedOutBooks)
    {
        if(br->ISBN == ISBN)
        {
            int uNum = br->userNo;
            UserBase* u = GetUser(uNum);
            Book *b = GetBook(br->ISBN);

            for(int i = 0; i < b->copiesAvailable.size(); i++)
            {
                if(b->copiesAvailable.at(i) == uNum)
                {
                    b->copiesAvailable[i] = -1;

                    for(int j = i + 1; j < b->copiesAvailable.size(); j++)
                    {
                        if((j + 1) < b->copiesAvailable.size())
                        {
                            //Shift all currently checked out copies up one index.
                            b->copiesAvailable[j] = b->copiesAvailable[j + 1];
                        }
                        else
                        {
                            //The last copy in the vector becomes available.
                            b->copiesAvailable[j] = -1;
                        }
                    }
                }
            }

            u->ReturnBook(*b);
        }
    }
}

/*
 * CheckOutBook is used to checkout books that have not been placed on hold.
 * This function adds the user's card number to the book's copiesAvailable vector
 * and checks out the book to the user if the function was not called by ReserveBook()
 */
void LibraryDB::CheckOutBook(UserBase *u, Book *b, bool needsReminder, bool isReservation)
{
    foreach(int i, b->copiesAvailable)
    {
        //-1 indicates an available copy
        if(i == -1)
        {
            //Update copiesAvailable to indicate who checked out the book
            i = u->GetCardNumber();

            if(!isReservation)
            {
                //Add the book to the user's checkedOut array
                u->CheckOutBook(*b);

                //Get the return date for the book
                QDate dueDate = QDate::currentDate();
                if(b->longTerm)
                    dueDate.addDays(28); // 4 weeks
                else
                    dueDate.addDays(7); // 1 week

                checkedOutBooks.push_back(new BookReciept{u->GetCardNumber(), b->ISBN, dueDate, needsReminder});
            }

            SortCheckOutBooks();
            break;
        }
    }

}

QVector<BookReciept*> LibraryDB::BooksDueBy(QDate date) const
{
    QVector<BookReciept*> booksDue;
    foreach(BookReciept* br, checkedOutBooks)
    {
        if(br->dateDue <= date)
        {
            booksDue.push_back(br);
        }
    }

    return booksDue;
}

/*
 * ReserveBook functions similarly to CheckOutBook with the exception
 * of adding the book to the user's checked out array.
 */
void LibraryDB::ReserveBook(UserBase *u, Book *b, QDate pickupDate)
{
    BookReciept *br = new BookReciept{u->GetCardNumber(), b->ISBN, pickupDate, false};
    reservedBooks.push_back(br);
    CheckOutBook(u, b, false, true);
}

QVector<BookReciept*> LibraryDB::GetReservation(const int userNumber)
{
    QVector<BookReciept*> reservations;
    foreach(BookReciept *br, reservedBooks)
    {
        if(br->userNo == userNumber)
        {
            reservations.push_back(br);
        }
    }

    return reservations;
}

/*
 * FulfillReservation is used to complete the checkout process when a user
 * has already reserved a book.
 */
void LibraryDB::FulfillReservation(BookReciept *br)
{
    checkedOutBooks.push_back(br);
    reservedBooks.removeAll(br);
    UserBase* u = GetUser(br->userNo);
    u->CheckOutBook(*(GetBook(br->ISBN)));
}

void LibraryDB::SaveData()
{

}

void LibraryDB::SortCheckOutBooks()
{
    BookReciept* first, *second, *temp;
    for(int i = 0; i < checkedOutBooks.size(); i++)
    {
        first = checkedOutBooks.at(i);
        for(int j = i + 1; j < checkedOutBooks.size(); j++)
        {
            second = checkedOutBooks.at(j);
            if(second->dateDue < first->dateDue)
            {
                temp = first;
                first = second;
                second = temp;
            }
        }
    }
}

