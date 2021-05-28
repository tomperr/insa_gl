#define run(x) runHelper(#x, x)

#include <iostream>
#include <assert.h>

using namespace std;

int runned = 0;

void runHelper(const char *f_name, void (*f)(void))
{
    cout << f_name << "... ";
    (*f)();
    cout << "success" << endl;
    runned++;
}

#include "Attribute.hpp"
#include "Sensor.hpp"
#include "Cleaner.hpp"
#include "Measurement.hpp"
#include "Private.hpp"

// TESTING METHODS

void test_addition()
{
    assert(2 + 5 == 7);
    assert(0 + 0 == 0);
    assert(42 + 666 == 708);
}

void test_sanity_id_user()
{
    User::SetFilename("./ressources/tests/user_profile_sanity/users.csv");
    User_profile::SetFilename("./ressources/tests/user_profile_sanity/user_profiles.csv");
    Sensor::SetFilename("./ressources/tests/user_profile_sanity/sensors.csv");

    User::ReadAll();
    User_profile::ReadAll();
    Sensor::ReadAll();

    User::LinkAll();
    User_profile::LinkAll();
    Sensor::LinkAll();

    for (auto& row: User::users)
    {
        User user = row.second;
        User_profile* profile = user.GetProfile();

        assert(profile == nullptr || user.GetId() == profile->GetId()); 
    }
}

int main()
{
    // running tests
    run(test_addition);
    run(test_sanity_id_user);

    cout << endl << runned << " tests runned successfully" << endl;

    return 0;
}