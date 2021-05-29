#include <iostream>

#include "Attribute.hpp"
#include "Sensor.hpp"
#include "Measurement.hpp"
#include "Cleaner.hpp"
#include "User.hpp"
#include "User_profile.hpp"

using namespace std;

int main()
{
    // READING AND LINKING DATA
    Attribute::ReadAll();
    Sensor::ReadAll();
    Measurement::ReadAll();
    Cleaner::ReadAll();
    User::ReadAll();
    User_profile::ReadAll();

    Sensor::LinkAll();
    Measurement::LinkAll();
    Attribute::LinkAll();
    User::LinkAll();

    Private::ReadAll();
    Private::LinkAll();

    User_profile::LinkAll();

    for (auto& row: Private::privates)
    {
        cout << "id_private : " << row.second.GetId() << endl;
        for (Sensor* s: row.second.GetSensors())
        {
            cout << "id_private_sensor : " << s->GetId() << endl;
        }
    }

    Attribute::EmptyData();
    Sensor::EmptyData();
    Measurement::EmptyData();
    Cleaner::EmptyData();
    User::EmptyData();
    User_profile::EmptyData();
    Private::EmptyData();

    cout << "EMPTY" << endl;

    for (auto& row: Private::privates)
    {
        cout << "id_private : " << row.second.GetId() << endl;
        for (Sensor* s: row.second.GetSensors())
        {
            cout << "id_private_sensor : " << s->GetId() << endl;
        }
    }

    return 0;
}