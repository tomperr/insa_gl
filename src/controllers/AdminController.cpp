#include "AdminController.hpp"

using namespace std;

AdminController::AdminController() {
	// silence is golden
}

void AdminController::ShowControlPanel() {
	int choice = AdminViews::ControlPanel();

	switch(choice)
	{
		case 0:
		{
			break;
		}

		case 1:
		{
			AdminViews::ResultFailedSensors(Sensor::DetectFailedSensors(Sensor::sensors, 25));
			//cout << "ResultFailedSensors" << endl;
			break;
		}

		case 2:
		{
			AdminViews::ResultFakeMeasurement(Measurement::DetectFakeMeasurement());
			break;
		}
	}
}