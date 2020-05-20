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
