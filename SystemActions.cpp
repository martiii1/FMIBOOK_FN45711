#include "SystemActions.hpp"

void SystemActions::isTheActionAllowed(UserData &actor, SystemActions::Action action, UserData &subject)
{

    if(action == SystemActions::Action::Nothing)
        throw std::exception("Invalid action, try again! \n");

    if(!actionCheck(actor, action, subject))
        throw std::exception("You do not have the permissions to do that! \n");

}

bool SystemActions::actionCheck(UserData &actor, SystemActions::Action action, UserData &subject)
{
    switch (action)
    {
        case SystemActions::Action::Nothing:                                    // Invalid action
            return false;

        case SystemActions::Action::Add_post:                                   // Adding post
            return actor.getUserTier() != UserTiers::Tier::Nothing;

        case SystemActions::Action::Remove_post:                                // Removing post
            if(actor.getUserTier() >= UserTiers::Tier::Moderator)
                return true;
            else
                return (actor.getUserTier() == UserTiers::Tier::Basic_User &&
                       strcmp(actor.getUsername(), subject.getUsername()) == 0);

        case  SystemActions::Action::Change_username:                            // Change username
            return true;

        case  SystemActions::Action::Block_user:                                // Block user
            return actor.getUserTier() >= UserTiers::Tier::Moderator;

        case  SystemActions::Action::Unblock_user:                              // Unblock user
            return actor.getUserTier() >= UserTiers::Tier::Moderator;

        case SystemActions::Action::Add_user:                                   // Add user
            return actor.getUserTier() >= UserTiers::Admin;

        case SystemActions::Action::Remove_user:                                // Remove user
            return actor.getUserTier() >= UserTiers::Admin;

        case SystemActions::Action::Change_tier:                                // Change user tier
            return actor.getUserTier() >= UserTiers::Admin;
    }
}
