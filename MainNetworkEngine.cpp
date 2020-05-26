#include "MainNetworkEngine.hpp"
#include <cstring>
#include <iostream>


void MainNetworkEngine::inputParser(const char *commandLine)
{
    char *tempCommandLine = new char[strlen(commandLine) + 1];
    strcpy(tempCommandLine,commandLine);

    try
    {
        commandCaller(commandLine);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        throw;
    }

    delete [] tempCommandLine;

}

void MainNetworkEngine::commandCaller(const char *commandLineText)
{
    char *tempCommandLine = new char[strlen(commandLineText) + 1];
    strcpy(tempCommandLine,commandLineText);

    char *token = strtok(tempCommandLine, " "); // This takes the name out of a correct input
    if (token == nullptr)
    {
        delete [] tempCommandLine;
        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    token = strtok(nullptr, " "); // This takes the action out of a correct input
    if (token == nullptr)
    {
        delete[] tempCommandLine;
        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    try
    {
        if (strcmp(token, "display_users") == 0)
        {
            show_users();
        }

        if (strcmp(token, "display_posts") == 0)
        {
            show_posts();
        }

        if (strcmp(token, "add_user") == 0)
        {
            add_user(commandLineText);
        }

        if (strcmp(token, "add_moderator") == 0)
        {
            add_moderator(commandLineText);
        }

        if (strcmp(token, "remove_user") == 0)
        {
            remove_user(commandLineText);
        }
    }
    catch (...)
    {
        delete [] tempCommandLine;
        throw;
    }

    delete [] tempCommandLine;
}

void MainNetworkEngine::permissionChecker(UserTiers::Tier actorTier, const char *action)
{
    if (strcmp(action, "add_user") == 0)
    {
        if (actorTier != UserTiers::Tier::Admin)
            throw std::exception("You do not have permission to do that! \n");

        return;
    }

    if (strcmp(action, "add_moderator") == 0)
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

void MainNetworkEngine::add_user(const char *commandLineText)
{
    char *tempCommandLine = new char[strlen(commandLineText) + 1];
    strcpy(tempCommandLine,commandLineText);

    const char *tempAction = "add_user";
    char *tempActor;
    char *tempSubject;
    int tempAge = -1;

    char *token = strtok(tempCommandLine, " "); // This takes the name out of a correct input

    // Actor username
    tempActor = new char[strlen(token) + 1];
    strcpy(tempActor,token);

    // Skip action
    token = strtok(nullptr, " ");

    // New username
    token = strtok(nullptr, " ");
    if(token == nullptr)
    {
        delete [] tempCommandLine;
        delete [] tempActor;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    tempSubject = new char[strlen(token) + 1];
    strcpy(tempSubject,token);

    // Age
    token = strtok(nullptr, " ");
    if(token == nullptr)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempSubject;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }
    tempAge = atoi(token);

    // Age check
    if(tempAge <=0 || tempAge > 100)  // Somewhat random limit for the age for a fast check
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempSubject;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    UserTiers::Tier tempActorTier = fUsers.getTierFromUsername(tempActor);

    try
    {
        permissionChecker(tempActorTier, tempAction);

        usernameAvailabilityChecker(tempSubject);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempSubject;

        throw;
    }

    UserData tempUser(tempSubject, UserTiers::Tier::Basic_User, tempAge);
    fUsers.addUser(tempUser);

    delete [] tempCommandLine;
    delete [] tempActor;
    delete [] tempSubject;
}

void MainNetworkEngine::remove_user(const char *commandLineText)
{
    char *tempCommandLine = new char[strlen(commandLineText) + 1];
    strcpy(tempCommandLine,commandLineText);

    const char *tempAction = "remove_user";
    char *tempActor;
    char *tempSubject;

    char *token = strtok(tempCommandLine, " "); // This takes the name out of a correct input

    // Actor username
    tempActor = new char[strlen(token) + 1];
    strcpy(tempActor,token);

    // Skip action
    token = strtok(nullptr, " ");

    // New username
    token = strtok(nullptr, " ");
    if(token == nullptr)
    {
        delete [] tempCommandLine;
        delete [] tempActor;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    tempSubject = new char[strlen(token) + 1];
    strcpy(tempSubject,token);


    UserTiers::Tier tempActorTier = fUsers.getTierFromUsername(tempActor);
    try
    {
        permissionChecker(tempActorTier, tempAction);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempSubject;

        throw;
    }

    fUsers.removeUser(tempSubject);

    delete [] tempCommandLine;
    delete [] tempActor;
    delete [] tempSubject;
}

void MainNetworkEngine::start()
{
    char *tempCommandBuffer = new char[1000];
    std::cout << "Starting... \n";
    std::cout << "Please enter the admin username: ";
    std::cin.getline(tempCommandBuffer, 1000);
    UserData tempAdmin(tempCommandBuffer,UserTiers::Tier::Admin,20);
    fUsers.addUser(tempAdmin);

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

void MainNetworkEngine::show_users()
{
    fUsers.printAllUsers();
}

void MainNetworkEngine::usernameAvailabilityChecker(const char *username)
{
    if(fUsers.doesUsernameExist(username))
    {
        throw std::exception("Username is already used! \n");
    }
}

void MainNetworkEngine::show_posts()
{
    fPosts.printAllPosts();

}

void MainNetworkEngine::postCommandCaller(const char *commandLineText)
{

}

void MainNetworkEngine::add_moderator(const char *commandLineText)
{
    char *tempCommandLine = new char[strlen(commandLineText) + 1];
    strcpy(tempCommandLine,commandLineText);

    const char *tempAction = "add_moderator";
    char *tempActor;
    char *tempSubject;
    int tempAge = -1;

    char *token = strtok(tempCommandLine, " "); // This takes the name out of a correct input

    // Actor username
    tempActor = new char[strlen(token) + 1];
    strcpy(tempActor,token);

    // Skip action
    token = strtok(nullptr, " ");

    // New username
    token = strtok(nullptr, " ");
    if(token == nullptr)
    {
        delete [] tempCommandLine;
        delete [] tempActor;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    tempSubject = new char[strlen(token) + 1];
    strcpy(tempSubject,token);

    // Age
    token = strtok(nullptr, " ");
    if(token == nullptr)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempSubject;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }
    tempAge = atoi(token);

    // Age check
    if(tempAge <=0 || tempAge > 100)  // Somewhat random limit for the age for a fast check
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempSubject;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    UserTiers::Tier tempActorTier = fUsers.getTierFromUsername(tempActor);

    try
    {
        permissionChecker(tempActorTier, tempAction);

        usernameAvailabilityChecker(tempSubject);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempSubject;

        throw;
    }

    UserData tempUser(tempSubject, UserTiers::Tier::Moderator, tempAge);
    fUsers.addUser(tempUser);

    delete [] tempCommandLine;
    delete [] tempActor;
    delete [] tempSubject;

}
