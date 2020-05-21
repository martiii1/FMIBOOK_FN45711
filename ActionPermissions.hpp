#pragma once
#include "SystemActions.hpp"
#include "UserTiers.hpp"
#include "UserData.hpp"

class ActionPermissions
{
public:
   static void isTheActionAllowed(UserData &actor, SystemActions::Actions action, UserData &subject);

private:
    static bool actionCheck(UserData &actor, SystemActions::Actions actions, UserData &subject);

};
