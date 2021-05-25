#include "User.hpp"
#include "User_profile.hpp"

string User::filename = "./ressources/users.csv";
bool User::fileHasBeenRead = false;
bool User::objectsHaveBeenLinked = false;
map<string, User> User::users = map<string, User>();

User_profile* User::GetProfile()
{
    return profile;
}

bool User::AuthenticateUser(string username, string password)
{
    if ( User::users.count(username) > 0  &&  User::users[username].GetProfile() != nullptr
        && User::users[username].GetProfile()->GetPassword() == password )
    {
        // Auth(users[username]);
        return true;
    }
    return false;
}

string User::GetIdSensor()
{
	return this->id_sensor;
}

void User::SetIdSensor(string id)
{
	this->id_sensor = id;
}