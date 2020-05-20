#pragma once
#include "UserTiers.hpp"
#include "SystemActions.hpp"

class User
{
public:
    User();
    ~User();

    UserTiers::Tier getUserTier();
    char* getUsername();
    unsigned short int getUserAge();

    void setUserTier(User &actor, User &subject, UserTiers::Tier newTier);
    void setUsername(User &actor, User &subject,const char* newUsername);


private:
    char* fUsername;
    unsigned short int fAge;
    UserTiers::Tier fUserTier;

    void delUserMem();
    void copyUser(User& other);
};