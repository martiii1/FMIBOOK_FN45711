#pragma once

#include "UserData.hpp"

class UserDatabase
{
public:
    UserDatabase();

    UserDatabase(unsigned int initialCapacity);

    UserDatabase(const UserDatabase &other);

    UserDatabase &operator=(const UserDatabase &other);

    ~UserDatabase();

    void addUser(const UserData& newUser);

    void printAllUsers();

    UserTiers::Tier getTierFromUsername(const char *username);

    void removeUser(const char* username);

    unsigned int getSize();

    bool doesUsernameExist(const char* username);

    void blockUser(const char* username);

    void changeUsername(const char* oldUsername, const char *newUsername);

private:
    UserData *fAllUsers;
    unsigned int fCapacity;
    unsigned int fSize;

    UserData *allocateUserDatabase(unsigned int newCapacity);

    void resizeAllUsers(unsigned int newCapacity);

    void delMem();

    void copyUserDatabase(const UserDatabase &other);
};
