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
    int nbFailed = 0;
        
    for(const auto& elem : sensors){ // Pour chaque capteur passé en paramètre
        int lat = ((Sensor) elem.second).GetLatitude();
        int lon = ((Sensor) elem.second).GetLongitude();
        
        vector<Measurement*> measurements = ((Sensor) elem.second).GetMeasurements();
        double donneesInitiales[4];
        for(int i=0; i<4; i++){
            donneesInitiales[i] = measurements[measurements.size()-1-i]->GetValue();
        }
         
        Sensor listeVoisins[sensors.size()];
        int count = 0;
        
        for(const auto& toCompare : sensors){ // On retraverse la liste pour trouver les sensors voisins
            if( ((Sensor) elem.second).GetId() != ((Sensor) toCompare.second).GetId()){ 
                int latC = ((Sensor) toCompare.second).GetLatitude();
                int lonC = ((Sensor) toCompare.second).GetLongitude();
                int distance = sqrt(pow(lat-latC,2)+pow(lon-lonC,2));
                
                if(distance<0.1){ // Si le capteur est assez proche de celui qui nous intéresse
                    listeVoisins[count] = (Sensor) toCompare.second; // On le rajoute à la liste des voisins
                    count++;
                }
            }
        }
        
        double moyenneDonneesVoisins[4]; // Nous allons faire la moyenne des données des voisins ...
        double coef; // ... et comparer cette moyenne aux données du sensor
        
        for(int i=0; i<count; i++){ // On traverse la liste des voisins pour faire la moyenne
            vector<Measurement*> measurements = listeVoisins[i].GetMeasurements();
            for(int i=0; i<4; i++){
                moyenneDonneesVoisins[i] += measurements[measurements.size()-1-i]->GetValue();
            }
            coef++;
        }

        int wrongMeasures = 0;
        for(int i=0; i<4; i++){
            moyenneDonneesVoisins[i] = moyenneDonneesVoisins[i]/coef;
            double comparison = abs(donneesInitiales[i]/moyenneDonneesVoisins[i] - 1)*100;
            if(comparison > errorMarginPercentage){
                wrongMeasures++;
            }
        }
        if(wrongMeasures>2){
            //listFailedSensors.insert(make_pair(nbFailed, (Sensor) elem.second));
            failed_sensors.push_back((Sensor) elem.second);
            nbFailed++;
        }
    }
    return failed_sensors;
}