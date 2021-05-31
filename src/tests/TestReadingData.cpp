#include "TestReadingData.hpp"

#include <assert.h>
#include <iostream>

#include "User.hpp"
#include "User_profile.hpp"
#include "Sensor.hpp"
#include "Cleaner.hpp"
#include "Measurement.hpp"

using namespace std;

void test_reading_users()
{
    User::SetFilename("./ressources/tests/reading_data/users.csv");
    User::ReadAll();

    assert(User::users.size() == 2);

    User::EmptyData();
}

void test_reading_user_profiles()
{
    User_profile::SetFilename("./ressources/tests/reading_data/user_profiles.csv");
    User_profile::ReadAll();

    assert(User_profile::user_profiles.size() == 2);

    User_profile::EmptyData();
}

void test_reading_sensors()
{
    Sensor::SetFilename("./ressources/tests/reading_data/sensors.csv");
    Sensor::ReadAll();

    assert(Sensor::sensors.size() == 2);

    Sensor::EmptyData();
}

void test_reading_measurements()
{
    Measurement::SetFilename("./ressources/tests/reading_data/measurements.csv");
    Measurement::ReadAll();

    assert(Measurement::measurements.size() == 24);

    Measurement::EmptyData();
}

void test_reading_cleaners()
{
    Cleaner::SetFilename("./ressources/tests/reading_data/cleaners.csv");
    Cleaner::ReadAll();

    assert(Cleaner::cleaners.size() == 2);

    Cleaner::EmptyData();
}

void test_reading_attributes()
{
    Attribute::SetFilename("./ressources/tests/reading_data/attributes.csv");
    Attribute::ReadAll();

    assert(Attribute::attributes.size() == 4);

    Attribute::EmptyData();
}