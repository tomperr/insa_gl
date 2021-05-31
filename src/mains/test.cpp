#define run(x) runHelper(#x, x)

#include <iostream>
#include "TestAuthentification.hpp"
#include "TestCleaner.hpp"
#include "TestReadingData.hpp"
#include "TestLinkingData.hpp"
#include "TestFailedSensors.hpp"

using namespace std;

int runned = 0;

void runHelper(const char *f_name, void (*f)(void))
{
    cout << f_name << "... ";
    (*f)();
    cout << "success" << endl;
    runned++;
}

void test_authentification()
{
    run(test_is_auth_ok1);
    run(test_is_auth_ok2);
    run(test_auth_ok1);
    run(test_auth_ok2);
    run(test_auth_ko);
    run(test_deauth_ok);
    run(test_deauth_ko1);
    run(test_getuser_ok1);
    run(test_getuser_ok2);
    run(test_getuser_limit);
    run(test_integration_ok);
}

void test_reading_data()
{
    run(test_reading_users);
    run(test_reading_user_profiles);
    run(test_reading_sensors);
    run(test_reading_measurements);
    run(test_reading_cleaners);
    run(test_reading_attributes);
}

void test_linking_data()
{
    run(test_linking_users);
    run(test_linking_user_profiles);
    run(test_linking_sensors);
    run(test_linking_measurements);
    run(test_linking_attributes);
}

void test_cleaner()
{
    run(test_compute_cleaner_effect_test);
}


void test_failed_sensors()
{
    run(test_detect_failed_sensors);
}

int main()
{
    // running tests
    test_cleaner();
    test_authentification();
    test_reading_data();
    test_linking_data();
    test_failed_sensors();

    cout << endl << runned << " tests runned successfully" << endl;

    return 0;
}