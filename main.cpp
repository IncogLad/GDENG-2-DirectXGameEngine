#include "AppWindow.h"

int main()
{
	AppWindow::initialize();
	AppWindow* app = AppWindow::getInstance();
	

	while (app->isRun())
	{
		app->broadcast();
	}
	

	return 0;
}