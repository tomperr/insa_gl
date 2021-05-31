#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <list>
#include <map>

#include "Model.hpp"
#include "User_profile.hpp"
#include "Authentification.hpp"

class User_profile;
class Authentificate;

using namespace std;

class User : public Model
{
    
    public:

        // Variable statique
        static map<string, User> users;

        User();

        // Méthodes statiques
        static void ReadAll();
        static void LinkAll();
        static void SetFilename(string filename);
        static void EmptyData();

        static bool AuthenticateUser(string username, string password);

        User_profile* GetProfile();
        void SetProfile(User_profile* profile);

        string GetId();
        void SetId(string id);

        string GetIdSensor();
        void SetIdSensor(string id);
    
    protected:

        // Variables statiques
        static string filename;      
        static bool fileHasBeenRead;      
        static bool objectsHaveBeenLinked;

        string id;
        string id_sensor;

        // Navigation
        User_profile* profile;
};

#endif