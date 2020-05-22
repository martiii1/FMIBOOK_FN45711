#pragma once

#include "UserData.hpp"

class UserDatabase
{

public:
    UserDatabase();
    ~UserDatabase();

private:
    UserData *fAllUsers;
    unsigned int fCapacity;
    unsigned int fSize;

    UserData *allocateUserDatabase(unsigned int newCapacity);

    void resizeAllUsers(unsigned int newCapacity);
    void delMem();
};
