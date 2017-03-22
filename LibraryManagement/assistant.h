#ifndef ASSISTANT_H
#define ASSISTANT_H

#include "staff.h"

class Assistant : public Staff
{
public:
    Assistant(QString name, int cardNumber, QString addr, int phoneNumber, QString username);

    void AddBook(Book b);
    void RemoveBook(Book b);

    void AddUser(User u);
    void RemoveUser(User u);
};

#endif // ASSISTANT_H
