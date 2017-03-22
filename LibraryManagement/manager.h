#ifndef MANAGER_H
#define MANAGER_H

#include "assistant.h"

class Manager : public Assistant
{
public:
    Manager(QString name, int cardNumber, QString addr, int phoneNumber, QString username);
};

#endif // MANAGER_H
