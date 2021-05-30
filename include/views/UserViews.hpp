#ifndef USERVIEWS_HPP
#define USERVIEWS_HPP

#include <iostream>

using namespace std;

class UserViews {
    public:
    static string GetUsername();
    static string GetPassword();
    static void LoginSuccess();
    static void LoginFailed(int code);
    static void LogoutSuccess();
};

#endif