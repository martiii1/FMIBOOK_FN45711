#include "UserDatabase.hpp"

UserData* UserDatabase::allocateUserDatabase(unsigned int newCapacity)
{
    UserData* tempPointer = new UserData[newCapacity];
    fCapacity = newCapacity;
    return tempPointer;
}

void UserDatabase::delMem()
{
    delete [] fAllUsers;
}

void UserDatabase::resizeAllUsers(unsigned int newCapacity)
{
    UserData* tempPointer = new UserData[newCapacity];

    for(int i=0;i<fSize;i++)
    {
        tempPointer[i] = fAllUsers[i];
    }
    delMem();

    fAllUsers = tempPointer;
    fCapacity = newCapacity;
}

UserDatabase::~UserDatabase()
{
    delMem();
}
