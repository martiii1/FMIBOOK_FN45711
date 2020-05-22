#include <iostream>
#include "UserDatabase.hpp"

int main()
{
    UserData mUser("marti",UserTiers::Tier::Admin,20);
    UserData vUser("victor",UserTiers::Tier::Admin,19);
    UserData cUser("ceci",UserTiers::Tier::Admin,20);

    UserDatabase testDatabase(5);

    testDatabase.addUser(mUser);
    testDatabase.addUser(vUser);

    testDatabase.printAllUsers();

    return 0;
}
