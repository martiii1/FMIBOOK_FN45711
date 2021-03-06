#pragma once
#include "UserTiers.hpp"


class UserData
{
public:
    UserData();
    UserData(const char* username, UserTiers::Tier userTier, unsigned short int userAge);
    ~UserData();
    UserData &operator=(const UserData& other);
    UserData(const UserData &other);


    UserTiers::Tier getUserTier() const;
    char* getUsername() const;
    unsigned short int getUserAge() const;

    void setUserTier(UserTiers::Tier newTier);
    void setUsername(const char *newUsername);

    void printUserData();


private:
    char* fUsername;
    unsigned short int fAge;
    UserTiers::Tier fUserTier;

    void delUserMem();
    void copyUser(const UserData& other);
    void defaultUserInit();
};