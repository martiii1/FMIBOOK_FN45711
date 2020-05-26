#pragma once

#include "Post.hpp"

class PostsDatabase
{
public:
    PostsDatabase();

    PostsDatabase(unsigned int initialCapacity);

    PostsDatabase(const PostsDatabase &other);

    void printAllPosts();

private:
    Post *fAllPosts;
    unsigned int fSize;
    unsigned int fCapacity;

    Post *allocatePostDatabase(unsigned int newCapacity);

    void delMem();

    void copyPostsDatabase(const PostsDatabase &other);

};
