#include "CleanerController.hpp"
#include <iostream>

using namespace std;

CleanerController :: CleanerController(){
    //bloc vide
}

void CleanerController::ShowData(){
    vector<Cleaner> cleaners;

    for(auto it = Cleaner::cleaners.begin(); it != Cleaner::cleaners.end(); ++it)
    {
        Cleaner cleaner = (*it).second;
        cleaners.push_back(cleaner);
    }

    CleanerViews::ListedData(cleaners);
}

void CleanerController::ShowCleanerEffect(){
    vector<Cleaner> cleaners;

    for(auto it = Cleaner::cleaners.begin(); it != Cleaner::cleaners.end(); ++it)
    {
        Cleaner cleaner = (*it).second;
        cleaners.push_back(cleaner);
    }
    
    CleanerViews::ListedData(cleaners);
    Cleaner cleaner = CleanerViews::getCleaner(cleaners);
    int radius = CleanerViews::GetRadius();
    CleanerViews::ResultComputeCleanerEffectOnArea(Cleaner::ComputeCleanerEffectOnArea(cleaner, radius));
}



