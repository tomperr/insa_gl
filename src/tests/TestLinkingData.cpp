#include "TestLinkingData.hpp"

#include <assert.h>
#include <iostream>

#include "User.hpp"
#include "User_profile.hpp"
#include "Sensor.hpp"
#include "Cleaner.hpp"
#include "Measurement.hpp"

void test_linking_users()
{
    User::SetFilename("./ressources/tests/reading_data/users.csv");
    User_profile::SetFilename("./ressources/tests/reading_data/user_profiles.csv");

    User::ReadAll();
    User_profile::ReadAll();

    User::LinkAll();
    User_profile::LinkAll();

    for (auto row: User::users)
    {
        User user = row.second;

        assert(user.GetProfile() != nullptr);
        assert(user.GetProfile()->GetId() == user.GetId());
    }

    User::EmptyData();
    User_profile::EmptyData();
}

void test_linking_user_profiles()
{
    User::SetFilename("./ressources/tests/reading_data/users.csv");
    User_profile::SetFilename("./ressources/tests/reading_data/user_profiles.csv");

    User::ReadAll();
    User_profile::ReadAll();

    User::LinkAll();
    User_profile::LinkAll();

    for (auto row: User_profile::user_profiles)
    {
        User_profile profile = row.second;

        assert(profile.GetUser() != nullptr);
        assert(profile.GetUser()->GetId() == profile.GetId());
    }

    User::EmptyData();
    User_profile::EmptyData();
}

void test_linking_sensors()
{
    Sensor::SetFilename("./ressources/tests/reading_data/sensors.csv");
    User::SetFilename("./ressources/tests/reading_data/users.csv");
    User_profile::SetFilename("./ressources/tests/reading_data/user_profiles.csv");
    Measurement::SetFilename("./ressources/tests/reading_data/measurements.csv");

    // READING AND LINKING DATA
    Sensor::ReadAll();
    Measurement::ReadAll();
    User::ReadAll();
    User_profile::ReadAll();
    Private::ReadAll();

    Sensor::LinkAll();
    User::LinkAll();
    Private::LinkAll();
    User_profile::LinkAll();

    for (auto row: Sensor::sensors)
    {
        Sensor sensor = row.second;
        assert(sensor.GetMeasurements().size() > 0);
    }

    Sensor::EmptyData();
    User::EmptyData();
    User_profile::EmptyData();
    Measurement::EmptyData();
    Private::EmptyData();
}

void test_linking_measurements()
{
    Measurement::SetFilename("./ressources/tests/reading_data/measurements.csv");
    Attribute::SetFilename("./ressources/tests/reading_data/attributes.csv");
    Sensor::SetFilename("./ressources/tests/reading_data/sensors.csv");

    Measurement::ReadAll();
    Attribute::ReadAll();
    Sensor::ReadAll();

    Measurement::LinkAll();

    for (auto row: Measurement::measurements)
    {
        Measurement m = row.second;

        assert(m.GetAttribute() != nullptr);
        assert(m.GetSensor() != nullptr);
    }

    Measurement::EmptyData();
    Attribute::EmptyData();
    Sensor::EmptyData();
}

void test_linking_attributes()
{
    Measurement::SetFilename("./ressources/tests/reading_data/measurements.csv");
    Attribute::SetFilename("./ressources/tests/reading_data/attributes.csv");

    Measurement::ReadAll();
    Attribute::ReadAll();

    Attribute::LinkAll();

    for (auto row: Attribute::attributes)
    {
        Attribute attr = row.second;

        assert(attr.GetMeasurements().size() != 0);
    }

    Measurement::EmptyData();
    Attribute::EmptyData();
    Sensor::EmptyData();
}
