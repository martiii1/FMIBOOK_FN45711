#pragma once

#include "PostType.hpp"

class Post
{
public:
    Post();
    ~Post();

    void createPost(const char *usernameOfPoster, const char *postType, const char *post);


private:
    char* fPostUsername;
    unsigned int fPostNumber;
    PostType::Type fType;
    char* fPost;

    static unsigned int fPostUniqueNumber;

    void delMem();
    void emptyPost();

   void setTypeFromStr(const char* type);
};
