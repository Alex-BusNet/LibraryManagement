#ifndef MANAGER_H
#define MANAGER_H

#include "staff.h"

class Manager : public Staff
{
public:
    Manager(QString name, QString addr, QString phoneNumber, QString username) :
        Staff(name, addr, phoneNumber, username){}
    template<typename T>
    static bool instanceof(const T *ptr) { return (dynamic_cast<const Manager*>(ptr) != nullptr); }
};

#endif // MANAGER_H
