#include "TestFailedSensors.hpp"

void test_detect_failed_sensors()
{
    Sensor::SetFilename("./ressources/tests/detect_failed_sensors/sensors.csv");
    Measurement::SetFilename("./ressources/tests/detect_failed_sensors/measurements.csv");

    Sensor::ReadAll();
    Measurement::ReadAll();

    Sensor::LinkAll();
    Measurement::LinkAll();

    vector<Sensor> failedSensors = Sensor::DetectFailedSensors(Sensor::sensors,15.0);

    assert(failedSensors.size() == 2);
    
}