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
    User::ReadAll();
    User_profile::ReadAll();

    Sensor::LinkAll();
    Measurement::LinkAll();
    Attribute::LinkAll();
    User::LinkAll();

    Private::ReadAll();
    Private::LinkAll();

    User_profile::LinkAll();


    /*
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
    */

    /*
    for(auto& row : User::users)
    {
        cout << "id_user : "<< row.first << endl;
        cout << "id_user_sensor : " << row.second.GetIdSensor() << endl;
        cout << endl;
    }
    */

    for(auto& row : Private::privates)
    {
        cout << "id_private : "<< row.first << endl;
        cout << "pass : "<< row.second.GetProfile()->GetPassword() << endl;

        for (Sensor* s: row.second.GetSensors())
        {
            cout << "private_sensor_id : " << s->GetId() << endl;
        }

        cout<< endl;
    }
    
    /*
    for(auto& row : User_profile::user_profiles)
    {
        cout << "id_user : "<< row.first << endl;
        cout << "user_role : " << row.second.GetRole() << endl;
        cout << "id_user_sensor : " << row.second.GetUser()->GetIdSensor() << endl;
        cout << endl;
    }
    */

    return 0;
}