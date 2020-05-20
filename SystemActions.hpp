#pragma once
#include <iostream>
#include <cstring>
#include "UserTiers.hpp"
#include "User.hpp"

class SystemActions
{
public:
    enum Action{
        Nothing,
        Add_post,
        Remove_post,
        Block_user,
        Unblock_user,
        Add_user,
        Remove_user
    };

    void isTheActionAllowed(User actor, SystemActions::Action action, User subject);
};
