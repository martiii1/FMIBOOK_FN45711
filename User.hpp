#pragma once
#include "UserTiers.hpp"

class User
{
public:
    User();

    UserTiers::Tier getUserTier();
    char* getUsername();
    unsigned short int getUserAge();

private:
    char* fUsername;
    unsigned short int fAge;
    UserTiers::Tier fUserTier;
};