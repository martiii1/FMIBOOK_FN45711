#pragma once
#include "UserTiers.hpp"

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

    bool isTheActionAllowed(Action inputAction, UserTiers::Tier userTier);
};
