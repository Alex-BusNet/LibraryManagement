#include "userbase.h"

UserBase::UserBase(QString name, QString addr, int phoneNumber, QString username)
{
    this->name = name;
    this->cardNumber = cardNumber;
    this->address = addr;
    this->phoneNumber = phoneNumber;
    this->username = username;
}

void UserBase::SetName(QString n)
{
    this->name = n;
}

void UserBase::SetAddress(QString a)
{
    this->address = a;
}

void UserBase::SetPhoneNumber(int pn)
{
    this->phoneNumber = pn;
}

void UserBase::SetCardNumber(int cn)
{
    this->cardNumber = cn;
}

void UserBase::SetUsername(QString un)
{
    this->username = un;
}

QString UserBase::GetUsername() const
{
    return this->username;
}

QString UserBase::GetName() const
{
    return this->name;
}

QString UserBase::GetAddress() const
{
    return this->address;
}

int UserBase::GetPhoneNumber() const
{
    return this->phoneNumber;
}

int UserBase::GetCardNumber() const
{
    return this->cardNumber;
}

bool UserBase::CanCheckOutBook()
{
    return false;
}

void UserBase::ReturnBook(const Book &b)
{

}

void UserBase::CheckOutBook(const Book &b)
{

}
