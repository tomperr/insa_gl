#include "Attribute.hpp"
#include "Sensor.hpp"
#include "Cleaner.hpp"
#include "Measurement.hpp"
#include "Private.hpp"

#include <map>
#include <ctime>

using namespace std;

int main(void)
{
    Attribute::ReadAll();

    for(auto& row : Attribute::attributes)
    {
        cout << "id:" << row.second.GetId();
        cout << " unit:" << row.second.GetUnit();
        cout << " description:" << row.second.GetDescription();
        cout << endl; 
    }

    Sensor::ReadAll();

    for(auto& row : Sensor::sensors)
    {
        cout << "id:" << row.second.GetId();
        cout << " longitude:" << row.second.GetLongitude();
        cout << " latitude:" << row.second.GetLatitude();
        cout << endl; 
    }

    

    Measurement::ReadAll();
    tm buff_date;

    for(auto& row : Measurement::measurements)
    {
        cout << "id_sensor:" << row.second.GetIdSensor();
        cout << " id_attribute:" << row.second.GetIdAttribute();
        cout << " value:" << row.second.GetValue();

		buff_date = row.second.GetDate();

        cout << " time:" << buff_date.tm_mday << "/" <<
        	buff_date.tm_mon << "/" << buff_date.tm_year;
        cout << endl; 
    }

    Cleaner::ReadAll();

    for(auto& row : Cleaner::cleaners)
    {
        cout << "id:" << row.second.GetId();
        cout << " longitude:" << row.second.GetLongitude();
        cout << " latitude:" << row.second.GetLatitude();
        cout << " activity_start:" << row.second.GetActivityStart().tm_mday << "/" << row.second.GetActivityStart().tm_mon << "/" << row.second.GetActivityStart().tm_year << " " << row.second.GetActivityStart().tm_hour << ":" << row.second.GetActivityStart().tm_min;
        cout << " activity_end:" << row.second.GetActivityEnd().tm_mday << "/" << row.second.GetActivityEnd().tm_mon << "/" << row.second.GetActivityEnd().tm_year << " " << row.second.GetActivityEnd().tm_hour << ":" << row.second.GetActivityEnd().tm_min;
        cout << endl; 
    }

    Private::ReadAll();
    for(auto& row : Private::privates)
    {
         cout << "id : "<<row.first<<endl;
         vector <Sensor> sensors = row.second.GetSensors();
         for(int i=0; i<sensors.size();++i){
             cout << "\t sensor id : "<<sensors[i].GetId()<<endl;
         }
         cout<< endl;
    }


    return 0;
}