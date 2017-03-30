#ifndef MANAGER_H
#define MANAGER_H

#include "staff.h"

class Manager : public Staff
{
public:
    Manager(QString name, QString addr, QString phoneNumber, QString username);

    void AddBook(Book b);
    void RemoveBook(Book b);

    void AddUser(User u);
    void RemoveUser(User u);

    template<typename T>
    static bool instanceof(const T *ptr) { return (dynamic_cast<const Manager*>(ptr) != nullptr); }
};

#endif // MANAGER_H
