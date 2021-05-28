#include <map>
#include <ctime>

#include "Attribute.hpp"
#include "Sensor.hpp"
#include "Cleaner.hpp"
#include "Measurement.hpp"
#include "Private.hpp"

#include "HomeController.hpp"

using namespace std;

int main(void)
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

    // MAIN LOOP

    HomeController homecontroller;
    int choice = 1;
    while (choice != 0)
    {
        choice = homecontroller.ShowHome();
        if (choice == 0) break; // quitting option

        cout << endl; // spacing
        homecontroller.NavigateTo(choice);
        cout << endl; // spacing
    }

    return 0;
}