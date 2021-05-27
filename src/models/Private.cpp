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

Private :: Private(string id, vector <Sensor*> sensors)
{
    this->id=id;
    this->sensors=sensors;
}

Private::Private (string id_user, string id_sensor)
{
    this->id = id_user;
    this->id_sensor = id_sensor;
}

void Private::ReadAll()
{

    // Private must not read from file but from users and user_profiles already loaded

    /*
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

                    newPrivate.sensors.push_back(&(it->second));
                    
                    Private::privates.insert(make_pair(newPrivate.id, newPrivate));
                }else{
                    map<string, Private>::iterator privateIterator;
                    privateIterator=Private::privates.find(buffer);

                    getline(file,buffer,';');
                    Sensor::ReadAll();
                    map<string, Sensor>::iterator sensorIterator;
                    sensorIterator=Sensor::sensors.find(buffer);

                    (privateIterator->second).sensors.push_back(&(sensorIterator->second));

                }
                getline(file, buffer);
            }        
        }

        Private::fileHasBeenRead = true;
    }
    */

    for (auto& row : User::users)
    {
        if (row.second.GetProfile()->GetRole() == User_profile::Role::private_user)
        {
            Private new_private(row.second.GetId(), row.second.GetIdSensor());
            new_private.SetProfile(row.second.GetProfile());
            Private::privates.insert(make_pair(new_private.GetId(), new_private));
        }
    }

    Private::fileHasBeenRead = true;
}

void Private::LinkAll()
{
    for(auto& row : Private::privates)
    {
        // finding associated sensor
        auto returned_sensor = Sensor::sensors.find(row.second.GetIdSensor());
        if (returned_sensor != Sensor::sensors.end()) {
            Sensor& s = returned_sensor->second;
            row.second.AddSensor(&(s));
        }        
        
    }

    Private::objectsHaveBeenLinked = true;
    
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

vector <Sensor*> Private::GetSensors()
{
    return this->sensors;
}

void Private::AddSensor(Sensor* s)
{
    this->sensors.push_back(s);
}