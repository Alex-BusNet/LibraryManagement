#ifndef USER_H
#define USER_H

#include <QString>
#include "datatypes.h"
#include "userbase.h"

class User : public UserBase
{
public:
    User(QString name, int cardNumber, QString addr, int phoneNumber, QString username);

    bool CanCheckOutBook() override;
    void CheckOutBook(const Book &b) override;
    void ReturnBook(const Book &b) override;

    void GetCheckedOutBooks(const Book arr[]);

private:
    Book checkedOut[6];
};

#endif // USER_H
