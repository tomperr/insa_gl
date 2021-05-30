#ifndef USERCONTROLLER_HPP
#define USERCONTROLLER_HPP

#include <iostream>
#include "UserViews.hpp"
#include "Authentification.hpp"
#include "User.hpp"

class UserController
{

public:

	UserController();

	void ShowLogin();
	void ShowLogout();

};

#endif