#ifndef AUTHENTIFICATION_HPP
#define AUTHENTIFICATION_HPP

#include "User.hpp"

class Authentification
{
    public:
    static User* user;
    static bool authenticated;

    static bool isAuth();
    static bool Auth(User* user);
    static bool Deauth();
    static User* getUser();
};

#endif