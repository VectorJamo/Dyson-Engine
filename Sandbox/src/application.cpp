#include "Application.h"

#include <entry_point.h>

Application::Application()
{
	window = nullptr;
	text = nullptr;
}

Application::~Application()
{
	delete text;
	delete window;
}

void Application::Setup()
{
	window = new graphics::Window(800, 600, "Dyson Engine");
	window->Init();
	window->SetVSyncEnabled(false);

	// Initialize
	text = new Text("res/fonts/Roboto/Roboto-Regular.ttf", 48);
	text->SetPosition(0.0f, 0.0f);
	text->SetText("Hello World!");
	text->SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	text->SetScale(0.5f);
	text->SetRotation(60.0f);
}

void Application::Update()
{
	while (!window->IsClosed())
	{
		window->Clear(0.0f, 0.0f, 0.0f, 1.0f);
		HandleInput();
		
		// Draw
		text->Render();


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


