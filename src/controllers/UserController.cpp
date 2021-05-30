#include "UserController.hpp"

using namespace std;

UserController::UserController() {
	// silence is golden
}

void UserController::ShowLogin() {
	string username;
	string password;

	bool firsttime = true;
	bool logedin = false;
	
	if(Authentification::isAuth())
	{
		UserViews::LoginFailed(1);
	}
	else 
	{
		while(!Authentification::isAuth())
		{
			if(firsttime)
			{
				firsttime = false;
			}
			else
			{
				if(User::users.size() == 0)
				{
					UserViews::LoginFailed(2);
				}
				else
				{
					UserViews::LoginFailed(0);
				}
			}

			username = UserViews::GetUsername();
			password = UserViews::GetPassword();

			logedin = User::AuthenticateUser(username, password);
		}
	}

	if(logedin) UserViews::LoginSuccess();
}

void UserController::ShowLogout() {
	Authentification::Deauth();
	UserViews::LogoutSuccess();
}