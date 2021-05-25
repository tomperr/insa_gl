#include <iostream>
#include <ctime>
#include "Cleaner.hpp"
#include <sstream>

using namespace std;

// Initialisation des variables statiques
string Cleaner::filename = "./ressources/cleaners.csv";
bool Cleaner::fileHasBeenRead = false;
bool Cleaner::objectsHaveBeenLinked = false;
map<string, Cleaner> Cleaner::cleaners = map<string, Cleaner>();

Cleaner::Cleaner()
{
	// silence id golden
}

Cleaner::Cleaner(string id, double latitude, double longitude,
	tm activity_start, tm activity_end)
{
	this->id = id;
	this->latitude = latitude;
	this->longitude = longitude;
	this->activity_start = activity_start;
	this->activity_end = activity_end;
}

void Cleaner::ReadAll()
{
    if(!Cleaner::fileHasBeenRead)
    {
        ifstream file(Cleaner::filename.c_str(), ifstream::in); 
    
        if(file.is_open())
        {
            string buffer;

            while(!file.eof())
            {
                Cleaner newCleaner;

                getline(file, newCleaner.id, ';');

                if(file.eof()) break;
                
                getline(file, buffer, ';');
                newCleaner.latitude = stod(buffer);

                getline(file, buffer, ';');
                newCleaner.longitude = stod(buffer);

                struct tm tmBuffer;

                getline(file, buffer, ';');
                std::istringstream ss_acStart(buffer);
                ss_acStart >> std::get_time(&tmBuffer, "%Y-%m-%d %H:%M:%S");
                newCleaner.activity_start = tmBuffer;

                getline(file, buffer, ';');
                std::istringstream ss_acEnd(buffer);
                ss_acEnd >> std::get_time(&tmBuffer, "%Y-%m-%d %H:%M:%S");
                newCleaner.activity_end = tmBuffer;

                getline(file, buffer); // Enlever le \r\n de fin de ligne

                Cleaner::cleaners.insert(make_pair(newCleaner.id, newCleaner));
            }
        }

        Cleaner::fileHasBeenRead = true;
    }
}

string Cleaner::GetId()
{
	return this->id;
}

void Cleaner::SetId(string id)
{
	this->id = id;
}

double Cleaner::GetLongitude()
{
	return this->longitude;
}

void Cleaner::SetLongitude(double longitude)
{
	this->longitude = longitude;
}

double Cleaner::GetLatitude()
{
	return this->latitude;
}

void Cleaner::SetLatitude(double latitude)
{
	this->latitude = latitude;
}

tm Cleaner::GetActivityStart()
{
	return this->activity_start;
}

void Cleaner::SetActivityStart(tm activity_start)
{
	this->activity_start = activity_start;
}

tm Cleaner::GetActivityEnd()
{
	return this->activity_end;
}

void Cleaner::SetActivityEnd(tm activity_end)
{
	this->activity_end = activity_end;
}