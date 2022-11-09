#pragma once
#include "AUIScreen.h"


class GameView : public AUIScreen
{
public:
	typedef std::string String;
	GameView();
	~GameView();

	
	void drawUI() override;

};
