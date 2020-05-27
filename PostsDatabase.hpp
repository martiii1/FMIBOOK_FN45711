#pragma once

#include "Post.hpp"

class PostsDatabase
{
public:
    PostsDatabase();

    PostsDatabase(unsigned int initialCapacity);

    PostsDatabase(const PostsDatabase &other);

    PostsDatabase &operator=(const PostsDatabase &other);

    void printAllPosts();

    PostType::Type textToPostType(const char *text);

    void createNewPost(const Post &newPost);


private:
    Post *fAllPosts;
    unsigned int fSize;
    unsigned int fCapacity;

    Post *allocatePostDatabase(unsigned int newCapacity);

    void delMem();

    void copyPostsDatabase(const PostsDatabase &other);

    void resizeAllPosts(unsigned int newCapacity);
};
