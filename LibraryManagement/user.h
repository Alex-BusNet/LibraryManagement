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
    void CheckOutBook(const Book &b) override;
    void ReturnBook(const Book &b) override;
    void LoadCheckOutData(int index, const Book &b) override;

    void GetCheckedOutBooks(Book (&arr)[6]);

private:
    Book checkedOut[6];
};

#endif // USER_H
