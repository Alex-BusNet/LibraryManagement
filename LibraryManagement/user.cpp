#include "user.h"


User::User(QString name, QString addr, int phoneNumber, QString username) :
    UserBase(name, addr, phoneNumber, username)
{
    for(int i = 0; i < 6; i++)
    {
        checkedOut[i] = 0;
    }
}

/*
 * CanCheckOut() checks if the last slot
 * in the array is filled. If it is, then
 * the function returns false; otherwise
 * the function returns true. The array is
 * 'sorted' so that when a book is returned,
 * the empty slot is moved to the end.
 */
bool User::CanCheckOutBook()
{
    if(checkedOut[5] == 0)
    {
        return false;
    }

    return true;
}

void User::CheckOutBook(const Book &b)
{
    for(int i = 0; i < 6; i++)
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

/*
 * ReturnBook() searches through the array of
 * checked out books to find the book being returned.
 * When it does, all books behind it in the array are
 * shifted up one index. The shifting stops when the
 * end of the array is reached, or when the next book in
 * the array is NULL. Once the shift operation has finished,
 * the book at the last indexed checked is set to NULL
 * regardless if it is already NULL.
 */
void User::ReturnBook(const Book &b)
{
    for(int i = 0; i < 6; i++)
    {
        //Check if the book at this location is the book being returned
        if(checkedOut[i] == b)
        {
            //Move every book in the array whose
            // index is greater than i up one index;
            int j = i + 1;
            for(; j < 6; j++)
            {
                //Check to see if there is a book in the next slot
                if(checkedOut[j].ISBN != 0)
                    checkedOut[j - 1] = checkedOut[j];
                else
                    break;
            }

            //Clear the book at j.
            checkedOut[j] = Book{"", "", 0, QVector<int>{0}, false};
            break;
        }
    }
}

void User::LoadCheckOutData(int index, const Book &b)
{
    checkedOut[index] = b;
}

void User::GetCheckedOutBooks(const Book arr[])
{
    arr = checkedOut;
}
