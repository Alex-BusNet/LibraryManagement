#ifndef USERBASE_H
#define USERBASE_H

#include <QString>
#include "datatypes.h"

class UserBase
{
public:
    UserBase(QString name, int cardNumber, QString addr, int phoneNumber, QString username);

    void SetName(QString n);
    void SetAddress(QString a);
    void SetPhoneNumber(int pn);
    void SetCardNumber(int cn);
    void SetUsername(QString un);

    virtual QString GetUsername() const;
    virtual QString GetName() const;
    virtual QString GetAddress() const;
    virtual int GetPhoneNumber() const;
    virtual int GetCardNumber() const;

    virtual bool CanCheckOutBook();
    virtual void ReturnBook(const Book &b);
    virtual void CheckOutBook(const Book &b);

    bool operator==(const UserBase &other) { return (other.cardNumber == cardNumber); }



private:
    QString name;
    QString username;
    int cardNumber;
    QString address;
    int phoneNumber;
};

#endif // USERBASE_H
