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

    void inputParser(const char *commandLine);

    bool checkForExit(const char *text);

    void commandCaller(const char *commandLineText);

    void postCommandCaller(const char *commandLineText);

    void firstWordCommands(const char* commandText);

    void permissionChecker(UserTiers::Tier actorTier, const char *action);

    void usernameAvailabilityChecker(const char *username);

    void show_users();

    void show_posts();

    void add_user(const char *commandLineText);

    void add_moderator(const char *commandLineText);

    void remove_user(const char *commandLineText);

    void remove_post(const char *commandLineText);

    void post(const char *commandLineText);

    void help();
};
