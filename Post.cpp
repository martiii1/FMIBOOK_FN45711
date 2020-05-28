#include "Post.hpp"
#include <iostream>
#include <cstring>

unsigned int Post::fPostUniqueNumber = 0;

Post::Post()
{
    emptyPost();
}

void Post::createPost(const char *usernameOfPoster, PostType::Type postType, const char *post)
{
    fPostUsername = new char[strlen(usernameOfPoster) + 1];
    strcpy(fPostUsername,usernameOfPoster);

    fType = postType;

    fPost = new char[strlen(post) + 1];
    strcpy(fPost, post);

    fPostNumber = fPostUniqueNumber;

    std::cout << "Post" << " #" << fPostUniqueNumber << " was created \n";

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

const char *Post::getPostTxt()
{
    return fPost;
}

PostType::Type Post::getPostType()
{
    return fType;
}

unsigned int Post::getPostNumber()
{
    return fPostNumber;
}

void Post::displayPostText()
{
    std::cout << fPost;

}

Post &Post::operator=(const Post &other)
{
    if(this != &other)
    {
        delMem();
        copyPost(other);
    }
    else
        return *this;
}

void Post::copyPost(const Post &other)
{
    fPostUsername = new char[strlen(other.fPostUsername) + 1];
    strcpy(fPostUsername,other.fPostUsername);

    fPost = new char[strlen(other.fPost)];
    strcpy(fPost, other.fPost);

    fPostNumber = other.fPostNumber;
    fType = other.fType;
}
