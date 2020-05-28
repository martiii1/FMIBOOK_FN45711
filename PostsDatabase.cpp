#include "PostsDatabase.hpp"
#include <iostream>

PostsDatabase::PostsDatabase()
{
    fAllPosts = allocatePostDatabase(10);
    fSize = 0;
    fCapacity = 5;

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
    if(strcmp(text, "[image]") == 0)
        return PostType::Type::Image;

    if(strcmp(text, "[text]") == 0)
        return PostType::Type::Text;

    if(strcmp(text, "[url]") == 0)
        return PostType::Type::Link;

    throw std::invalid_argument("Unsupported post type! \n");
}
