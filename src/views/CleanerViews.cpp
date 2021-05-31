#include "CleanerViews.hpp"

void CleanerViews::ListedData(vector<Cleaner> cleaners)
{
    cout << "Liste détaillé des cleaners" << endl;
    for(Cleaner cleaner : cleaners)
    {
        struct tm acstart = cleaner.GetActivityStart();
        struct tm acend = cleaner.GetActivityEnd();
        cout << setfill('0') << "CleanerID: " << cleaner.GetId();
        cout << " debut: " << std::setw(2) << acstart.tm_mday << "/" << std::setw(2) << acstart.tm_mon+1 << "/" << acstart.tm_year+1900;
        cout << " fin: " << std::setw(2) << acend.tm_mday << "/" << std::setw(2) << acend.tm_mon+1 << "/" << acend.tm_year+1900;
        cout << " latitude: " << cleaner.GetLatitude() << " longitude: " << cleaner.GetLongitude();
        cout << endl;
    }
}

Cleaner CleanerViews::getCleaner(vector<Cleaner> cleaners)
{
    int index = 0;
    bool firstiteration = true;
    bool choiceCorrect = false;
    int choice = -1;

    while(!choiceCorrect)
    {
        if(firstiteration)
        {
            firstiteration = false;
        }
        else
        {
            cout << "Choix erroné !" << endl;
        }

        cout << "0 - Revenir en arrière" << endl;

        index = 1;
        for(Cleaner cleaner : cleaners)
        {
            cout << index++ << " - CleanerID: " << cleaner.GetId() << endl;
        }

        cout << "> ";
        cin >> choice;
        if(choice >= 0 && choice <= index - 1)
        {
            choiceCorrect = true;
        }
    }

    return cleaners[choice - 1];
}

void CleanerViews::ResultComputeCleanerEffectOnArea(vector<double> data)
{
    // TODO: mettre une unité
    if(data.size() < 4)
    {
        cout << "Erreur avec les données !" << endl;
    }
    else
    {
        cout << "Effet sur la zone (en pourcentage) :" << endl;
        cout << "O3: " << data[0] << endl;
        cout << "SO2: " << data[1] << endl;
        cout << "NO2: " << data[2] << endl;
        cout << "PM10: " << data[3] << endl;
    }
}

int CleanerViews::GetRadius()
{
    int radius = -1;

    while(radius <= 0)
    {
        cout << "Rayon de la zone : ";
        cin >> radius;

        if(radius <= 0)
            cout << "Erreur de saisie." << endl << endl;
    }

    return radius;
}