#include "PostsDatabase.hpp"
#include <iostream>
#include <fstream>


PostsDatabase::PostsDatabase()
{
    fAllPosts = allocatePostDatabase(10);
    fSize = 0;

}

Post *PostsDatabase::allocatePostDatabase(unsigned int newCapacity)
{
    Post *tempPointer = new Post[newCapacity];
    fCapacity = newCapacity;

    return tempPointer;
}

PostsDatabase::PostsDatabase(unsigned int initialCapacity)
{
    fSize = 0;
    fCapacity = initialCapacity;
    fAllPosts = allocatePostDatabase(fCapacity);
}

void PostsDatabase::delMem()
{
    delete[] fAllPosts;

}

void PostsDatabase::copyPostsDatabase(const PostsDatabase &other)
{
    delMem();
    fAllPosts = allocatePostDatabase(other.fCapacity);
    fSize = other.fSize;

    for (int i = 0; i < fSize; i++)
    {
        fAllPosts[i] = other.fAllPosts[i];
    }

}

PostsDatabase::PostsDatabase(const PostsDatabase &other)
{
    copyPostsDatabase(other);
}

void PostsDatabase::printAllPosts()
{
    if (fSize == 0)
        throw std::exception("There are no post available. \n");

    for (int i = 0; i < fSize; i++)
    {
        std::cout << "Post #" << fAllPosts[i].getPostNumber() << ", Type: " << fAllPosts[i].getPostType()
                  << ",  text: " << fAllPosts[i].getPostTxt() << std::endl;
    }

}

void PostsDatabase::createNewPost(const Post &newPost)
{
    if (fSize >= fCapacity - 1)
        resizeAllPosts(fCapacity * 2);

    fAllPosts[fSize] = newPost;
    fSize++;
}

void PostsDatabase::resizeAllPosts(unsigned int newCapacity)
{
    Post *tempPointer = new Post[newCapacity];

    for (int i = 0; i < fSize; i++)
    {
        tempPointer[i] = fAllPosts[i];
    }
    delMem();

    fAllPosts = tempPointer;
    fCapacity = newCapacity;
}

PostsDatabase &PostsDatabase::operator=(const PostsDatabase &other)
{
    if (this != &other)
        copyPostsDatabase(other);

    return *this;
}

PostType::Type PostsDatabase::textToPostType(const char *text)
{
    if (strcmp(text, "[image]") == 0)
        return PostType::Type::Image;

    if (strcmp(text, "[text]") == 0)
        return PostType::Type::Text;

    if (strcmp(text, "[url]") == 0)
        return PostType::Type::Link;

    throw std::invalid_argument("Unsupported post type! \n");
}

void PostsDatabase::removePost(unsigned int postNumber)
{
    Post *fTempPosts = new Post[fCapacity];

    size_t counter = 0;
    size_t counterNew = 0;
    size_t counterOld = 0;

    while (counter < fSize)
    {
        if (fAllPosts[counterOld].getPostNumber() == postNumber)
        {
            std::cout << fAllPosts[counterOld].getPostNumber() << " was removed. \n";
            counterOld++;
            counter++;
            continue;
        }

        fTempPosts[counterNew] = fAllPosts[counterOld];
        counterOld++;
        counterNew++;
        counter++;
    }


    if (counterNew < counterOld)
    {
        // delete[] fAllPosts; crashes the program somehow
        fAllPosts = fTempPosts;
        fSize--;
    }
    else
    {
        delete[] fTempPosts;
        throw std::exception("The post wasn't found and wasn't deleted, check if you entered the correct number. \n");
    }

}

void PostsDatabase::generatePostHtml(unsigned int postNumber)
{
    char *tempBuffer = new char[10];
    char *filename = new char[20];
    strcpy(filename, "Post No ");
    strcat(filename, itoa(postNumber, tempBuffer, 10));
    strcat(filename, ".html");

    std::ofstream file(filename);

    if (!file.is_open())
        throw std::exception("Unknown error has occurred! \n");

    bool foundPost = false;
    for (int i = 0; i < fSize; i++)
    {
        if (fAllPosts[i].getPostNumber() == postNumber)
        {
            foundPost = true;
            fAllPosts[i].writePostToFile(file);
        }
    }

    if (!foundPost)
    {
        file.close();
        delete[] tempBuffer;
        delete[] filename;
        throw std::invalid_argument("Post not found! Try again. \n");
    }


    file.close();

    std::cout << "Html file containing post #" << postNumber << " was created. \n";

    delete[] tempBuffer;
    delete[] filename;
}

void PostsDatabase::getAllPostsHtml()
{
    const char *filename = "AllPosts.html";

    std::ofstream file(filename);

    for (int i = 0; i < fSize; i++)
    {
        if (!file.is_open())
            throw std::exception("Unknown error has occurred! \n");

        fAllPosts[i].writePostToFile(file);
        file << std::endl << std::endl;

    }

    file.close();

    std::cout << "Html file containing all available posts was created. \n";

}

void PostsDatabase::getAllPostsHtmlByUser(const char *username)
{
    char *filename = new char[255];
    strcpy(filename, "AllPostsBy");
    strcat(filename, username);
    strcat(filename, ".html");

    std::ofstream file(filename);

    for (int i = 0; i < fSize; i++)
    {
        if (!file.is_open())
        {
            delete[] filename;
            throw std::exception("Unknown error has occurred! \n");
        }

        if (strcmp(fAllPosts[i].getPostUsername(), username) == 0)
        {
            fAllPosts[i].writePostToFile(file);
            file << std::endl << std::endl;
        }

    }

    file.close();
    delete[] filename;

    std::cout << "Html file containing all posts made by  " << username << "\n";

}

void PostsDatabase::removeAllPostsByUser(const char *username)
{
    Post *fTempPosts = new Post[fCapacity];

    size_t counter = 0;
    size_t counterNew = 0;
    size_t counterOld = 0;

    while (counter < fSize)
    {
        if (strcmp(fAllPosts[counterOld].getPostUsername(), username) == 0)
        {
            std::cout << fAllPosts[counterOld].getPostNumber() << " was removed. \n";
            counterOld++;
            counter++;
            continue;
        }

        fTempPosts[counterNew] = fAllPosts[counterOld];
        counterOld++;
        counterNew++;
        counter++;
    }


    if (counterNew < counterOld)
    {
        // delete[] fAllPosts; crashes the program somehow
        fAllPosts = fTempPosts;
        fSize--;
    }
    else
    {
        delete[] fTempPosts;
        throw std::exception("The post wasn't found and wasn't deleted, check if you entered the correct number. \n");
    }


}

int PostsDatabase::getNumberOfPostsByUsername(const char *username)
{
    size_t counter = 0;
    for (int i = 0; i < fSize; i++)
    {
        if (strcmp(fAllPosts[i].getPostUsername(), username) == 0)
            counter++;
    }

    return counter;
}
