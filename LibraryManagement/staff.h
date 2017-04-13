#ifndef STAFF_H
#define STAFF_H

#include "user.h"

class Staff : public UserBase
{
public:
    Staff(QString name, QString addr, QString phoneNumber, QString username);

    bool CanCheckOutBook() override;
    void ReturnBook() override ;
    void CheckOutBook() override;
    void LoadCheckOutData(int checkCount) override;
    int GetCheckedOutBooks();


    template<typename T>
    static bool instanceof(const T *ptr) { return (dynamic_cast<const Staff*>(ptr) != nullptr); }

private:
    Book checkedOut[12];
    int maxCheckout = 12, currentCheckOut;
};

#endif // STAFF_H
