#pragma once
#include "AUIScreen.h"

class ColorPicker : public AUIScreen
{
public:
	typedef std::string String;
	ColorPicker();
	~ColorPicker();

	void drawUI() override;
};

