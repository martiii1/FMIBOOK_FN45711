#include "ActionPermissions.hpp"

bool ActionPermissions::actionCheck(UserData &actor, SystemActions::Actions action, UserData &subject)
{
    switch (action)
    {
        case SystemActions::Actions::Nothing:                                    // Invalid action
            return false;

        case  SystemActions::Actions::Add_post:                                   // Adding post
            return actor.getUserTier() != UserTiers::Tier::Nothing;

        case  SystemActions::Actions::Remove_post:                                // Removing post
            if(actor.getUserTier() >= UserTiers::Tier::Moderator)
                return true;
            else
                return (actor.getUserTier() == UserTiers::Tier::Basic_User &&
                        strcmp(actor.getUsername(), subject.getUsername()) == 0);

        case   SystemActions::Actions::Change_username:                            // Change username
            return true;

        case   SystemActions::Actions::Block_user:                                // Block user
            return actor.getUserTier() >= UserTiers::Tier::Moderator;

        case   SystemActions::Actions::Unblock_user:                              // Unblock user
            return actor.getUserTier() >= UserTiers::Tier::Moderator;

        case  SystemActions::Actions::Add_user:                                   // Add user
            return actor.getUserTier() >= UserTiers::Admin;

        case  SystemActions::Actions::Remove_user:                                // Remove user
            return actor.getUserTier() >= UserTiers::Admin;

        case  SystemActions::Actions::Change_tier:                                // Change user tier
            return actor.getUserTier() >= UserTiers::Admin;
    }
    return false;
}


void ActionPermissions::isTheActionAllowed(UserData &actor, SystemActions::Actions action, UserData &subject)
{

    if(action == SystemActions::Actions::Nothing)
        throw std::exception("Invalid action, try again! \n");

    //if(!actionCheck(actor, action, subject))

    if(!actionCheck(actor, action, subject))
        throw std::exception("You do not have the permissions to do that! \n");

}
