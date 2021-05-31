#include "TestCleaner.hpp"

void test_compute_cleaner_effect_test()
{
    Sensor::SetFilename("./ressources/tests/compute_cleaner_effect_test/sensors.csv");
    Measurement::SetFilename("./ressources/tests/compute_cleaner_effect_test/measurements.csv");
    Cleaner::SetFilename("./ressources/tests/compute_cleaner_effect_test/cleaners.csv");

    Sensor::ReadAll();
    Measurement::ReadAll();
    Cleaner::ReadAll();

    Sensor::LinkAll();
    Measurement::LinkAll();

    //computing the value of the effect of that cleaner manually
    //the only sensors (among the sensors we put in the test csv file) in the circular area of 50km radius 
    //are sensor33, sensor43 and sensor44  so we only take into account their measurements

    double pourcentageDeProgressionOzone = 100*((1-48.23/49.77)+(1-46.3/46.52)+(1-38.44/38.53))/3;
    double pourcentageDeProgressionSoufre = 100*((1-44.47/42.33)+(1-35.54/33.12)+(1-41.64/40.0))/3; 
    double pourcentageDeProgressionAzote = 100*((1-51.37/51.36)+(1-39.84/38.65)+(1-39.72/38.26))/3;
    double pourcentageDeProgressionFines = 100*((1-55.56/57.43)+(1-73.16/73.17)+(1-57.5/58.59))/3;

    //we call the static function ComputeCleanerEffectOnArea and compare results
    map<string, Cleaner>::iterator cleanerIt=Cleaner::cleaners.begin();
    vector<double> pourcentageDeProgression = Cleaner::ComputeCleanerEffectOnArea((cleanerIt)->second);

    assert(pourcentageDeProgressionOzone - pourcentageDeProgression.back() <0.0001);       pourcentageDeProgression.pop_back();
    assert(pourcentageDeProgressionSoufre - pourcentageDeProgression.back() <0.0001);      pourcentageDeProgression.pop_back();
    assert(pourcentageDeProgressionAzote - pourcentageDeProgression.back() <0.0001);       pourcentageDeProgression.pop_back();
    assert(pourcentageDeProgressionFines - pourcentageDeProgression.back() <0.0001);       pourcentageDeProgression.pop_back();

    
    Sensor::EmptyData();
    Measurement::EmptyData();
    Cleaner::EmptyData();

}