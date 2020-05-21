#pragma once
#include "UserData.hpp"

class LinkedUser
{
public:
    LinkedUser();
    LinkedUser(const UserData& other);

    UserData fLinkedUser;
    LinkedUser *fPointerToNextUser;

};
