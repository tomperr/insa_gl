#ifndef SENSOR_HPP
#define SENSOR_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

#include "Model.hpp"
#include "Measurement.hpp"
#include "Private.hpp"

class Measurement;
class Private;

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
	static void SetFilename(string filename);
	static void EmptyData();
	static vector<Sensor> DetectFailedSensors(map<string, Sensor> sensors, double errorMarginPercentage);

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

	vector<Measurement*> GetMeasurements();
	void AddMeasurements(Measurement* measurement);

	Private* GetPrivate();
	void SetPrivate(Private* private_user);



protected:

	// Attributs protégés
	string id;
	double latitude;
	double longitude;

	// Navigation
	vector<Measurement*> measurements;
	Private* private_user;

};

#endif