#pragma once
#include "AUIScreen.h"
class TopdownView : public AUIScreen
{
public:
	typedef std::string String;
	TopdownView();
	~TopdownView();


	void drawUI() override;
};

