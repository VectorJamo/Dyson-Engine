#include "Application.h"

#include <entry_point.h>

Application::Application()
{
	window = nullptr;
	sprite = nullptr;
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
	sprite = new Sprite(0, 0, 100, 100);
	sprite->SetColor(vec4(1.0f, 0.0f, 1.0f, 1.0f));
	sprite->SetTexture("res/textures/cute doge.jpeg");
	sprite->SetColor(vec4(1.0f, 0.0f, 1.0f, 1.0f));
}

void Application::Update()
{
	while (!window->IsClosed())
	{
		window->Clear(0.0f, 0.0f, 0.0f, 1.0f);
		HandleInput();
		
		// Draw
		sprite->Draw();


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


