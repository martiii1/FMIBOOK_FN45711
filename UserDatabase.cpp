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

    std::cout << newUser.getUsername() << " was created. \n";

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
    size_t counterNew = 0;
    size_t counterOld = 0;

    while (counter < fSize)
    {
        if (strcmp(username, fAllUsers[counterOld].getUsername()) == 0)
        {
            std::cout << fAllUsers[counterOld].getUsername() << " was removed. \n";
            counterOld++;
            counter++;
            continue;
        }

        fTempUsers[counterNew] = fAllUsers[counterOld];
        counterOld++;
        counterNew++;
        counter++;
    }

    if (counterNew < counterOld)
    {
        delete[] fAllUsers; // TODO
        fAllUsers = fTempUsers;
        fSize--;
    }
    else
    {
        delete[] fTempUsers;
        throw std::exception("The user wasn't found and wasn't deleted, check if you entered the correct username. \n");
    }

}

unsigned int UserDatabase::getSize()
{
    return fSize;
}

bool UserDatabase::doesUsernameExist(const char *username)
{
    for (int i = 0; i < fSize; i++)
    {
        if (strcmp(fAllUsers[i].getUsername(), username) == 0)
        {
            return true;
        }
    }
    return false;
}

void UserDatabase::blockUser(const char *username)
{
    bool userFound = false;

    for (int i = 0; i < fSize; i++)
    {
        if (strcmp(fAllUsers[i].getUsername(), username) == 0)
        {
            userFound = true;
            fAllUsers[i].setUserTier(UserTiers::Tier::Banned_user);
        }
    }

    if(!userFound)
        throw std::exception("User not found! \n");
}

void UserDatabase::changeUsername(const char *oldUsername, const char *newUsername)
{

    bool userFound = false;

    for (int i = 0; i < fSize; i++)
    {
        if (strcmp(fAllUsers[i].getUsername(), oldUsername) == 0)
        {
            userFound = true;
            fAllUsers[i].setUsername(newUsername);
        }
    }

    if(!userFound)
        throw std::exception("User not found! \n");
}
