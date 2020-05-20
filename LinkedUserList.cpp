#include "LinkedUserList.hpp"

LinkedUserList::~LinkedUserList()
{
    LinkedUser *tempPointer = fPointerToFirstUser;

    while (tempPointer != nullptr)
    {
       tempPointer->fLinkedUser.~UserData();
       tempPointer = tempPointer->fPointerToNextUser;
    }
}

LinkedUserList::LinkedUserList()
{
    fPointerToFirstUser = nullptr;
    fPointerToLastUser = nullptr;
}
