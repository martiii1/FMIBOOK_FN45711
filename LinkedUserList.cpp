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
