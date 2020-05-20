#pragma once
#include "User.hpp"

class LinkedUser
{
public:
    LinkedUser();

    User fLinkedUser;
    User* fPointerToNextUser;


};
