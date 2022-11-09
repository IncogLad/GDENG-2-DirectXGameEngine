#pragma once
#include "AUIScreen.h"


class CreditsScreen : public AUIScreen
{
public:
	typedef std::string String;
	CreditsScreen();
	~CreditsScreen();

	void drawUI() override;
};

