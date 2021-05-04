#include "HomeController.hpp"
#include <iostream>

using namespace std;

HomeController::HomeController() {
	// silence is golden
}

void HomeController::ShowHome() {
	cout << "Show Home View" << endl;
}

void HomeController::NavigateTo(int choice) {
	cout << "NavigateTo : " << choice << endl;
}