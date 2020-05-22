#include "UserData.hpp"
#include <cstring>
#include <iostream>

UserData::UserData()
{
    defaultUserInit();
}

UserTiers::Tier UserData::getUserTier() const
{
    return fUserTier;
}

char *UserData::getUsername() const
{
    return fUsername;
}

unsigned short int UserData::getUserAge() const
{
    return fAge;
}

void UserData::setUserTier(UserTiers::Tier newTier)
{
    fUserTier = newTier;
}

void UserData::setUsername(const char *newUsername)
{
    delete[] fUsername;
    fUsername = new char[strlen(newUsername) + 1];
    strcpy(fUsername, newUsername);
}

UserData::~UserData()
{
    delUserMem();
}

void UserData::delUserMem()
{
    delete[] fUsername;
}

void UserData::copyUser(const UserData &other)
{
    char *tempName = new char[strlen(other.getUsername()) + 1];
    strcpy(tempName, other.getUsername());
    delUserMem();

    fUsername = tempName;
    fUserTier = other.getUserTier();
    fAge = other.fAge;
}

UserData &UserData::operator=(const UserData &other)
{
   if(this != &other)
   {
       delUserMem();
       copyUser(other);
   }
   else
       return *this;
}

UserData::UserData(const UserData &other)
{
    copyUser(other);
}

UserData::UserData(const char *username, UserTiers::Tier userTier, unsigned short userAge)
{
    defaultUserInit();

    setUsername(username);
    fAge = userAge;
    fUserTier = userTier;
}

void UserData::defaultUserInit()
{
    fUsername = nullptr;
    fAge = 0;
    fUserTier = UserTiers::Tier::Nothing;
}

void UserData::printUserData()
{
    std::cout << "Username: " << fUsername << "  is " << fUserTier << "  and is " << fAge << " years old \n";
}
