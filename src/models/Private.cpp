#include "Private.hpp"

using namespace std;

string Private::filename = "./ressources/users.csv";
bool Private::fileHasBeenRead = false;
bool Private::objectsHaveBeenLinked = false;
map<string, Private> Private::privates = map<string, Private>();

Private::Private ()
{
    //silence is golden
}

Private :: Private(string id, vector <Sensor> sensors)
{
    this->id=id;
    this->sensors=sensors;
}

void Private::ReadAll()
{
    if(!Private::fileHasBeenRead)
    {
        ifstream file(Private::filename.c_str(), ifstream::in); 
    
        if(file.is_open())
        {
            string buffer;

            while(!file.eof())
            {
                getline(file,buffer,';');
                if(!Private::privates.count(buffer)){ //on rentre ici si c est la premiere fois que nous rencontrons ce user
                    Private newPrivate;

                    newPrivate.id=buffer;

                    getline(file,buffer,';');
                    Sensor::ReadAll();
                    map<string, Sensor>::iterator it;
                    it=Sensor::sensors.find(buffer);

                    newPrivate.sensors.push_back(it->second);
                    
                    Private::privates.insert(make_pair(newPrivate.id, newPrivate));
                }else{
                    map<string, Private>::iterator privateIterator;
                    privateIterator=Private::privates.find(buffer);

                    getline(file,buffer,';');
                    Sensor::ReadAll();
                    map<string, Sensor>::iterator sensorIterator;
                    sensorIterator=Sensor::sensors.find(buffer);

                    (privateIterator->second).sensors.push_back(sensorIterator->second);

                }
                getline(file, buffer);
            }        
        }

        Private::fileHasBeenRead = true;
    }
}

vector<Sensor> Private::GetSensors()
{
    return sensors;
}

bool Private::GetTrust()
{
    return profile->GetTrust();
}

void Private::SetTrust(bool newTrust)
{
    profile->SetTrust(newTrust);
}

void Private::AddScore(int toBeAdded)
{
    this->GetProfile()->AddToScore(toBeAdded);
}