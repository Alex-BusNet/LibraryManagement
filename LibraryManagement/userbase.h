#ifndef USERBASE_H
#define USERBASE_H

#include <QString>
#include "datatypes.h"

class UserBase
{
public:
    UserBase(QString name, QString addr, QString phoneNumber, QString username);

    void SetName(QString n);
    void SetAddress(QString a);
    void SetPhoneNumber(QString pn);
    void SetCardNumber(int cn);
    void SetUsername(QString un);

    virtual QString GetUsername() const;
    virtual QString GetName() const;
    virtual QString GetAddress() const;
    virtual QString GetPhoneNumber() const;
    virtual int GetCardNumber() const;

    virtual bool CanCheckOutBook();
    virtual void ReturnBook();
    virtual void CheckOutBook();
    virtual int GetCheckedOutBooks();
    virtual void LoadCheckOutData(int checkCount);

    bool operator==(const UserBase &other) { return (other.cardNumber == cardNumber); }



private:
    QString name;
    QString username;
    int cardNumber;
    QString address;
    QString phoneNumber;
};

#endif // USERBASE_H
