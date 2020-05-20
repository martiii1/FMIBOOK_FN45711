#pragma once

#include "LinkedUser.hpp"
class LinkedUserList
{
public:
    LinkedUserList();;
    ~LinkedUserList();

private:

    LinkedUser *fPointerToFirstUser;
    LinkedUser *fPointerToLastUser;

};
