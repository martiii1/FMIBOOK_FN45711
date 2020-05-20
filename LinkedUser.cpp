#include "LinkedUser.hpp"

LinkedUser::LinkedUser()
{
    fPointerToNextUser = nullptr;
}

LinkedUser::LinkedUser(const UserData &other)
{
    fLinkedUser = other;
    fPointerToNextUser = nullptr;
}
