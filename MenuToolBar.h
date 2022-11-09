#pragma once
#include "AUIScreen.h"

class UISystem;

class MenuToolBar: public AUIScreen
{
public:
	typedef std::string String;
	MenuToolBar();
	~MenuToolBar();


	void drawUI() override;

private:
	friend class UISystem;
};

