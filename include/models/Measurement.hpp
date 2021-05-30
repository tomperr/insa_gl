#ifndef MEASUREMENT_HPP
#define MEASUREMENT_HPP

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Model.hpp"
#include "Sensor.hpp"
#include "Attribute.hpp"

class Sensor;
class Attribute;

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
	static void SetFilename(string filename);
	static void EmptyData();

	// Attributs publiques
	static multimap<string, Measurement> measurements;

	// Méthodes publiques
	Measurement();
	Measurement(tm date, string id_sensor, string id_attribute, double value);
	vector< pair<Sensor, Measurement> > DetectFakeMeasurement();

	// Getters et Setters
	double GetValue();
	void SetValue(double value);

	tm* GetDate();
	void SetDate(tm date);

	string GetIdSensor();
	void SetIdSensor(string id_sensor);

	string GetIdAttribute();
	void SetIdAttribute(string id_attribute);

	Sensor* GetSensor();
	void SetSensor(Sensor* s);

	Attribute* GetAttribute();
	void SetAttribute(Attribute* attr);

protected:

	// Attributs protégés
	Sensor* sensor;
	Attribute* attribute;

	tm date;
	string id_sensor;
	string id_attribute;
	double value;

};

#endif