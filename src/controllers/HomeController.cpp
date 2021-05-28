#include <iostream>

#include "HomeController.hpp"

#include "HomeViews.hpp"

using namespace std;

HomeController::HomeController() {
	// silence is golden
}

int HomeController::ShowHome() {
	return HomeViews::Home();
}

void HomeController::NavigateTo(int choice) {
	
	// here we'll call other controllers methods

	switch (choice)
	{
		case 1:
		{
			if(Authentification::isAuth())
			{
				// disconnection
				cout << "disconnection" << endl;
			}
			else
			{
				// connection
				cout << "connection" << endl;
			}
			break;
		}

		case 2:
		{
			// compute air quality
			cout << "compute air quality" << endl;
			break;
		}

		case 3:
		{
			// show data
			cout << "show data" << endl;
			break;
		}

		case 4:
		{
			// sort sensors by similitude
			cout << "sort sensors by similitude" << endl;
			break;
		}

		case 5:
		{
			// compute cleaner effect
			cout << "compute cleaner effect" << endl;
			break;
		}

		case 6:
		{
			if(Authentification::isAuth())
			{
				User* user = Authentification::getUser();
				User_profile* profile = user->GetProfile();

				if (profile->GetRole() == User_profile::Role::admin)
				{
					// show faulty sensors
					cout << "show faulty sensors" << endl;
				}
				else if (profile->GetRole() == User_profile::Role::private_user)
				{
					// show score
					cout << "show score" << endl;
				}
			}
			break;
		}

		case 7:
		{
			// detect fake/wrong data
			cout << "detect fake/wrong data" << endl;
		}
	}

}