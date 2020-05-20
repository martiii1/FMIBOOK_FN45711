#pragma once
#include "UserData.hpp"

class LinkedUser
{
public:
    LinkedUser();

    UserData fLinkedUser;
    LinkedUser *fPointerToNextUser;

};
