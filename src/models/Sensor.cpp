#include <iostream>
#include <stdlib.h>
#include <map>
#include <cmath>

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
    this->SetPrivate(nullptr);
}

Sensor::Sensor(string id, double latitude, double longitude)
{
	this->id = id;
	this->latitude = latitude;
	this->longitude = longitude;
    this->SetPrivate(nullptr);
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
    (this->measurements).push_back(measurement);
}

Private* Sensor::GetPrivate()
{
    return this->private_user;
}

void Sensor::SetPrivate(Private* private_user)
{
    this->private_user = private_user;
}

void Sensor::SetFilename(string filename)
{
    Sensor::filename = filename;
}

void Sensor::EmptyData()
{
    Sensor::sensors = map<string, Sensor>();
    Sensor::objectsHaveBeenLinked = false;
    Sensor::fileHasBeenRead = false;
}

vector<Sensor> Sensor::DetectFailedSensors(map<string, Sensor> sensors, double errorMarginPercentage)
{
    //map<int, Sensor> listFailedSensors = map<int, Sensor>();
    vector<Sensor> failed_sensors = vector<Sensor>();

    for(const auto& elem : sensors)
    {
        Sensor sensor = elem.second;
        vector<Measurement*> measurements = sensor.GetMeasurements();

        double lastMeasurements[4];
        for(int i=0; i<4; i++){
            lastMeasurements[i] = measurements[measurements.size()-1-(3-i)]->GetValue();
        }

        vector<Sensor> listeVoisins;
        for(const auto& toCompare : sensors){ // On retraverse la liste pour trouver les sensors voisins
            if( ((Sensor) elem.second).GetId() != ((Sensor) toCompare.second).GetId()){ 
                int latC = ((Sensor) toCompare.second).GetLatitude();
                int lonC = ((Sensor) toCompare.second).GetLongitude();
                int distance = sqrt(pow(sensor.GetLatitude()-latC,2)+pow(sensor.GetLongitude()-lonC,2));
                
                if(distance<0.1){ // Si le capteur est assez proche de celui qui nous intéresse
                    listeVoisins.push_back((Sensor)(toCompare.second));
                }
            }
        }

        double moyennesTotalVoisins[4];
        for(int i=0; i<4; i++)
        {
            moyennesTotalVoisins[i] = 0;
        }

        for (Sensor voisin: listeVoisins)
        {

            vector<Measurement*> voisin_measurements = voisin.GetMeasurements();

            double moyenneCurrentVoisin[4];
            for(int i=0; i<4; i++)
            {
                moyenneCurrentVoisin[i] = 0;
            }

            for (int i=0; i< (int) (voisin_measurements.size()); i++)
            {
                moyenneCurrentVoisin[i%4] += voisin_measurements[i]->GetValue();
            }

            for(int i=0; i<4; i++)
            {
                moyenneCurrentVoisin[i] /= (voisin_measurements.size()/4);
            }

            for(int i=0; i<4; i++)
            {
                moyennesTotalVoisins[i] += moyenneCurrentVoisin[i];
            }

        }

        for(int i=0; i<4; i++)
        {
            moyennesTotalVoisins[i] /= listeVoisins.size();
        }

        int wrongMeasures = 0;
        for(int i=0; i<4; i++){
            double comparison = abs(lastMeasurements[i]/moyennesTotalVoisins[i] - 1)*100;

            if(comparison > errorMarginPercentage){
                wrongMeasures++;
            }

        }
        if(wrongMeasures>2){
            failed_sensors.push_back((Sensor) elem.second);
        }

    }

    return failed_sensors;

}