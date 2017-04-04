#include "librarydb.h"
#include <QDebug>
#include <QFile>
#include <QFutureSynchronizer>
#include <QtConcurrent>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QVariantList>
#include <QVariantList>

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
int LibraryDB::LogIn(const QString username, const QString pass)
{
    if(!memberLogins.contains(username))
        return -1;

    QString storedPass = memberLogins.value(username);

    if(storedPass == pass)
        return Authenticate(GetUser(username));

    return -1;
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

Book *LibraryDB::GetBookAt(int index)
{
    return masterList.at(index);
}

Book* LibraryDB::GetBook(const int ISBN)
{
    foreach(Book* b, masterList)
    {
        if(b->ISBN == ISBN)
            return b;
    }

    return masterList.at(0);
}

Book* LibraryDB::GetBook(const QString title, const QString author)
{
    foreach(Book* b, masterList)
    {
        if((b->title == title) && (b->author == author))
            return b;
    }

    return masterList.at(0);
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
                if(Staff::instanceof(u))
                {
                    static_cast<Staff*>(u)->CheckOutBook(*b);
                }
                else
                {
                    static_cast<User*>(u)->CheckOutBook(*b);
                }

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
    qDebug() << "Saving data";
    QFile master("../LibraryManagement/Assets/BookList/master.json");

    if(!master.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open masterList save file");
        return;
    }

    QJsonDocument doc;
    QJsonArray arr;

    //Info tags: ISBN, Book-title, Book-Author, YoP, publisher, image-url-s, image-url-m, image-url-l
    for(int i = 0; i < masterList.size(); i++)
    {
        QJsonObject obj;
        obj["isbn"] = masterList.at(i)->ISBN;
        obj["book-title"] = masterList.at(i)->title;
        obj["book-author"] = masterList.at(i)->author;
        obj["longterm"] = masterList.at(i)->longTerm;
        obj["publisher"] = masterList.at(i)->publisher;
        obj["yop"] = masterList.at(i)->publishYear;

        QJsonArray cArr;
        for(int j = 0; j < masterList.at(i)->copiesAvailable.size(); j++)
        {
            cArr.push_back(masterList.at(i)->copiesAvailable.at(j));
        }
        obj["copies"] = cArr;

        arr.push_back(obj);
    }

    doc.setArray(arr);
    master.write(doc.toJson());
    master.flush();
    master.close();

    QFile regUserFile("../LibraryManagement/Assets/UserLists/regUsers.json");

    if(!regUserFile.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open register users save file");
        return;
    }

    QJsonArray ruArr;

    foreach(UserBase *ub, registeredUsers)
    {
        QJsonObject obj;
        obj["name"] = ub->GetName();
        obj["username"] = ub->GetUsername();
        obj["cardnumber"] = ub->GetCardNumber();
        obj["address"] = ub->GetAddress();
        obj["phonenumber"] = ub->GetPhoneNumber();
        obj["userlevel"] = Authenticate(ub);

        if(obj["userlevel"].toInt() > 0)
        {
            Book arr[12];
            static_cast<Staff*>(ub)->GetCheckedOutBooks(arr);
            QJsonArray bArr;
            for(int i = 0; i < 12; i++)
            {
                bArr.push_back(arr[i].ISBN);
            }

            obj["checkedoutbooks"] = bArr;
        }
        else
        {
            Book arr[6];
            static_cast<User*>(ub)->GetCheckedOutBooks(arr);
            QJsonArray bArr;
            for(int i = 0; i < 6; i++)
            {
                bArr.push_back(arr[i].ISBN);
            }

            obj["checkedoutbooks"] = bArr;
        }

        ruArr.push_back(obj);
    }

    doc.setArray(ruArr);
    regUserFile.write(doc.toJson());
    regUserFile.flush();
    regUserFile.close();

    QFile userLogins("../LIbraryManagement/Assets/UserLists/logins.json");
    if(!userLogins.open(QIODevice::WriteOnly))
    {
        qWarning("Could not open user login save file");
        return;
    }

    QJsonArray ulArr;

    foreach(QString key, memberLogins.keys())
    {
        QJsonObject obj;
        obj["username"] = key;
        obj["password"] = memberLogins.value(key);

        ulArr.push_back(obj);
    }

    doc.setArray(ulArr);
    userLogins.write(doc.toJson());
    userLogins.flush();
    userLogins.close();

    qDebug() << "Save complete";
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

void LibraryDB::ParseBookData()
{

    QFile libFile("../LibraryManagement/Assets/BookList/master.json");

    if(!libFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open file");
        return;
    }

    QByteArray libArr = libFile.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(libArr);
    QJsonArray arr = doc.array();
    Book *b;

    qDebug() << "masterList size:" << arr.size();
    for(int i = 1; i < arr.size(); i++)
    {
        QJsonObject obj = arr.at(i).toObject();

        if(!obj.contains("longterm"))
        {
            obj["longterm"] = false;
        }
        if(!obj.contains("copies"))
        {
            obj["copies"] = QJsonArray{-1, -1, -1};
        }

        b = new Book
        {
            obj["book-title"].toString(),
            obj["book-author"].toString(),
            obj["isbn"].toString().toInt(),
            QVector<int>{-1},
            obj["longterm"].toBool(),
            obj["publisher"].toString(),
            obj["yop"].toInt()
        };

        QJsonArray cArr = obj["copies"].toArray();
        b->copiesAvailable.clear();
        for(int i = 0; i < cArr.size(); i++)
        {
            b->copiesAvailable.push_back(cArr[i].toInt());
        }

        masterList.push_back(b);
    }

    libFile.close();
}

void LibraryDB::ParseUserData()
{
    QFile regUserFile("../LibraryManagement/Assets/UserLists/regUsers.json");

    if(!regUserFile.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open register users save file");
        return;
    }

    QByteArray userArr = regUserFile.readAll();
    QJsonDocument uDoc = QJsonDocument::fromJson(userArr);
    QJsonArray uArr = uDoc.array();
    User* u;
    Staff* s;
    Manager* m;
    int userLvl;

    for(int i = 0; i < uArr.size(); i++)
    {
        QJsonObject obj = uArr[i].toObject();
        userLvl = obj["userlevel"].toInt();

        if(userLvl == 0) //Normal User
        {
            u = new User(
                    obj["name"].toString(),
                    obj["address"].toString(),
                    obj["phonenumber"].toString(),
                    obj["username"].toString());
            u->SetCardNumber(obj["cardnumber"].toInt());

            QJsonArray bArr = obj["checkedoutbooks"].toArray();
            for(int i = 0; i < bArr.size(); i++)
            {
                int ISBN = bArr[i].toInt();
                Book *b = GetBook(ISBN);
                u->LoadCheckOutData(i, *b);
            }

            registeredUsers.push_back(u);
        }
        else if(userLvl == 1) //Staff
        {
            s = new Staff(
                    obj["name"].toString(),
                    obj["address"].toString(),
                    obj["phonenumber"].toString(),
                    obj["username"].toString());
            s->SetCardNumber(obj["cardnumber"].toInt());

            registeredUsers.push_back(s);
            staffMembers.push_back(s);

            QJsonArray bArr = obj["checkedoutbooks"].toArray();
            for(int i = 0; i < bArr.size(); i++)
            {
                int ISBN = bArr[i].toInt();
                Book *b = GetBook(ISBN);
                s->LoadCheckOutData(i, *b);
            }
        }
        else if(userLvl == 2) //Manager
        {
            m = new Manager(
                    obj["name"].toString(),
                    obj["address"].toString(),
                    obj["phonenumber"].toString(),
                    obj["username"].toString());
            m->SetCardNumber(obj["cardnumber"].toInt());

            registeredUsers.push_back(m);
            staffMembers.push_back(m);

            QJsonArray bArr = obj["checkedoutbooks"].toArray();
            for(int i = 0; i < bArr.size(); i++)
            {
                int ISBN = bArr[i].toInt();
                Book *b = GetBook(ISBN);
                m->LoadCheckOutData(i, *b);

            }
        }
    }

    regUserFile.close();

    QFile userLogins("../LibraryManagement/Assets/UserLists/logins.json");
    if(!userLogins.open(QIODevice::ReadOnly))
    {
        qWarning("Could not open user login save file");
        return;
    }

    QByteArray loginArr = userLogins.readAll();
    QJsonDocument lDoc = QJsonDocument::fromJson(loginArr);
    QJsonArray lArr = lDoc.array();

    for(int i = 0; i < lArr.size(); i++)
    {
        QJsonObject obj = lArr[i].toObject();
        memberLogins.insert(obj["username"].toString(), obj["password"].toString());
    }

    userLogins.close();
}

void LibraryDB::ParseDBJson()
{
    //-------------------
    //Load the saved info for the database
    //-------------------

    masterList.push_back(new Book{"Title", "Author", 0, QVector<int>{-1,-1,-1}, false, "Publisher", 0});
    QFutureSynchronizer<void> sync;
    sync.addFuture(QtConcurrent::run(this, LibraryDB::ParseBookData));
    sync.addFuture(QtConcurrent::run(this, LibraryDB::ParseUserData));
    sync.waitForFinished();

    qDebug() << "Parse Complete";
}
