#ifndef USERBASE_H
#define USERBASE_H

#include <QString>



class UserBase
{
public:
    UserBase(QString name, int cardNumber, QString addr, int phoneNumber, QString username);

    void SetName(QString n);
    void SetAddress(QString a);
    void SetPhoneNumber(int pn);
    void SetCardNumber(int cn);
    void SetUsername(QString un);

    QString GetUsername() const;

    bool operator==(const UserBase &other) { return (other.cardNumber == cardNumber); }

private:
    QString name;
    QString username;
    int cardNumber;
    QString address;
    int phoneNumber;
};

#endif // USERBASE_H
