#ifndef PRIVATE_HPP
#define PRIVATE_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "User.hpp"
#include "Sensor.hpp"

class Sensor;

using namespace std;

class Private: public User
{
    public:

        // Variable statique
        static map<string, Private> privates;

        //Méthode publique
        Private ();
        Private (string id, vector <Sensor*> sensors);
        Private (string id_user, string id_sensor);


        // Méthodes statiques
        static void ReadAll();
        static void LinkAll();
        static void SetFilename(string filename);

        vector <Sensor*> GetSensors();
        void AddSensor(Sensor* s);

        bool GetTrust();
        void SetTrust(bool trust);

        void AddScore(int toBeAdded);

    protected:
        // Variables statiques
        static string filename;      
        static bool fileHasBeenRead;      
        static bool objectsHaveBeenLinked;

        vector <Sensor*> sensors;

};

#endif