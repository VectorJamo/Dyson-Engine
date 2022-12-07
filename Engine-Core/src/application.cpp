#include "application.h"

Application::Application()
{
	// Make the window
	window = new ds::graphics::Window(800, 600, "Dyson Engine");
	window->Init();
	window->SetVSyncEnabled(false);

}

Application::~Application()
{
	delete window;
}

void Application::MainLoop()
{
	Setup();
	while (!window->IsClosed())
	{
		window->Clear();
		window->PollEvents();


		Update();


		window->Display();
	}
}