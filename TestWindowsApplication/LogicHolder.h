#pragma once
#include "Window.h"
#include "ConfuxTimer.h"

class LogicHolder
{
public:
	LogicHolder();
	
	int go();
private: 
	void doFrame();
private:
	Window window;
	ConfuxTimer timer;
};

