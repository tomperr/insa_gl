#ifndef ADMINVIEWS_HPP
#define ADMINVIEWS_HPP

#include <iostream>
#include <vector>
#include "Sensor.hpp"
#include "Measurement.hpp"

using namespace std;

class AdminViews
{
    public:
    static int ControlPanel();
    static void ResultFailedSensors(vector<Sensor> sensors);
    static void ResultFakeMeasurement(vector<pair<Sensor, Measurement>> data);
};

#endif