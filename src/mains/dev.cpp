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

    cout << "test" << endl;
    Sensor::DetectFailedSensors(Sensor::sensors, 1);

    return 0;
}