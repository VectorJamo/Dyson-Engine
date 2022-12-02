#include "Application.h"

#include <entry_point.h>

Application::Application()
{
	window = nullptr;
}

Application::~Application()
{
	delete window;
}

void Application::Setup()
{
	window = new graphics::Window(800, 600, "Dyson Engine");
	window->Init();
	window->SetVSyncEnabled(false);

	// Initialize
}

void Application::Update()
{
	while (!window->IsClosed())
	{
		window->Clear(0.0f, 0.0f, 0.0f, 1.0f);
		HandleInput();
		
		// Draw
		window->DrawDot(maths::vec2(0.0f, 0.0f), maths::vec4(1.0f, 0.0f, 1.0f, 1.0f));

		window->Display();
	}
}

void Application::HandleInput()
{
	window->PollEvents();

	OrthographicCamera::UpdateControls();
}

void Application::Run()
{
	Setup();
	Update();
}


