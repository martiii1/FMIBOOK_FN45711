#include "UserDatabase.hpp"
#include <iostream>

UserData *UserDatabase::allocateUserDatabase(unsigned int newCapacity)
{
    UserData *tempPointer = new UserData[newCapacity];
    fCapacity = newCapacity;
    return tempPointer;
}

void UserDatabase::delMem()
{
    delete[] fAllUsers;
}

void UserDatabase::resizeAllUsers(unsigned int newCapacity)
{
    UserData *tempPointer = new UserData[newCapacity];

    for (int i = 0; i < fSize; i++)
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

UserDatabase::UserDatabase()
{
    fSize = 0;
    fCapacity = 10;
    fAllUsers = allocateUserDatabase(fCapacity);
}

UserDatabase::UserDatabase(unsigned int initialCapacity)
{
    fSize = 0;
    fCapacity = initialCapacity;
    fAllUsers = allocateUserDatabase(fCapacity);
}

UserDatabase::UserDatabase(const UserDatabase &other)
{
    copyUserDatabase(other);
}

void UserDatabase::copyUserDatabase(const UserDatabase &other)
{
    delMem();
    fAllUsers = allocateUserDatabase(other.fCapacity);
    fSize = other.fSize;

    for (int i = 0; i < fSize; i++)
    {
        fAllUsers[i] = other.fAllUsers[i];
    }
}

UserDatabase &UserDatabase::operator=(const UserDatabase &other)
{
    if (this != &other)
        copyUserDatabase(other);

    return *this;
}

void UserDatabase::addUser(const UserData &newUser)
{
    if (fSize >= fCapacity - 1)
        resizeAllUsers(fCapacity * 2);

    fAllUsers[fSize] = newUser;
    fSize++;

}

void UserDatabase::printAllUsers()
{
    for (int i = 0; i < fSize; i++)
    {
        fAllUsers[i].printUserData();
    }

}

UserTiers::Tier UserDatabase::getTierFromUsername(const char *username)
{
    for (int i = 0; i < fSize; i++)
    {
        if (strcmp(fAllUsers[i].getUsername(), username) == 0)
            return fAllUsers[i].getUserTier();
    }

    return UserTiers::Tier::Nothing;
}

void UserDatabase::removeUser(const char *username)
{
    UserData *fTempUsers = new UserData[fCapacity];
    size_t counter = 0;

    // fSize starts at 0 so by removing one user the counter should go to ( fSize - 1 ) - 1 (the removed user)
    while (counter != fSize - 2)
    {
        if (strcmp(username, fAllUsers[counter].getUsername()) == 0)
            continue;

        fTempUsers[counter] = fAllUsers[counter];
        counter++;
    }

}

unsigned int UserDatabase::getSize()
{
    return fSize;
}
