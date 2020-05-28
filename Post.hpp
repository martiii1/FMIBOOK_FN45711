#pragma once

#include "PostType.hpp"

class Post
{
public:
    Post();

    ~Post();

    void createPost(const char *usernameOfPoster, PostType::Type postType, const char *post);

    unsigned int getPostNumber();

    Post &operator=(const Post &other);

    Post(const Post &other);

    PostType::Type getPostType();

    const char *getPostTxt();

    void displayPostText();

private:
    char *fPostUsername;
    unsigned int fPostNumber;
    PostType::Type fType;
    char *fPost;
    static unsigned int fPostUniqueNumber;

    void copyPost(const Post &other);

    void delMem();

    void emptyPost();

    void setTypeFromStr(const char *type);
};
