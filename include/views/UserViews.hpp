#ifndef USERVIEWS_HPP
#define USERVIEWS_HPP

#include <iostream>

using namespace std;

class UserViews {
    public:
    string GetUsername();
    string GetPassword();
    void LoginSuccess();
    void LoginFailed(int code);
};

#endif