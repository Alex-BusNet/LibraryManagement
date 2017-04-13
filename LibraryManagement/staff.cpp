#include "staff.h"
#include "librarydb.h"
#include <QDebug>

Staff::Staff(QString name, QString addr, QString phoneNumber, QString username) :
    UserBase(name, addr, phoneNumber, username)
{
    for(int i = 0; i < 12; i++)
    {
        checkedOut[i] = (*(LibraryDB::instance()->GetBookAt(0)));
    }
}

bool Staff::CanCheckOutBook()
{
    if(checkedOut[11] != 0)
    {
        qDebug() << this->GetName() << "Cannot check out anymore books";
        return false;
    }

    qDebug() << this->GetName() << "Can check out more books";
    return true;
}

void Staff::ReturnBook()
{
    if(maxCheckout > 0)
        currentCheckOut--;
//    for(int i = 0; i < 12; i++)
//    {
//        if(checkedOut[i] == b)
//        {
//            int j = i + 1;
//            for(; j < 12; j++)
//            {
//                if(checkedOut[j].ISBN != 0)
//                    checkedOut[j - 1] = checkedOut[j];
//                else
//                    break;
//            }

//            checkedOut[j] = (*(LibraryDB::instance()->GetBookAt(0)));
//            break;
//        }
//    }
}

void Staff::CheckOutBook()
{
    if(currentCheckOut != maxCheckout)
        currentCheckOut++;
//    for(int i = 0; i < 12; i++)
//    {
//        qDebug() << "checkedOut[" << i << "].ISBN == 0" << (checkedOut[i].ISBN == 0) << "ISBN:" << checkedOut[i].ISBN;
//        if(checkedOut[i].ISBN == 0)
//        {
//            qDebug() << "Checking out" << b.title << "to" << this->GetName() << "in slot" << i;
//            checkedOut[i] = b;
//            qDebug() << this->GetName() << "now has" << checkedOut[i].title << "new ISBN:" << checkedOut[i].ISBN;
//            break;
//        }
//    }

}

void Staff::LoadCheckOutData(int checkCount)
{
    currentCheckOut = checkCount;
}

int Staff::GetCheckedOutBooks()
{
    return currentCheckOut;
}
