#pragma once
#include "UserTiers.hpp"
#include "ActionPermissions.hpp"

class UserData
{
public:
    UserData();
    ~UserData();
    UserData &operator=(const UserData& other);
    UserData(const UserData &other);

    UserTiers::Tier getUserTier() const;
    char* getUsername() const;
    unsigned short int getUserAge() const;

    void setUserTier(UserTiers::Tier newTier);
    void setUsername(const char *newUsername);


private:
    char* fUsername;
    unsigned short int fAge;
    UserTiers::Tier fUserTier;

    void delUserMem();
    void copyUser(const UserData& other);
};