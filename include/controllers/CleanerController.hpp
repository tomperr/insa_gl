#ifndef CLEANERCONTROLLER_HPP
#define CLEANERCONTROLLER_HPP

#include <iostream>
#include <vector>
#include "Cleaner.hpp"
#include "CleanerViews.hpp"

class CleanerController
{
    public:
        CleanerController();
        
        void ShowData() ;

        void ShowCleanerEffect() ; // function to show the effect of a cleaner
	
};

#endif