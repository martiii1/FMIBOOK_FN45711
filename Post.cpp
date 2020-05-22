#include "Post.hpp"
#include <iostream>
#include <cstring>

Post::Post()
{
    emptyPost();
}

void Post::createPost(const char *usernameOfPoster, const char *postType, const char *post)
{
    fPostUsername = new char[strlen(usernameOfPoster) + 1];
    strcpy(fPostUsername,usernameOfPoster);

    setTypeFromStr(postType);

    fPost = new char[strlen(post) + 1];
    strcpy(fPost, post);

    fPostNumber = fPostUniqueNumber;

    fPostUniqueNumber++;
}

void Post::delMem()
{
    delete [] fPost;
    delete [] fPostUsername;

}

Post::~Post()
{
    delMem();
}

void Post::emptyPost()
{
    fPostUsername = nullptr;
    fPostNumber = 0;
    fType = PostType::Type::Nothing;
    fPost = nullptr;

    fPostUniqueNumber = 0;

}

void Post::setTypeFromStr(const char *type)
{
    if( strcmp(type,"[text]") == 0)
        fType = PostType::Type::Text;
    else if( strcmp(type,"[url]") == 0)
        fType = PostType::Type::Link;
    else if( strcmp(type,"[image]") == 0)
        fType = PostType::Type::Image;
    else
    {
        fType = PostType::Type::Nothing;
        throw std::exception("Unknown image type, please try again \n");
    }

}
