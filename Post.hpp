#pragma once

#include "PostType.hpp"

class Post
{
public:
    Post();

    ~Post();

    void createPost(const char *usernameOfPoster, PostType::Type postType, const char *post);

    unsigned int getPostNumber();

    PostType::Type getPostType();

    const char* getPostTxt();

private:
    char *fPostUsername;
    unsigned int fPostNumber;
    PostType::Type fType;
    char *fPost;
    static unsigned int fPostUniqueNumber;

    void delMem();

    void emptyPost();

    void setTypeFromStr(const char *type);
};
