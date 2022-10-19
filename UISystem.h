#pragma once
#include <d3d11.h>

class UISystem
{
public:
	UISystem();
	~UISystem();

	static void initialize();
	static UISystem* getInstance();
	static void destroy();

	void update();
	void initImGUI(HWND hwnd);

private:
	static UISystem* sharedInstance;
	bool show_demo_window = true;
};

