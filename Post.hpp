#pragma once

#include "PostType.hpp"
#include <fstream>

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

    void writePostToFile(std::ofstream &file);

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

    void htmlFileStart(std::ofstream &file);

    void htmlFileEnd(std::ofstream &file);

    void textPostToFile(std::ofstream &file);

    void linkPostToFile(std::ofstream &file);

    void imagePostToFile(std::ofstream &file);

};
