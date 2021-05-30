#include "AdminViews.hpp"

int AdminViews::ControlPanel()
{
    int choice = -1;
    bool firstTime = true;
    bool choiceCorrect = false;

    cout << "Panneau de contrôles Administrateur" << endl;

    while(!choiceCorrect)
    {
        if(firstTime)
        {
            firstTime = false;
        }
        else
        {
            cout << "Choix erroné !" << endl;
        }

        cout << "0 - Revenir en arrière" << endl;
        cout << "1 - Rechercher les capteurs défectueux" << endl;
        cout << "2 - Rechercher les mesures fausses" << endl;

        cout << "> ";
        cin >> choice;

        if(choice >= 0 && choice <= 2)
        {
            choiceCorrect = true;
        }
    }

    return choice;
}

void AdminViews::ResultFailedSensors(vector<Sensor> sensors)
{
    //TODO: mettre des vraies infos
    for(Sensor sensor : sensors)
    {
        cout << "SensorID: " << sensor.GetId() << endl;
    }
}

void AdminViews::ResultFakeMeasurement(vector<pair<Sensor, Measurement>> data)
{
    //TODO: mettre des vraies infos
    for(pair<Sensor,Measurement> apair : data)
    {
        cout << "SensorID: " << apair.first.GetId() << " " << apair.second.GetValue() << endl;
    }
}