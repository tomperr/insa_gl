#include <iostream>
#include <ctime>
#include <utility>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

#include "Measurement.hpp"
#include "Sensor.hpp"

using namespace std;

// Initialisation des variables statiques
string Measurement::filename = "./ressources/measurements.csv";
bool Measurement::fileHasBeenRead = false;
bool Measurement::objectsHaveBeenLinked = false;
multimap<string, Measurement> Measurement::measurements = multimap<string, Measurement>();

Measurement::Measurement()
{
	// silence id golden
}

Measurement::Measurement(tm date, string id_sensor, string id_attribute, double value)
{
	this->date = date;
	this->id_sensor = id_sensor;
	this->id_attribute = id_attribute;
	this->value = value;	
}

void Measurement::ReadAll()
{
    if(!Measurement::fileHasBeenRead)
    {
        ifstream file(Measurement::filename.c_str(), ifstream::in); 
    
        if(file.is_open())
        {
            string buffer;
            getline(file, buffer); // Enlever la première ligne (nom des colonnes)

            while(!file.eof())
            {
                Measurement newMeasurement;

                // TODO : NE FONCTIONNE PAS
                getline(file, buffer, ';');
                istringstream ss_acStart(buffer);
                ss_acStart >> get_time(&(newMeasurement.date), "%d/%m/%Y %R");

                // timestamp to 

                if(file.eof()) break;

                getline(file, newMeasurement.id_sensor, ';');
                getline(file, newMeasurement.id_attribute, ';');

                getline(file, buffer, ';');
                newMeasurement.value = atof(buffer.c_str());

                getline(file, buffer); // Enlever le \r\n de fin de ligne

                Measurement::measurements.insert(make_pair(newMeasurement.id_sensor, newMeasurement));
            }
        }

        Measurement::fileHasBeenRead = true;
    }
}

vector< pair<Sensor, Measurement> > Measurement::DetectFakeMeasurement()
{
	// just to compile before we implement it
	return vector< pair<Sensor, Measurement> >();
}

double Measurement::GetValue()
{
	return this->value;
}

void Measurement::SetValue(double value)
{
	this->value = value;
}

tm Measurement::GetDate()
{
	return this->date;
}

void Measurement::SetDate(tm date)
{
	this->date = date;
}

string Measurement::GetIdSensor()
{
	return this->id_sensor;
}

void Measurement::SetIdSensor(string id_sensor)
{
	this->id_sensor = id_sensor;
}

string Measurement::GetIdAttribute()
{
	return this->id_attribute;
}

void Measurement::SetIdAttribute(string id_attribute)
{
	this->id_attribute = id_attribute;
}