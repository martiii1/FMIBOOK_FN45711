#include <iostream>
#include "LinkedUserList.hpp"
#include "UserData.hpp"
#include "UserTiers.hpp"

int main()
{

    LinkedUserList userBase;
    UserData asd("Martin",UserTiers::Tier::Admin, 20);

    userBase.addUser(asd);



}
