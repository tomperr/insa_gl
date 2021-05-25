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
    Sensor::ReadAll();
    Measurement::ReadAll();
    Cleaner::ReadAll();
    Private::ReadAll();

    Sensor::LinkAll();
    Measurement::LinkAll();
    Attribute::LinkAll();

    for(auto& row : Attribute::attributes)
    {
        cout << "id:" << row.second.GetId();
        cout << " unit:" << row.second.GetUnit();
        cout << " description:" << row.second.GetDescription();
        cout << endl; 
    }

    

    for(auto& row : Sensor::sensors)
    {
        cout << "id:" << row.second.GetId();
        cout << " longitude:" << row.second.GetLongitude();
        cout << " latitude:" << row.second.GetLatitude();
        cout << endl; 
    }

    

    tm buff_date;

    for(auto& row : Measurement::measurements)
    {
        cout << "id_sensor:" << row.second.GetIdSensor();
        cout << " id_attribute:" << row.second.GetIdAttribute();
        cout << " value:" << row.second.GetValue();

		buff_date = row.second.GetDate();

        cout << " time:" << buff_date.tm_mday << "/" <<
        	buff_date.tm_mon+1 << "/" << buff_date.tm_year+1900;
        cout << endl; 
    }


    for(auto& row : Cleaner::cleaners)
    {
        cout << "id:" << row.second.GetId();
        cout << " longitude:" << row.second.GetLongitude();
        cout << " latitude:" << row.second.GetLatitude();

        struct tm activityStart = row.second.GetActivityStart();
        struct tm activityEnd = row.second.GetActivityEnd();

        cout << " activity_start:" << std::setfill ('0') << std::setw(2) << activityStart.tm_mday << "/" << std::setw(2) << activityStart.tm_mon+1 << "/" << activityStart.tm_year+1900 << " " << std::setw(2) << activityStart.tm_hour << ":" << std::setw(2) << activityStart.tm_min;
        cout << " activity_end:" << std::setw(2) << activityEnd.tm_mday << "/" << std::setw(2) << activityEnd.tm_mon+1 << "/" << activityEnd.tm_year+1900 << " " << std::setw(2) << activityEnd.tm_hour << ":" << std::setw(2) << activityEnd.tm_min;
        cout << endl; 
    }

    for(auto& row : Private::privates)
    {
        cout << "id : "<<row.first<<endl;
        vector <Sensor*> sensors = row.second.GetSensors();
        for(long unsigned int i=0; i<sensors.size();++i){
            cout << "\t sensor id : "<<sensors[i]->GetId()<<endl;
        }
        cout<< endl;
    }


    return 0;
}