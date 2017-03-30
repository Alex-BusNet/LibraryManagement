#ifndef STAFF_H
#define STAFF_H

#include "user.h"

class Staff : public UserBase
{
public:
    Staff(QString name, QString addr, QString phoneNumber, QString username);

    bool CanCheckOutBook() override;
    void ReturnBook(const Book &b) override ;
    void CheckOutBook(const Book &b) override;
    void LoadCheckOutData(int index, const Book &b) override;
    void GetCheckedOutBooks(Book (&arr)[12]);


    template<typename T>
    static bool instanceof(const T *ptr) { return (dynamic_cast<const Staff*>(ptr) != nullptr); }

private:
    Book checkedOut[12];
};

#endif // STAFF_H
