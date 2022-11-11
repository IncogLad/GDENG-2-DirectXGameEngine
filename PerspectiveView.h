#pragma once
#include "AUIScreen.h"
class PerspectiveView : public AUIScreen
{
public:
	typedef std::string String;
	PerspectiveView();
	~PerspectiveView() override;


	void drawUI() override;
};

