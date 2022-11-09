#pragma once
#include <string>

class UISystem;

class AUIScreen
{
public:
	typedef std::string String;
	AUIScreen(String name);
	virtual ~AUIScreen();

	String getName();
	virtual void drawUI() = 0;

	bool open = true;

private:
	String name;
	friend class UISystem;
};

