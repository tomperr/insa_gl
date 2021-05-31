#define run(x) runHelper(#x, x)

#include <iostream>
#include "TestAuthentification.hpp"
#include "TestCleaner.hpp"

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

void test_cleaner()
{
    run(test_compute_cleaner_effect_test);
}

int main()
{
    // running tests
    test_cleaner();
    test_authentification();

    cout << endl << runned << " tests runned successfully" << endl;

    return 0;
}