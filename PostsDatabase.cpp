#include "PostsDatabase.hpp"

PostsDatabase::PostsDatabase()
{
    fAllPosts = nullptr;
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
    delete [] fAllPosts;

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
