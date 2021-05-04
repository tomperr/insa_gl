#ifndef CLEANER_HPP
#define CLEANER_HPP

#include "Model.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

class Cleaner: public Model
{

public:

	// Attributs publiques

	static map<string, Cleaner> cleaners;

	// Méthodes publiques

	Cleaner();
	Cleaner(string id, double latitude, double longitude, tm activity_start, tm activity_end);

	// Méthodes statiques

	static void ReadAll();
    static void LinkAll();

	// Getters et Setters

	string GetId();
	void SetId(string id);

	double GetLongitude();
	void SetLongitude(double longitude);

	double GetLatitude();
	void SetLatitude(double latitude);

	tm GetActivityStart();
	void SetActivityStart(tm activity_start);

	tm GetActivityEnd();
	void SetActivityEnd(tm activity_end);


protected:
	// Attributs statiques

	static string filename;      
    static bool fileHasBeenRead;      
    static bool objectsHaveBeenLinked;

	// Attributs protégés

	string id;
	double latitude;
	double longitude;
	tm activity_start;
	tm activity_end;

};

#endif