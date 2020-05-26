#pragma once
#include "UserDatabase.hpp"
#include "PostsDatabase.hpp"

class MainNetworkEngine
{
public:

    void start();
    void commandCaller();



private:
    UserDatabase fUsers;
    PostsDatabase fPosts;

    void inputParser(char* commandLine);
    void commandCaller(const char* actor,const char* action, const char* subject,int age);
    void permissionChecker(const char *actor, const char *action, const char *subject);
};
