#include "staff.h"

Staff::Staff(QString name, int cardNumber, QString addr, int phoneNumber) :
    User(name, cardNumber, addr, phoneNumber)
{

}

bool Staff::CanCheckOutBook()
{
    if(checkedOut[11] == NULL)
    {
        return false;
    }

    return true;
}

void Staff::ReturnBook(Book b)
{
    for(int i = 0; i < 12; i++)
    {
        if(checkedOut[i] == b)
        {
            int j = i + 1;
            for(; j < 12; j++)
            {
                if(checkedOut[j] != NULL)
                    checkedOut[j - 1] = checkedOut[j];
                else
                    break;
            }

            checkedOut[j] = NULL;
            break;
        }
    }
}
