#ifndef USER_PROFILE_HPP
#define USER_PROFILE_HPP

#include <string>
#include <iostream>
#include <map>

#include "Model.hpp"
#include "User.hpp"

class User;

using namespace std;

class User_profile : public Model
{
    public:
        static map<string, User_profile> user_profiles;
        
        enum Role {private_user, admin};

        // Méthodes statiques
        static void ReadAll();
        static void LinkAll();
        static void SetFilename(string filename);
        static void EmptyData();

        // Méthodes publiques
        User_profile ();
        User_profile (string Id,string Mdp,bool Trust,int Score, User_profile::Role Role);

        string GetId(){ return id; }
        string GetPassword(){ return mdp; }

        bool GetTrust(){ return trust; }
        void SetTrust(bool newTrust){ trust = newTrust;}

        int GetScore(){ return score; }
        void SetScore(int newScore){ score = newScore; }

        void AddToScore(int toBeAdded){ score += toBeAdded; }

        User_profile::Role GetRole(){ return role; }
        void SetRole(User_profile::Role newRole){ this->role = newRole;}

        User* GetUser();
        void SetUser(User* user);
        
    protected:
        // Variables statiques
        static string filename;      
        static bool fileHasBeenRead;      
        static bool objectsHaveBeenLinked;

        string id;
        string mdp;
        bool trust;
        int score;
        User_profile::Role role;

        // Navigation
        User* user;
};

#endif