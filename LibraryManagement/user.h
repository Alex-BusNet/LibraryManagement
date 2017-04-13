#ifndef USER_H
#define USER_H

#include <QString>
#include "datatypes.h"
#include "userbase.h"

class User : public UserBase
{
public:
    User(QString name, QString addr, QString phoneNumber, QString username);

    bool CanCheckOutBook() override;
    void CheckOutBook() override;
    void ReturnBook() override;
    int GetCheckedOutBooks() override;
    void LoadCheckOutData(int checkCount) override;

private:
    Book checkedOut[6];
    int maxCheckout = 6, currentCheckOut;
};

#endif // USER_H
