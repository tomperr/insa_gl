#include "User.hpp"
#include "User_profile.hpp"

string User::filename = "./ressources/users.csv";
bool User::fileHasBeenRead = false;
bool User::objectsHaveBeenLinked = false;
map<string, User> User::users = map<string, User>();

void User::ReadAll()
{
    if(!User::fileHasBeenRead)
    {
        ifstream file(User::filename.c_str(), ifstream::in); 
    
        if(file.is_open())
        {
            string buffer;

            while(!file.eof())
            {
                User newUser;

                getline(file,buffer,';');
                newUser.SetId(buffer);

                getline(file,buffer,';');
                newUser.SetIdSensor(buffer);
                
                User::users.insert(make_pair(newUser.GetId(), newUser));
                
                getline(file, buffer);
            }        
        }

        User::fileHasBeenRead = true;
    }
}

void User::LinkAll()
{
    for(auto& row : User::users)
    {
        // find user_profile
        auto returned_profile = User_profile::user_profiles.find(row.first);
        if (returned_profile != User_profile::user_profiles.end())
        {
            User_profile& user_profile = returned_profile->second;
            row.second.SetProfile(&(user_profile));
        }
    }

    User::objectsHaveBeenLinked = true;
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

User_profile* User::GetProfile()
{
    return this->profile;
}

void User::SetProfile(User_profile* profile)
{
    this->profile = profile;
}

string User::GetId()
{
    return this->id;
}

void User::SetId(string id)
{
    this->id = id;
}

string User::GetIdSensor()
{
	return this->id_sensor;
}

void User::SetIdSensor(string id)
{
	this->id_sensor = id;
}

void User::SetFilename(string filename)
{
    User::filename = filename;
}