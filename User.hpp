#pragma once
#include "UserTiers.hpp"
#include "SystemActions.hpp"

class User
{
public:
    User();
    ~User();
    User &operator=(const User& other);
    User(const User &other);

    UserTiers::Tier getUserTier() const;
    char* getUsername() const;
    unsigned short int getUserAge() const;

    void setUserTier(User &actor, User &subject, UserTiers::Tier newTier);
    void setUsername(User &actor, User &subject,const char* newUsername);


private:
    char* fUsername;
    unsigned short int fAge;
    UserTiers::Tier fUserTier;

    void delUserMem();
    void copyUser(const User& other);
};