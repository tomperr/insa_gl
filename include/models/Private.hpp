#ifndef PRIVATE_HPP
#define PRIVATE_HPP

#include <iostream>
#include <string>
#include <map>
#include "User.hpp"

using namespace std;

class Private : public User
{
    public:

    // Variable statique
    static map<string, Private> privates;

	// Méthodes statiques
    static void ReadAll();
    static void LinkAll();

    bool GetTrust();
    void SetTrust(bool trust);
    void AddScore(int toBeAdded);

    protected:
    // Variables statiques
    static string filename;      
    static bool fileHasBeenRead;      
    static bool objectsHaveBeenLinked;

};

#endif