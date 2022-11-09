#pragma once
#include <d3d11.h>
#include <list>
#include <unordered_map>

#include "AUIScreen.h"


typedef std::string String;
typedef std::list<AUIScreen*> UIList;
typedef std::unordered_map<String, AUIScreen*> UITable;

class CreditsScreen;
class MenuToolBar;
class GameView;
class PerspectiveView;
class TopDownView;
class ColorPicker;

class UINames
{
public:
	const String MENU_TOOL_BAR = "MENU_TOOL_BAR";
	const String CREDITS_SCREEN = "CREDITS_SCREEN";
	const String COLOR_PICKER = "COLOR_PICKER";

	const String GAME_VIEW = "GAME_VIEW";
	const String PERSPECTIVE_VIEW = "PERSPECTIVE_VIEW";
	const String TOPDOWN_VIEW = "TOPDOWN_VIEW";
};


class UISystem
{
public:
	UISystem();
	~UISystem();

	static void initialize();
	static UISystem* getInstance();
	static void destroy();

	void updateNewFrame();
	void update();
	void initImGUI(HWND hwnd);

	static const int WINDOW_HEIGHT = 1440;
	static const int WINDOW_WIDTH = 900;

private:
	static UISystem* sharedInstance;

	UINames uiNames;
	UIList uiList;
	UITable uiTable;

	bool show_demo_window = true;

private:
	friend class CreditsScreen;
	friend class MenuToolBar;
	friend class ColorPicker;
	friend class GameView;
	friend class PerspectiveView;
	friend class TopDownView;
};

