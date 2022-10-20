#pragma once
#include <d3d11.h>
#include <list>
#include "Viewport.h"

class UISystem
{
public:
	UISystem();
	~UISystem();

	static void initialize();
	static UISystem* getInstance();
	static void destroy();

	void updateNewFrame();
	void update(SwapChain* swapChain);
	void initImGUI(HWND hwnd);

private:
	static UISystem* sharedInstance;
	std::list<Viewport*> viewportList;
	bool show_demo_window = true;
};

