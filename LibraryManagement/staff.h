#ifndef STAFF_H
#define STAFF_H

#include "user.h"

class Staff : public User
{
public:
    Staff(QString name, int cardNumber, QString addr, int phoneNumber);

    bool CanCheckOutBook();
    void ReturnBook(Book b);

private:
    Book checkedOut[12];
};

#endif // STAFF_H
