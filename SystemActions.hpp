#pragma once

#include <iostream>
#include <cstring>
#include "UserTiers.hpp"
#include "User.hpp"

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

    void isTheActionAllowed(User &actor, SystemActions::Action action, User &subject);

private:
    bool actionCheck(User &actor, SystemActions::Action action, User &subject)
};
