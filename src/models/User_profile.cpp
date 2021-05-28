#include <iostream>
#include <stdlib.h>
#include <fstream>

#include "User_profile.hpp"
#include "User.hpp"

string User_profile::filename = "./ressources/user_profiles.csv";
bool User_profile::fileHasBeenRead = false;
bool User_profile::objectsHaveBeenLinked = false;
map<string, User_profile> User_profile::user_profiles = map<string, User_profile>();

User_profile::User_profile (string Id,string Mdp,bool Trust,int Score,User_profile::Role role){
    this->id = Id;
    this->mdp = Mdp;
    this->trust = Trust;
    this->score = Score;
    this->role = role;
    //silence is golden ! oula
}
User_profile::User_profile ()
{

}


void User_profile::ReadAll()
{
    if(!User_profile::fileHasBeenRead)
    {
        ifstream file(User_profile::filename.c_str(), ifstream::in); 
    
        if(file.is_open())
        {
            string buffer;
            //getline(file, buffer); // Enlever la première ligne (nom des colonnes)

            while(!file.eof())
            {
                User_profile profile;

                getline(file, profile.id, ';');

                if(file.eof()) break;
                
                getline(file, profile.mdp, ';');

                string Role;
                getline(file, Role, ';');
                if (Role=="Admin")
                    profile.role = User_profile::Role::admin;
                else 
                    profile.role = User_profile::Role::private_user;

                string Trust;
                getline(file, Trust, ';');
                if (Trust =="True")
                    profile.trust =true;
                else 
                    profile.trust =false;
                
                profile.score = 0;
                getline(file, buffer); // Enlever le \r\n de fin de ligne

                User_profile::user_profiles.insert(make_pair(profile.id, profile));
            }
        }

        User_profile::fileHasBeenRead = true;
    }
}

void User_profile::LinkAll()
{
    for(auto& row : User_profile::user_profiles)
    {
        // find user
        auto returned_user = User::users.find(row.first);
        if (returned_user != User::users.end()) {
            User& user = returned_user->second;
            row.second.SetUser(&(user));
        }        
    }

    User_profile::objectsHaveBeenLinked = true;
}

User* User_profile::GetUser()
{
    return this->user;
}

void User_profile::SetUser(User* user)
{
    this->user = user;
}

void User_profile::SetFilename(string filename)
{
    User_profile::filename = filename;
}