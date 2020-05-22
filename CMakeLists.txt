cmake_minimum_required(VERSION 3.16)
project(FMIBOOK_FN45711)

set(CMAKE_CXX_STANDARD 14)

add_executable(FMIBOOK_FN45711 main.cpp UserTiers.cpp UserTiers.hpp SystemActions.cpp SystemActions.hpp UserData.cpp UserData.hpp MainNetworkEngine.cpp MainNetworkEngine.hpp ActionPermissions.cpp ActionPermissions.hpp UserDatabase.cpp UserDatabase.hpp Post.cpp Post.hpp PostType.cpp PostType.hpp PostsDatabase.cpp PostsDatabase.hpp)