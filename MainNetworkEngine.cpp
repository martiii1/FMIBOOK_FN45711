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

    char *token = strtok(tempCommandLine, " "); // This takes the first word (name or a one word command).
    if (token == nullptr)
    {
        delete [] tempCommandLine;
        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    firstWordCommands(token); // Checks if the first word is a command on its own.


    token = strtok(nullptr, " "); // This takes the second word (most likely an action).
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
        else if (strcmp(token, "display_posts") == 0)
        {
            show_posts();
        }
        else if (strcmp(token, "add_user") == 0)
        {
            add_user(commandLineText);
        }
        else if (strcmp(token, "add_moderator") == 0)
        {
            add_moderator(commandLineText);
        }
        else if (strcmp(token, "remove_user") == 0)
        {
            remove_user(commandLineText);
        }
        else if (strcmp(token, "remove_post") == 0)
        {
            remove_post(commandLineText);
        }
        else if (strcmp(token, "post") == 0)
        {
            post(commandLineText);
        }
        else if (strcmp(token, "view_post") == 0)
        {
            view_post(commandLineText);
        }
        else
        {
            throw std::invalid_argument("Unexpected input, try again. \n");
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

    if (strcmp(action, "view_post") == 0)
    {
        if (actorTier < UserTiers::Tier::Banned_user)
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

    // Removed user username
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
        fUsers.removeUser(tempSubject);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempSubject;

        throw;
    }



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
            if(checkForExit(tempCommandBuffer))
                break;
            else
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

bool MainNetworkEngine::checkForExit(const char *text)
{
    char *tempTxt = new char[strlen(text) + 1];
    strcpy(tempTxt,text);

    char *token = strtok(tempTxt, " ");

    if(strcmp(token, "Exit") == 0 || strcmp(token, "exit") == 0)
    {
        delete [] tempTxt;
        return true;
    }
    else
    {
        delete [] tempTxt;
        return false;
    }
}

void MainNetworkEngine::help()
{
    std::cout << "[name] display_users - prints all registered users, their rank(the enum number) and their age. \n \n";

    std::cout << "[name] display_posts - prints the raw data from all available posts (for testing purposes). \n \n";

    std::cout << "[name1] add_user [name2] [age] - Adds a new basic user with username [name2] and age [age], \n";
    std::cout << "to add a user [name1] has to be the Admin and [name2] has to be an unused username. \n \n";

    std::cout << "[name1] add_moderator [name2] [age] - Adds a new moderator user with name [name2] and age [age], \n";
    std::cout << "to add a moderator [name1] has to be the Admin and [name2] has to be an unused username. \n \n";

    std::cout << "[name1] remove_user [name2] - Removes the user with username [name2] and deletes all posts made by the user, \n";
    std::cout << "to remove a user [name1] has to be the Admin.\n \n";
}

void MainNetworkEngine::firstWordCommands(const char *commandText)
{
    if(strcmp(commandText, "Help") == 0 || strcmp(commandText, "help") == 0)
    {
        help();
    }

}

void MainNetworkEngine::post(const char *commandLineText)
{
    char *tempCommandLine = new char[strlen(commandLineText) + 1];
    strcpy(tempCommandLine,commandLineText);

    const char *tempAction = "post";
    char *tempActor;
    char *tempPostType;

    char *token = strtok(tempCommandLine, " "); // This takes the name of the poster/actor.

    // Actor username
    tempActor = new char[strlen(token) + 1];
    strcpy(tempActor,token);

    // Skip action
    token = strtok(nullptr, " ");

    // The type of post( [image], [link] or [text] ).
    token = strtok(nullptr, " ");
    if(token == nullptr)
    {
        delete [] tempCommandLine;
        delete [] tempActor;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }
    // Post type in text.
    tempPostType = new char[strlen(token) + 1];
    strcpy(tempPostType, token);

    PostType::Type tempType;
    try
    {
        tempType = fPosts.textToPostType(token);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempPostType;
        throw;
    }


    UserTiers::Tier tempActorTier = fUsers.getTierFromUsername(tempActor);
    try
    {
        permissionChecker(tempActorTier, tempAction);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempPostType;

        throw;
    }

    // Get the actual post
    token = strtok(nullptr, " ");
    if(token == nullptr)
    {
        delete [] tempCommandLine;
        delete [] tempActor;
        delete [] tempPostType;

        throw std::invalid_argument("Unexpected input! Try again. \n");
    }

    char *tempPostText = new char[strlen(token) + 1];
    char *tempBuffer = nullptr;
    strcpy(tempPostText,token);

    while (token != nullptr)
    {
        token = strtok(nullptr, " ");
        if(token == nullptr)
            continue;

        delete [] tempBuffer;
        tempBuffer = new char[strlen(tempPostText) + 1];
        strcpy(tempBuffer,tempPostText);

        delete [] tempPostText;
        tempPostText = new char[strlen(tempBuffer) + strlen(token) + 2]; // for \0 and for the space between words
        strcpy(tempPostText, tempBuffer);
        strcat(tempPostText, " ");
        strcat(tempPostText, token);

    }
    delete [] tempBuffer;

    Post tempPost;
    tempPost.createPost(tempActor,tempType,tempPostText);

    fPosts.createNewPost(tempPost);


    delete [] tempPostText;
    delete [] tempCommandLine;
    delete [] tempActor;
    delete [] tempPostType;
}

void MainNetworkEngine::remove_post(const char *commandLineText)
{
    char *tempCommandLine = new char[strlen(commandLineText) + 1];
    strcpy(tempCommandLine,commandLineText);

    const char *tempAction = "remove_post";
    char *tempActor;

    char *token = strtok(tempCommandLine, " "); // This takes the name out of a correct input

    // Actor username
    tempActor = new char[strlen(token) + 1];
    strcpy(tempActor,token);

    // Skip action
    token = strtok(nullptr, " ");

    // Removed post number
    token = strtok(nullptr, " ");
    unsigned int tempNum = atoi(token);

    UserTiers::Tier tempActorTier = fUsers.getTierFromUsername(tempActor);
    try
    {
        permissionChecker(tempActorTier, tempAction);
        fPosts.removePost(tempNum);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        delete [] tempActor;

        throw;
    }



    delete [] tempCommandLine;
    delete [] tempActor;

}

void MainNetworkEngine::view_post(const char *commandLineText)
{
    char *tempCommandLine = new char[strlen(commandLineText) + 1];
    strcpy(tempCommandLine,commandLineText);

    const char *tempAction = "view_post";
    char *tempActor;

    char *token = strtok(tempCommandLine, " "); // This takes the name out of a correct input

    // Actor username
    tempActor = new char[strlen(token) + 1];
    strcpy(tempActor,token);

    // Skip action
    token = strtok(nullptr, " ");

    // View post number
    token = strtok(nullptr, " ");
    unsigned int tempNum = atoi(token);

    UserTiers::Tier tempActorTier = fUsers.getTierFromUsername(tempActor);
    try
    {
        permissionChecker(tempActorTier, tempAction);
        fPosts.generatePostHtml(tempNum);
    }
    catch (...)
    {
        delete [] tempCommandLine;
        delete [] tempActor;

        throw;
    }



    delete [] tempCommandLine;
    delete [] tempActor;

}

