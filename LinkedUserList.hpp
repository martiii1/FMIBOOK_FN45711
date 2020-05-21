#pragma once

#include "LinkedUser.hpp"
class LinkedUserList
{
public:
    LinkedUserList();;
    ~LinkedUserList();

    void addUser(const UserData&);

    void changeUserTier(const char* actor,const char* subject, UserTiers::Tier newTier);
private:

    LinkedUser *fPointerToFirstUser;
    LinkedUser *fPointerToLastUser;


    void newUserTier(const char* username, UserTiers::Tier newTier);


};
