#include "ActionPermissions.hpp"

bool ActionPermissions::actionCheck(const char *actorName, UserTiers::Tier actorTier, SystemActions::Actions action,
                                    const char *subjectName, UserTiers::Tier subjectTier)
{

    switch (action)
    {
        case SystemActions::Actions::Nothing:                                    // Invalid action
            return false;

        case SystemActions::Actions::Add_post:                                   // Adding post
            return actorTier >= UserTiers::Tier::Basic_User;

        case SystemActions::Actions::Remove_post:                                // Removing post
            if (actorTier >= UserTiers::Tier::Moderator)
                return true;
            else
                return ((actorTier >= UserTiers::Tier::Basic_User) &&
                        strcmp(actorName, subjectName) == 0);

        case SystemActions::Actions::Change_username:                            // Change username
            return true;

        case SystemActions::Actions::Block_user:                                // Block user
            return actorTier >= UserTiers::Tier::Moderator;

        case SystemActions::Actions::Unblock_user:                              // Unblock user
            return actorTier >= UserTiers::Tier::Moderator;

        case SystemActions::Actions::Add_user:                                   // Add user
            return actorTier >= UserTiers::Admin;

        case SystemActions::Actions::Remove_user:                                // Remove user
            return actorTier >= UserTiers::Admin;

        case SystemActions::Actions::Change_tier:                                // Change user tier
            return actorTier >= UserTiers::Admin;
    }

    return false;

}


void
ActionPermissions::isTheActionAllowed(const char *actorName, UserTiers::Tier actorTier, SystemActions::Actions action,
                                      const char *subjectName, UserTiers::Tier subjectTier)
{

    if (action == SystemActions::Actions::Nothing)
        throw std::exception("Invalid action, try again! \n");

    //if(!actionCheck(actor, action, subject))

    if (!actionCheck(actorName, actorTier, action, subjectName, subjectTier))
        throw std::exception("You do not have the permissions to do that! \n");

}
