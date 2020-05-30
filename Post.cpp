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
    fPost = nullptr;
    fPostNumber = 0;
    fType = PostType::Type::Nothing;
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

Post::Post(const Post &other)
{
    copyPost(other);
}

void Post::writePostToFile(std::ofstream &file)
{
    htmlFileStart(file);

    if(fType == PostType::Type::Text)
    {
        textPostToFile(file);
    }
    else if(fType == PostType::Type::Link)
    {
        linkPostToFile(file);
    }
    else if(fType == PostType::Type::Image)
    {
        imagePostToFile(file);
    }

    htmlFileEnd(file);
}

void Post::htmlFileStart(std::ofstream &file)
{
    file << "<!DOCTYPE html>" << std::endl;
    file << "<html>" << std::endl;
    file << "<body>" << std::endl;
}

void Post::htmlFileEnd(std::ofstream &file)
{
    file << std::endl;

    file << "</body>" << std::endl;
    file << "</html>" << std::endl;
}

void Post::textPostToFile(std::ofstream &file)
{
    file << "<h2>Post #" << fPostNumber << ", made by: " << fPostUsername <<". </h2>" << std::endl;
    file << std::endl;

    file << "<p>" << fPost << " </p>" << std::endl;
}

void Post::linkPostToFile(std::ofstream &file)
{
    file << "<h2>Post #" << fPostNumber << ", made by: " << fPostUsername <<". </h2>" << std::endl;
    file << std::endl;

    file << "<a href=\"https://" << fPost << "\">" << fPost << "</a>" << std::endl;

}

void Post::imagePostToFile(std::ofstream &file)
{
    file << "<h2>Post #" << fPostNumber << ", made by: " << fPostUsername <<". </h2>" << std::endl;
    file << std::endl;

    file << "<img src=\"" << fPost << "\">" << fPost << "</a>" << std::endl;
}

const char *Post::getPostUsername()
{
    return fPostUsername;
}
