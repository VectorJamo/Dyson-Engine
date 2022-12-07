#pragma once
#include "engine.h"

class DS Application
{
protected:
	ds::graphics::Window* window;

public:
	Application();
	virtual ~Application();

	void MainLoop();
	
	virtual void Setup() = 0;
	virtual void Update() = 0;
};

