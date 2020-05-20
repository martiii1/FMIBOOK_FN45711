#pragma once

#include <iostream>
#include <cstring>
#include "UserTiers.hpp"
#include "UserData.hpp"

class SystemActions
{
public:
    enum Action
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

    static void isTheActionAllowed(UserData &actor, SystemActions::Action action, UserData &subject);

private:
    static bool actionCheck(UserData &actor, SystemActions::Action action, UserData &subject)
};
