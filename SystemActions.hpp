#pragma once

#include <iostream>
#include <cstring>
#include "UserTiers.hpp"
#include "UserData.hpp"

class SystemActions
{
public:
    enum Actions
    {
        Nothing,
        Add_post,
        Remove_post,
        Change_username,
        Block_user,
        Unblock_user,
        Add_user,
        Remove_user,
        Change_tier
    };

   static bool actionCheck(const UserData &actor, Actions actions,const UserData &subject);

   static void isTheActionAllowed(const UserData &actor, Actions action, const UserData &subject);

};
