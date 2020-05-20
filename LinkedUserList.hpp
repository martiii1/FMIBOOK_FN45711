#pragma once

#include "LinkedUser.hpp"
class LinkedUserList
{
public:
    LinkedUserList();;
    ~LinkedUserList();

    void addUser(const UserData&);

private:

    LinkedUser *fPointerToFirstUser;
    LinkedUser *fPointerToLastUser;


};
