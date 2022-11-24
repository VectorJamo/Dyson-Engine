#include "Application.h"

#include <entry_point.h>

Application::Application()
	:window(nullptr)
{
}

void Application::Setup()
{
	window = new graphics::Window(800, 600, "Dyson Engine");
	if (!window->Init())
		THROW_ERROR("Window initialization failed!");
	window->SetVSyncEnabled(true);

	// Initialize 
	Input::Init(window);

}

void Application::Update()
{
	while (!window->IsClosed())
	{
		window->Clear(0.0f, 0.0f, 0.0f, 1.0f);
		window->PollEvents();

		// Draw
		

		window->Display();
	}
}

void Application::Run()
{
	Setup();
	Update();
}


