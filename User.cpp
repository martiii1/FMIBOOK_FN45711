#include "User.hpp"

User::User()
{
    fUsername = nullptr;
    fAge = 0;
    fUserTier = UserTiers::Tier::Nothing;
}

UserTiers::Tier User::getUserTier()
{
    return fUserTier;
}

char *User::getUsername()
{
    return fUsername;
}

unsigned short int User::getUserAge()
{
    return fAge;
}

void User::setUserTier(User &actor, User &subject, UserTiers::Tier newTier)
{
    SystemActions::isTheActionAllowed(actor, SystemActions::Action::Change_tier, subject);

    subject.fUserTier = newTier;
}

void User::setUsername(User &actor, User &subject, const char *newUsername)
{
    SystemActions::isTheActionAllowed(actor, SystemActions::Action::Change_username, subject);

    delete[] fUsername;
    fUsername = new char[strlen(newUsername) + 1];
    strcpy(fUsername, newUsername);
}

User::~User()
{
    delUserMem();
}

void User::delUserMem()
{
    delete[] fUsername;
}

void User::copyUser(User &other)
{
    char *tempName = new char[strlen(other.getUsername()) + 1];

    delUserMem();

    strcpy(fUsername, other.getUsername());
    fUserTier =
}
