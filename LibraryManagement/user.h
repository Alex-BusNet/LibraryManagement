#ifndef USER_H
#define USER_H

#include <QString>
#include "datatypes.h"
#include "userbase.h"

class User : public UserBase
{
public:
    User(QString name, int cardNumber, QString addr, int phoneNumber, QString username);

    bool CanCheckOutBook();
    void CheckOutBook(Book b);

    void ReturnBook(Book b);

    void GetCheckedOutBooks(const Book arr[]);

    template<typename T>
    static bool instanceof(const T *ptr) { return (dynamic_cast<const User*>(ptr) != nullptr); }

private:
    Book checkedOut[6];
};

#endif // USER_H
