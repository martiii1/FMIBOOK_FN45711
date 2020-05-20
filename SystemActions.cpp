#include "SystemActions.hpp"

void SystemActions::isTheActionAllowed(User actor, SystemActions::Action action, User subject)
{

    switch (action)
    {
        case SystemActions::Action::Nothing:
            throw std::exception("Invalid action, try again! \n");

        case SystemActions::Action::Add_post:
            break;

        case SystemActions::Action::Remove_post:
            if(actor.fUserTier > )
    }

}
