#ifndef CLEANERVIEWS_HPP
#define CLEANERVIEWS_HPP

#include <iostream>
#include <vector>
#include <iomanip>
#include "Cleaner.hpp"

using namespace std;

class CleanerViews
{
    public:
    static void ListedData(vector<Cleaner> cleaners);
    static Cleaner getCleaner(vector<Cleaner> cleaners);
    static void ResultComputeCleanerEffectOnArea(vector<double> data);
    static int GetRadius();
};

#endif