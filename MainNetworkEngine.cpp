#include "MainNetworkEngine.hpp"
#include <cstring>
#include <iostream>


void MainNetworkEngine::inputParser(char *commandLine)
{
    char *tempActor;
    char *tempSubject;
    char *tempAction;
    int tempAge = -1;

    char *token = strtok(commandLine," ");
    if(token == nullptr)
        throw std::invalid_argument("Unexpected input! Try again. \n");

    tempActor = new char[strlen(token) + 1];
    strcpy(tempActor,token);                                                   // Gets the actor name

    token = strtok(nullptr," ");
    if(token == nullptr)
    {
        delete [] tempActor;
        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    tempAction = new char[strlen(token) + 1];
    strcpy(tempAction,token);                                                  // Gets the action

    token = strtok(nullptr," ");
    if(token == nullptr)
    {
        delete [] tempAction;
        delete [] tempActor;
        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    tempSubject = new char[strlen(token) + 1];
    strcpy(tempSubject,token);                                                 // Gets the subject name

    token = strtok(nullptr," ");                             // Gets possibly age if new user is added
    if(token != nullptr)
    {
        tempAge = atoi(token);
        if(tempAge > 100 || tempAge < 0)
        {
            delete [] tempAction;
            delete [] tempActor;
            delete [] tempSubject;
            throw std::invalid_argument("Unexpected input! Try again. \n");
        }
    }


    try
    {
        commandCaller(tempActor,tempAction,tempSubject,tempAge);
    }
    catch (...)
    {
        delete [] tempAction;
        delete [] tempActor;
        delete [] tempSubject;
        throw;
    }

    delete [] tempAction;
    delete [] tempActor;
    delete [] tempSubject;

}

void MainNetworkEngine::commandCaller(const char *actor, const char *action, const char *subject, int age)
{
    if(strcmp(action,"add_user") == 0)
    {
        if(age == -1)
            throw std::invalid_argument("Unexpected input! Try again. \n");

        permissionChecker(action,action,subject);

        UserData tempUser(subject,UserTiers::Tier::Basic_User,age);
        fUsers.addUser(tempUser);
    }

}

void MainNetworkEngine::permissionChecker(const char *actor, const char *action, const char *subject)
{


}
