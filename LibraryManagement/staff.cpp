#include "staff.h"

Staff::Staff(QString name, int cardNumber, QString addr, int phoneNumber, QString username) :
    UserBase(name, cardNumber, addr, phoneNumber, username)
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

void Staff::CheckOutBook(Book b)
{
    for(int i = 0; i < 12; i++)
    {
        //Find the first open slot in the array
        if(checkedOut[i] == 0)
        {
            //Add the book;
            checkedOut[i] = b;
            break;
        }
    }
}
