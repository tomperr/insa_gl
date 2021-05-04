#ifndef USER_PROFILE_HPP
#define USER_PROFILE_HPP

#include <string>
#include <iostream>
#include <map>
#include "Model.hpp"

using namespace std;

class User_profile : public Model
{
    public:
    static map<string, User_profile> user_profiles;

	// Méthodes statiques
    static void ReadAll();
    static void LinkAll();

    string GetId(){ return id; }
    string GetPassword(){ return mdp; }
    bool GetTrust(){ return trust; }
    void SetTrust(bool newTrust){ trust = newTrust;}
    int GetScore(){ return score; }
    void SetScore(int newScore){ score = newScore; }
    void AddToScore(int toBeAdded){ score += toBeAdded; }
    
    protected:
    // Variables statiques
    static string filename;      
    static bool fileHasBeenRead;      
    static bool objectsHaveBeenLinked;

    string id;
    string mdp;
    enum role {private_user, admin};
    bool trust;
    int score;
};

#endif