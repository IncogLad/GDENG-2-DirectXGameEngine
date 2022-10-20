#pragma once
#include "SwapChain.h"

class Viewport {

public:

	Viewport();
	~Viewport();

	void initialize(SwapChain* swap_chain);
	void destroy();
	void update(const char* name);


private:
	SwapChain* swapChain;
};