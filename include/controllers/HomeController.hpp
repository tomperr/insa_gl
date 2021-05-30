#ifndef HOMECONTROLLER_HPP
#define HOMECONTROLLER_HPP

#include <iostream>
#include "UserController.hpp"
#include "AdminController.hpp"
#include "CleanerController.hpp"

class HomeController
{

public:

	HomeController();

	int ShowHome();
	void NavigateTo(int choice);

};

#endif