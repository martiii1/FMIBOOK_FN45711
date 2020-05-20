#include "UserData.hpp"

UserData::UserData()
{
    fUsername = nullptr;
    fAge = 0;
    fUserTier = UserTiers::Tier::Nothing;
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

void UserData::setUserTier(UserData &actor, UserData &subject, UserTiers::Tier newTier)
{
    SystemActions::isTheActionAllowed(actor, SystemActions::Actions::Change_tier, subject);

    subject.fUserTier = newTier;
}

void UserData::setUsername(UserData &actor,UserData &subject, char *newUsername)
{
    SystemActions::isTheActionAllowed(actor, SystemActions::Actions::Change_username, subject);

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

    delUserMem();

    strcpy(fUsername, other.getUsername());
    fUserTier = other.getUserTier();
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
