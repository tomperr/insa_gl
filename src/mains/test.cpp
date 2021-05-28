#define run(x) runHelper(#x, x)

#include <iostream>
#include <assert.h>

using namespace std;

void runHelper(const char *f_name, void (*f)(void))
{
    cout << f_name << "... ";
    (*f)();
    cout << "success" << endl;
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
    for (auto& row: User::users)
    {
        User user = row.second;
        User_profile* profile = user.GetProfile();

        assert(user.GetId() == profile->GetId()); 
    }
}

int main()
{
    // reading and linking data
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

    // running tests
    run(test_addition);
    run(test_sanity_id_user);

    return 0;
}