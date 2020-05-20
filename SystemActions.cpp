#include "SystemActions.hpp"

void SystemActions::isTheActionAllowed(const UserData &actor, Actions action,const UserData &subject)
{

    if(action == Actions::Nothing)
        throw std::exception("Invalid action, try again! \n");

    //if(!actionCheck(actor, action, subject))

    if(!SystemActions::actionCheck(actor, action, subject))
        throw std::exception("You do not have the permissions to do that! \n");

}

bool SystemActions::actionCheck(const UserData &actor, Actions action,const UserData &subject)
{
    switch (action)
    {
        case Actions::Nothing:                                    // Invalid action
            return false;

        case  Actions::Add_post:                                   // Adding post
            return actor.getUserTier() != UserTiers::Tier::Nothing;

        case  Actions::Remove_post:                                // Removing post
            if(actor.getUserTier() >= UserTiers::Tier::Moderator)
                return true;
            else
                return (actor.getUserTier() == UserTiers::Tier::Basic_User &&
                       strcmp(actor.getUsername(), subject.getUsername()) == 0);

        case   Actions::Change_username:                            // Change username
            return true;

        case   Actions::Block_user:                                // Block user
            return actor.getUserTier() >= UserTiers::Tier::Moderator;

        case   Actions::Unblock_user:                              // Unblock user
            return actor.getUserTier() >= UserTiers::Tier::Moderator;

        case  Actions::Add_user:                                   // Add user
            return actor.getUserTier() >= UserTiers::Admin;

        case  Actions::Remove_user:                                // Remove user
            return actor.getUserTier() >= UserTiers::Admin;

        case  Actions::Change_tier:                                // Change user tier
            return actor.getUserTier() >= UserTiers::Admin;
    }
    return false;
}
