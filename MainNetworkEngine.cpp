#include "MainNetworkEngine.hpp"
#include <cstring>
#include <iostream>


void MainNetworkEngine::inputParser(char *commandLine)
{
    char *tempActor;
    char *tempSubject;
    char *tempAction;
    int tempAge = -1;

    char *token = strtok(commandLine, " ");
    if (token == nullptr)
        throw std::invalid_argument("Unexpected input! Try again. \n");

    tempActor = new char[strlen(token) + 1];
    strcpy(tempActor, token);                                                   // Gets the actor name

    token = strtok(nullptr, " ");
    if (token == nullptr)
    {
        delete[] tempActor;
        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    tempAction = new char[strlen(token) + 1];
    strcpy(tempAction, token);                                                  // Gets the action

    token = strtok(nullptr, " ");
    if (token == nullptr)
    {
        delete[] tempAction;
        delete[] tempActor;
        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    tempSubject = new char[strlen(token) + 1];
    strcpy(tempSubject, token);                                                 // Gets the subject name

    token = strtok(nullptr, " ");                             // Gets possibly age if new user is added
    if (token != nullptr)
    {
        tempAge = atoi(token);
        if (tempAge > 100 || tempAge < 0)
        {
            delete[] tempAction;
            delete[] tempActor;
            delete[] tempSubject;
            throw std::invalid_argument("Unexpected input! Try again. \n");
        }
    }


    try
    {
        commandCaller(tempActor, tempAction, tempSubject, tempAge);
    }
    catch (...)
    {
        delete[] tempAction;
        delete[] tempActor;
        delete[] tempSubject;
        throw;
    }

    delete[] tempAction;
    delete[] tempActor;
    delete[] tempSubject;

}

void MainNetworkEngine::commandCaller(const char *actor, const char *action, const char *subject, int age)
{
    if (strcmp(action, "display_users") == 0)
    {

    }

    if (strcmp(action, "add_user") == 0)
    {
        add_user(action, action, subject, age);
    }

    if (strcmp(action, "remove_user") == 0)
    {
        remove_user(actor, action, subject);
    }

}

void MainNetworkEngine::permissionChecker(UserTiers::Tier actorTier, const char *action)
{
    if (strcmp(action, "add_user") == 0)
    {
        if (actorTier != UserTiers::Tier::Admin)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }

    if (strcmp(action, "remove_user") == 0)
    {
        if (actorTier != UserTiers::Tier::Admin)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }

    if (strcmp(action, "change_tier") == 0)
    {
        if (actorTier != UserTiers::Tier::Admin)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }


    if (strcmp(action, "block_user") == 0)
    {
        if (actorTier <= UserTiers::Tier::Moderator)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }

    if (strcmp(action, "unblock_user") == 0)
    {
        if (actorTier <= UserTiers::Tier::Moderator)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }

    if (strcmp(action, "remove_post") == 0)
    {
        if (actorTier <= UserTiers::Tier::Moderator)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }

    if (strcmp(action, "post") == 0)
    {
        if (actorTier <= UserTiers::Tier::Banned_user)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }

    if (strcmp(action, "change_username") == 0)
    {
        if (actorTier <= UserTiers::Tier::Banned_user)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }

}

void MainNetworkEngine::add_user(const char *actor, const char *action, const char *subject, int age)
{
    UserTiers::Tier tempActorTier = fUsers.getTierFromUsername(actor);

    if (age == -1)
        throw std::invalid_argument("Unexpected input! Try again. \n");

    permissionChecker(tempActorTier, action);

    UserData tempUser(subject, UserTiers::Tier::Basic_User, age);
    fUsers.addUser(tempUser);

}

void MainNetworkEngine::remove_user(const char *actor, const char *action, const char *subject)
{
    UserTiers::Tier tempActorTier = fUsers.getTierFromUsername(actor);

    permissionChecker(tempActorTier, action);

    fUsers.removeUser(subject);

}

void MainNetworkEngine::start()
{
    char *tempCommandBuffer = new char[1000];
    std::cout << "Starting... \n";
    do
    {
        std::cin.getline(tempCommandBuffer, 1000);
        try
        {
            inputParser(tempCommandBuffer);
        }
        catch (std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (std::invalid_argument &e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Unknown error! \n";
        }

    } while (tempCommandBuffer[0] != 0);

    delete[] tempCommandBuffer;
}
