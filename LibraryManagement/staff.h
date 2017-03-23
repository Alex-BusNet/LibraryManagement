#ifndef STAFF_H
#define STAFF_H

#include "user.h"

class Staff : public UserBase
{
public:
    Staff(QString name, int cardNumber, QString addr, int phoneNumber, QString username);

    bool CanCheckOutBook();
    void ReturnBook(Book b);
    void CheckOutBook(Book b);

    template<typename T>
    static bool instanceof(const T *ptr) { return (dynamic_cast<const Staff*>(ptr) != nullptr); }

private:
    Book checkedOut[12];
};

#endif // STAFF_H
