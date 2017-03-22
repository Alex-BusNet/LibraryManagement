#ifndef USER_H
#define USER_H

#include <QString>
#include "datatypes.h"

class User
{
public:
    User(QString name, int cardNumber, QString addr, int phoneNumber);

    void SetName(QString n);
    void SetAddress(QString a);
    void SetPhoneNumber(int pn);
    void SetCardNumber(int cn);

    bool CanCheckOutBook();
    void CheckOutBook(Book b);

    void ReturnBook(Book b);

    void GetCheckedOutBooks(const Book arr[]);

private:
    QString name;
    int cardNumber;
    QString address;
    int phoneNumber;
    Book checkedOut[6];

};

#endif // USER_H
