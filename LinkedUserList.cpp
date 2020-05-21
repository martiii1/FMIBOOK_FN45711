#include "LinkedUserList.hpp"

LinkedUserList::~LinkedUserList()
{
    LinkedUser *tempPointer = fPointerToFirstUser;
    LinkedUser *tempPointerNext;

    while (tempPointer != nullptr)
    {
       tempPointer->fLinkedUser.~UserData();
       tempPointerNext = tempPointer->fPointerToNextUser;

       delete tempPointer;

       tempPointer = tempPointerNext;
    }


}

LinkedUserList::LinkedUserList()
{
    fPointerToFirstUser = nullptr;
    fPointerToLastUser = nullptr;
}

void LinkedUserList::addUser(const UserData &newUser)
{
    if(fPointerToFirstUser == nullptr)
    {
        fPointerToFirstUser = new LinkedUser(newUser);
        fPointerToLastUser = fPointerToFirstUser;
    }
    else
    {
        fPointerToLastUser->fPointerToNextUser = new LinkedUser(newUser);
        fPointerToLastUser = fPointerToLastUser->fPointerToNextUser;
    }

}

void LinkedUserList::changeUserTier(const char* actor,const char* subject, UserTiers::Tier newTier)
{
    UserTiers::Tier tempActorTier = getTierFromUsername(actor);
    UserTiers::Tier tempSubjectTier = getTierFromUsername(subject);

    ActionPermissions::isTheActionAllowed(tempActorTier, SystemActions::Actions::Change_tier, tempSubjectTier);

    newUserTier(subject,newTier);

}

void LinkedUserList::newUserTier(const char *username, UserTiers::Tier newTier)
{
    LinkedUser *tempPointer = fPointerToFirstUser;
    bool changes_made = false;

    while (tempPointer != nullptr)
    {
        if (strcmp(tempPointer->fLinkedUser.getUsername(), username) == 0)
        {
            tempPointer->fLinkedUser.setUserTier(newTier);
            changes_made = true;
            break;
        }
        else
        {
            tempPointer = tempPointer->fPointerToNextUser;
        }
    }

    if(!changes_made)
        throw std::exception("No user found with that username!");
}

void LinkedUserList::permissionChecker(const char *actor, const char *subject, SystemActions::Actions action)
{
    LinkedUser *tempPointer = fPointerToFirstUser;

    UserTiers::Tier tempActorTier  = getTierFromUsername(actor);
    UserTiers::Tier tempSubjectTier = getTierFromUsername(subject);


    if(tempSubjectTier == UserTiers::Tier::Nothing || tempActorTier == UserTiers::Tier::Nothing)
        throw std::exception("No user found with that username!");
    else
        ActionPermissions::isTheActionAllowed(actor, tempActorTier,action, subject,tempSubjectTier);
}

UserTiers::Tier LinkedUserList::getTierFromUsername(const char *username)
{
    LinkedUser *tempPointer = fPointerToFirstUser;

    UserTiers::Tier tempTier = UserTiers::Tier::Nothing;

    while (tempPointer != nullptr)
    {
        if (strcmp(tempPointer->fLinkedUser.getUsername(), username) == 0)
        {
            tempTier = tempPointer->fLinkedUser.getUserTier();
        }
        else
        {
            tempPointer = tempPointer->fPointerToNextUser;
        }
    }

    if(tempTier == UserTiers::Tier::Nothing)
        throw std::exception("No user found with that username!");

    return tempTier;
}
