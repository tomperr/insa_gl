#include "Authentification.hpp"

bool Authentification::authenticated = false;
User* Authentification::user = nullptr;

bool Authentification::isAuth()
{
    return Authentification::authenticated;
}

bool Authentification::Auth(User* user)
{
    bool auth = false;

    if(user != nullptr && !Authentification::isAuth())
    {
        Authentification::user = user;
        Authentification::authenticated = true;
        auth = true;
    }

    return auth;
}

bool Authentification::Deauth()
{
    bool deauth = false;

    if(Authentification::isAuth())
    {
        Authentification::user = nullptr;
        Authentification::authenticated = false;
        deauth = true;
    }

    return deauth;
}

User* Authentification::getUser()
{
    return Authentification::user;
}