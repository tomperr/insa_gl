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

vector<Sensor> Cleaner::getSensorsInCircularAreaByRadius(Cleaner aCleaner, int radius)
{
    double longitude = aCleaner.longitude;
    double latitude = aCleaner.latitude;
    
    Sensor::ReadAll();
    vector<Sensor> sensorsInsideTheArea = vector<Sensor> ();
    map<string,Sensor>::iterator sensorIterator;
    for(sensorIterator=Sensor::sensors.begin();sensorIterator!=Sensor::sensors.end();++sensorIterator){
        
        int R=6371;

        double latRadian_1 =(sensorIterator->second).GetLatitude()*M_PI/180;
        double latRadian_2 = latitude*M_PI/180;
        double deltaLatRadian = ((sensorIterator->second).GetLatitude() - latitude)*M_PI/180;
        double deltaLongRadian = ((sensorIterator->second).GetLongitude() - longitude)*M_PI/180;

        double a=sin(deltaLatRadian/2)*sin(deltaLatRadian/2)+ cos(latRadian_1)*cos(latRadian_2)*sin(deltaLongRadian/2)*sin(deltaLongRadian/2);
        double c= 2*atan2(sqrt(a),sqrt(1-a));

        double distance = R*c;
        if(distance<=radius)
            sensorsInsideTheArea.push_back(sensorIterator->second);
    }
    
    return sensorsInsideTheArea;
}

vector<double> Cleaner::ComputeCleanerEffectOnArea(Cleaner aCleaner, int radius)
{
    tm activityStart=aCleaner.activity_start;
    tm activityEnd =aCleaner.activity_end;
    double sommeProgressionOzone=0;
    double sommeProgressionSoufre=0;
    double sommeProgressionAzote=0;
    double sommeProgressionFines=0;
    int nombreDeCapteurs=0;
    vector<Sensor> SensorsInCircularArea = getSensorsInCircularAreaByRadius(aCleaner , radius);
    if(!SensorsInCircularArea.size()){
        vector<double> v {0,0,0,0};
        return v;
    } 

    vector<Sensor>::iterator it;
    for(it=SensorsInCircularArea.begin();it!=SensorsInCircularArea.end();++it){
        ++nombreDeCapteurs;
        double ozoneValueBefore =0; 
        double ozoneValueAfter =0;
        double soufreValueBefore=0 ; 
        double soufreValueAfter=0 ;
        double azoteValueBefore =0 ; 
        double azoteValueAfter =0;
        double finesValueBefore =0; 
        double finesValueAfter =0;
        vector<Measurement*> measurements = it->GetMeasurements();
        for (auto& row: measurements){

            if((row)->GetIdAttribute()=="O3" && difftime(mktime((row)->GetDate()),mktime(&activityStart))<0){
                ozoneValueBefore=(row)->GetValue();
                continue;
            }if((row)->GetIdAttribute()=="O3" && difftime(mktime((row)->GetDate()),mktime(&activityStart))>0 && difftime(mktime((row)->GetDate()),mktime(&activityEnd))<0){
                ozoneValueAfter=(row)->GetValue();
                continue;
            }if((row)->GetIdAttribute()=="SO2" && difftime(mktime((row)->GetDate()),mktime(&activityStart))<0){
                soufreValueBefore=(row)->GetValue();
                continue;
            }if((row)->GetIdAttribute()=="SO2" && difftime(mktime((row)->GetDate()),mktime(&activityStart))>0 && difftime(mktime((row)->GetDate()),mktime(&activityEnd))<0){
                soufreValueAfter=(row)->GetValue();
                continue;
            }if((row)->GetIdAttribute()=="NO2" && difftime(mktime((row)->GetDate()),mktime(&activityStart))<0){
                azoteValueBefore=(row)->GetValue();
                continue;
            }if((row)->GetIdAttribute()=="NO2" && difftime(mktime((row)->GetDate()),mktime(&activityStart))>0 && difftime(mktime((row)->GetDate()),mktime(&activityEnd))<0){
                azoteValueAfter=(row)->GetValue();
                continue;
            }if((row)->GetIdAttribute()=="PM10" && difftime(mktime((row)->GetDate()),mktime(&activityStart))<0){
                finesValueBefore=(row)->GetValue();
                continue;
            }if((row)->GetIdAttribute()=="PM10" && difftime(mktime((row)->GetDate()),mktime(&activityStart))>0 && difftime(mktime((row)->GetDate()),mktime(&activityEnd))<0){
                finesValueAfter=(row)->GetValue();
                continue;
            }
        }

        sommeProgressionOzone+=(1-ozoneValueAfter/ozoneValueBefore);
        sommeProgressionAzote+=(1-azoteValueAfter/azoteValueBefore);
        sommeProgressionSoufre+=(1-soufreValueAfter/soufreValueBefore);
        sommeProgressionFines+=(1-finesValueAfter/finesValueBefore);

    }

    double moyenneProgressionOzone=sommeProgressionOzone/nombreDeCapteurs;
    double moyenneProgressionAzote=sommeProgressionAzote/nombreDeCapteurs;
    double moyenneProgressionSoufre=sommeProgressionSoufre/nombreDeCapteurs;
    double moyenneProgressionFines=sommeProgressionFines/nombreDeCapteurs;

    vector <double> moyenneProgression= vector<double>();
    moyenneProgression.push_back(100*moyenneProgressionOzone);
    moyenneProgression.push_back(100*moyenneProgressionAzote);
    moyenneProgression.push_back(100*moyenneProgressionSoufre);
    moyenneProgression.push_back(100*moyenneProgressionFines);
    
    return moyenneProgression;
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

void Cleaner::SetFilename(string filename)
{
    Cleaner::filename = filename;
}

void Cleaner::EmptyData()
{
    Cleaner::cleaners = map<string, Cleaner>();
    Cleaner::objectsHaveBeenLinked = false;
    Cleaner::fileHasBeenRead = false;
}