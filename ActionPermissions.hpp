#pragma once
#include "SystemActions.hpp"
#include "UserTiers.hpp"
#include "UserData.hpp"
#include "LinkedUser.hpp"

class ActionPermissions
{
public:
   static void isTheActionAllowed(const char* actorName, UserTiers::Tier actorTier, SystemActions::Actions action, const char* subjectName,UserTiers::Tier subjectTier);

private:
    static bool actionCheck(const char* actorName, UserTiers::Tier actorTier, SystemActions::Actions action, const char* subjectName,UserTiers::Tier subjectTier);

};
