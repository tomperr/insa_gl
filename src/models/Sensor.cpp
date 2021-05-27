#include <iostream>
#include <stdlib.h>
#include <map>

#include "Sensor.hpp"
#include "Measurement.hpp"
#include "Private.hpp"

using namespace std;

// Initialisation des variables statiques
string Sensor::filename = "./ressources/sensors.csv";
bool Sensor::fileHasBeenRead = false;
bool Sensor::objectsHaveBeenLinked = false;
map<string, Sensor> Sensor::sensors = map<string, Sensor>();


Sensor::Sensor()
{
	// silence id golden
}

Sensor::Sensor(string id, double latitude, double longitude)
{
	this->id = id;
	this->latitude = latitude;
	this->longitude = longitude;
}

void Sensor::ReadAll()
{
    if(!Sensor::fileHasBeenRead)
    {
        ifstream file(Sensor::filename.c_str(), ifstream::in); 
    
        if(file.is_open())
        {
            string buffer;
            //getline(file, buffer); // Enlever la première ligne (nom des colonnes)

            while(!file.eof())
            {
                Sensor newSensor;

                getline(file, newSensor.id, ';');

                if(file.eof()) break;

                string str_latitude;
                string str_longitude;

                getline(file, str_latitude, ';');
                getline(file, str_longitude, ';');

                newSensor.latitude = atof(str_latitude.c_str());
                newSensor.longitude = atof(str_longitude.c_str());

                getline(file, buffer); // Enlever le \r\n de fin de ligne

                Sensor::sensors.insert(make_pair(newSensor.id, newSensor));
            }
        }

        Sensor::fileHasBeenRead = true;
    }
}

void Sensor::LinkAll()
{
    for(auto& row : Measurement::measurements)
    {
        // finding measurement and sensor associations
        auto returned = Sensor::sensors.find(row.second.GetIdSensor());
        if (returned != Sensor::sensors.end()) {
            Sensor& s = returned->second;
            s.AddMeasurements(&(row.second));
        }
    }

    for(auto& row : Private::privates)
    {
        // finding private and sensor associations
        auto returned = Sensor::sensors.find(row.second.GetIdSensor());
        if (returned != Sensor::sensors.end()) {
            Sensor& s = returned->second;
            s.SetPrivate(&(row.second));
        }
    }

    Sensor::objectsHaveBeenLinked = true;
}

string Sensor::GetId()
{
	return this->id;
}

void Sensor::SetId(string id)
{
	this->id = id;
}

double Sensor::GetLongitude()
{
	return this->longitude;
}

void Sensor::SetLongitude(double longitude)
{
	this->longitude = longitude;
}

double Sensor::GetLatitude()
{
	return this->latitude;
}

void Sensor::SetLatitude(double latitude)
{
	this->latitude = latitude;
}


vector<Measurement*> Sensor::GetMeasurements()
{
    return this->measurements;
}

void Sensor::AddMeasurements(Measurement* measurement)
{
    this->measurements.push_back(measurement);
}

Private* Sensor::GetPrivate()
{
    return this->private_user;
}

void Sensor::SetPrivate(Private* private_user)
{
    this->private_user = private_user;
}