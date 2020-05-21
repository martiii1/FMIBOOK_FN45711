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
    ActionPermissions::isTheActionAllowed(actor, SystemActions::Actions::Change_tier, subject);

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
