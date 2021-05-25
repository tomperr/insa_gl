#include "User_profile.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
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
                string mdp;
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
