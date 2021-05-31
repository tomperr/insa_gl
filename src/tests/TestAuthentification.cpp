#include "TestAuthentification.hpp"

void ResetAuthentification()
{
    Authentification::user = nullptr;
    Authentification::authenticated = false;
}

void test_is_auth_ok1()
{
    ResetAuthentification();
    assert(Authentification::isAuth() == false);
}

void test_is_auth_ok2()
{
    ResetAuthentification();
    User u;
    Authentification::Auth(&u);
    assert(Authentification::isAuth() == true);
}

void test_auth_ok1()
{
    ResetAuthentification();
    User u;
    assert(Authentification::Auth(&u) == true);
}

void test_auth_ok2()
{
    ResetAuthentification();
    User u1;
    User u2;
    assert(Authentification::Auth(&u1) == true);
    Authentification::Deauth();
    assert(Authentification::Auth(&u2) == true);
}

void test_auth_ko()
{
    ResetAuthentification();
    User u1;
    User u2;
    assert(Authentification::Auth(&u1) == true);
    assert(Authentification::Auth(&u2) == false);
}

void test_deauth_ok()
{
    ResetAuthentification();
    User u1;
    Authentification::Auth(&u1);
    assert(Authentification::Deauth() == true);
}

void test_deauth_ko1()
{
    ResetAuthentification();
    assert(Authentification::Deauth() == false);
}

void test_deauth_ko2()
{
    ResetAuthentification();
    User u1;
    Authentification::Auth(&u1);
    assert(Authentification::Deauth() == true);
    assert(Authentification::Deauth() == false);
}

void test_getuser_ok1()
{
    ResetAuthentification();
    User u;
    Authentification::Auth(&u);
    assert(&u == Authentification::getUser());
}

void test_getuser_ok2()
{
    ResetAuthentification();
    User u1;
    User u2;
    Authentification::Auth(&u1);
    assert(&u1 == Authentification::getUser());
    Authentification::Deauth();
    assert(nullptr == Authentification::getUser());
    Authentification::Auth(&u2);
    assert(&u2 == Authentification::getUser());
    Authentification::Deauth();
    assert(nullptr == Authentification::getUser());
}

void test_getuser_limit()
{
    ResetAuthentification();
    assert(nullptr == Authentification::getUser());
}

void test_integration_ok()
{
    ResetAuthentification();
    std::string username = "mon_existance_est_vaine";
    std::string mdp = "ma_liberté_est_un_mensonge";
    User u;

    u.SetId(username);
    User_profile up(username, mdp, true, 0, User_profile::Role::private_user);
    u.SetProfile(&up);
    User::users.insert(make_pair(up.GetId(), u));

    assert(User::AuthenticateUser(username, mdp) == true);
    assert(Authentification::isAuth() == true);
    assert(Authentification::getUser() == &User::users[username]);

    User::users.erase(username);
}