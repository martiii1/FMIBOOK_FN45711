#pragma once

#include "LinkedUser.hpp"
#include "ActionPermissions.hpp"

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


    UserTiers::Tier getTierFromUsername(const char* username);


    void newUserTier(const char* username, UserTiers::Tier newTier);

    void permissionChecker(const char* actor,const char* subject, SystemActions::Actions action);


};
