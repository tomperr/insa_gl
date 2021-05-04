#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>
#include <list>
#include <map>
#include "User_profile.hpp"
#include "Model.hpp"

using namespace std;

class User : public Model
{
    
    public:

    // Variable statique
    static map<string, User> users;

	// Méthodes statiques
    static void ReadAll();
    static void LinkAll();

    User_profile* GetProfile();
    bool AuthenticateUser(string username, string password);
    
    protected:
    // Variables statiques
    static string filename;      
    static bool fileHasBeenRead;      
    static bool objectsHaveBeenLinked;

    string id;
    User_profile* profile;
};

#endif