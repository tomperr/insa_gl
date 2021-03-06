#include "Private.hpp"

using namespace std;

string Private::filename = "";
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
    for (auto& row : User::users)
    {
        if (row.second.GetProfile() != nullptr &&
            row.second.GetProfile()->GetRole() == User_profile::Role::private_user)
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

void Private::SetFilename(string filename)
{
    Private::filename = filename;
}

void Private::EmptyData()
{
    Private::privates = map<string, Private>();
    Private::objectsHaveBeenLinked = false;
    Private::fileHasBeenRead = false;
}