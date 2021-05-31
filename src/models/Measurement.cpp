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
    this->sensor = nullptr;
}

Measurement::Measurement(tm date, string id_sensor, string id_attribute, double value)
{
	this->date = date;
	this->id_sensor = id_sensor;
	this->id_attribute = id_attribute;
	this->value = value;
    this->sensor = nullptr;
}

void Measurement::ReadAll()
{
    if(!Measurement::fileHasBeenRead)
    {
        ifstream file(Measurement::filename.c_str(), ifstream::in); 
    
        if(file.is_open())
        {
            string buffer;
            // getline(file, buffer); // Enlever la première ligne (nom des colonnes)

            while(!file.eof())
            {
                Measurement newMeasurement;

                getline(file, buffer, ';');
                istringstream ss_acStart(buffer);
                ss_acStart >> get_time(&(newMeasurement.date), "%Y-%m-%d %H:%M:%S");

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

void Measurement::LinkAll()
{
    for(auto& row : Measurement::measurements)
    {
        // finding associated sensor
        auto returned_sensor = Sensor::sensors.find(row.second.GetIdSensor());
        if (returned_sensor != Sensor::sensors.end()) {
            Sensor& s = returned_sensor->second;
            row.second.SetSensor(&s);
        }

        // finding associated attribute
        auto returned_attribute = Attribute::attributes.find(row.second.GetIdAttribute());
        if (returned_attribute != Attribute::attributes.end()) {
            Attribute& attr = returned_attribute->second;
            row.second.SetAttribute(&attr);
        }
        
    }

    Measurement::objectsHaveBeenLinked = true;
    
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

tm* Measurement::GetDate()
{
	return &(this->date);
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

Sensor* Measurement::GetSensor()
{
    return this->sensor;
}

void Measurement::SetSensor(Sensor* s)
{
    this->sensor = s;
}

Attribute* Measurement::GetAttribute()
{
    return this->attribute;
}

void Measurement::SetAttribute(Attribute* attr)
{
    this->attribute = attr;
}

void Measurement::SetFilename(string filename)
{
    Measurement::filename = filename;
}

void Measurement::EmptyData()
{
    Measurement::measurements = multimap<string, Measurement>();
    Measurement::objectsHaveBeenLinked = false;
    Measurement::fileHasBeenRead = false;
}
