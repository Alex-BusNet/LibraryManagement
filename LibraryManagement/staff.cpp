#include "staff.h"
#include <QDebug>

Staff::Staff(QString name, int cardNumber, QString addr, int phoneNumber, QString username) :
    UserBase(name, cardNumber, addr, phoneNumber, username)
{
    for(int i = 0; i < 12; i++)
    {
        checkedOut[i].ISBN = 0;
    }
}

bool Staff::CanCheckOutBook()
{
    if(checkedOut[11].ISBN != 0)
    {
        qDebug() << this->GetName() << "Cannot check out anymore books";
        return false;
    }

    qDebug() << this->GetName() << "Can check out more books";
    return true;
}

void Staff::ReturnBook(const Book &b)
{
    for(int i = 0; i < 12; i++)
    {
        if(checkedOut[i] == b)
        {
            int j = i + 1;
            for(; j < 12; j++)
            {
                if(checkedOut[j].ISBN != 0)
                    checkedOut[j - 1] = checkedOut[j];
                else
                    break;
            }

            checkedOut[j].ISBN = 0;
            break;
        }
    }
}

void Staff::CheckOutBook(const Book &b)
{
    for(int i = 0; i < 12; i++)
    {
        qDebug() << "checkedOut[" << i << "].ISBN == 0" << (checkedOut[i].ISBN == 0) << "ISBN:" << checkedOut[i].ISBN;
        if(checkedOut[i].ISBN == 0)
        {
            qDebug() << "Checking out" << b.title << "to" << this->GetName() << "in slot" << i;
            checkedOut[i] = b;
            qDebug() << this->GetName() << "now has" << checkedOut[i].title << "new ISBN:" << checkedOut[i].ISBN;
            break;
        }
    }

}
