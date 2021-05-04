#ifndef SENSOR_HPP
#define SENSOR_HPP

#include "Model.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Sensor: public Model
{

public:

    // Attributs publiques
	static map<string, Sensor> sensors;

	// Variables statiques
    static string filename;      
    static bool fileHasBeenRead;      
    static bool objectsHaveBeenLinked;

	// Méthodes statiques
    static void ReadAll();
    static void LinkAll();

	// Méthodes publiques

	Sensor();
	Sensor(string id, double latitude, double longitude);

	// Getters et Setters

	string GetId();
	void SetId(string id);

	double GetLongitude();
	void SetLongitude(double longitude);

	double GetLatitude();
	void SetLatitude(double latitude);


protected:

	// Attributs protégés

	string id;
	double latitude;
	double longitude;



};

#endif