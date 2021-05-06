#ifndef PRIVATE_HPP
#define PRIVATE_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector> 
#include "User.hpp"
#include "Sensor.hpp"

using namespace std;

class Private : public User
{
    public:

    // Variable statique
    static map<string, Private> privates;

    //Méthode publique
    Private ();
    Private (string id, vector <Sensor> sensors);

	// Méthodes statiques
    static void ReadAll();
    static void LinkAll();

    vector <Sensor> GetSensors();
    bool GetTrust();
    void SetTrust(bool trust);
    void AddScore(int toBeAdded);

    protected:
    // Variables statiques
    static string filename;      
    static bool fileHasBeenRead;      
    static bool objectsHaveBeenLinked;

    vector <Sensor> sensors;

};

#endif