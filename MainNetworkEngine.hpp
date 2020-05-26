#pragma once

#include "UserDatabase.hpp"
#include "PostsDatabase.hpp"

class MainNetworkEngine
{
public:

    void start();


private:
    UserDatabase fUsers;
    PostsDatabase fPosts;

    void inputParser(char *commandLine);

    void commandCaller(const char *actor, const char *action, const char *subject, int age);

    void show_users();

    void permissionChecker(UserTiers::Tier actorTier, const char *action);

    void usernameAvailabilityChecker(const char *username);

    void add_user(const char *actor, const char *action, const char *subject, int age);

    void remove_user(const char *actor, const char *action, const char *subject);
};
