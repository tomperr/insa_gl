#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <utility>

#include "Model.hpp"
#include "Sensor.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Measurement: public Model
{

public:

	// Variables statiques
    static string filename;      
    static bool fileHasBeenRead;      
    static bool objectsHaveBeenLinked;

    // Méthodes statiques
    static void ReadAll();
    static void LinkAll();

	// Attributs publiques
	static multimap<string, Measurement> measurements;

	// Méthodes publiques
	Measurement();
	Measurement(tm date, string id_sensor, string id_attribute, double value);
	vector< pair<Sensor, Measurement> > DetectFakeMeasurement();

	// Getters et Setters
	double GetValue();
	void SetValue(double value);

	tm GetDate();
	void SetDate(tm date);

	string GetIdSensor();
	void SetIdSensor(string id_sensor);

	string GetIdAttribute();
	void SetIdAttribute(string id_attribute);


protected:

	// Attributs protégés

	tm date;
	string id_sensor;
	string id_attribute;
	double value;

};

#endif