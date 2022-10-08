#include "AppWindow.h"
#include "EngineTime.h"

int main()
{
	AppWindow::initialize();
	AppWindow* app = AppWindow::getInstance();
	EngineTime::initialize();

	while (app->isRun())
	{
		app->broadcast();
	}
	

	return 0;
}