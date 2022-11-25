#include "Application.h"

#include <entry_point.h>

Application::Application()
	:window(nullptr), camera(nullptr), sprite(nullptr)
{
}

void Application::Setup()
{
	window = new graphics::Window(800, 600, "Dyson Engine");
	if (!window->Init())
		THROW_ERROR("Window initialization failed!");
	window->SetVSyncEnabled(false);

	// Initialize	
	Input::Init(window);
	Sprite::Init();
	
	camera = new OrthographicCamera(-400.0f, 400.0f, 300.0f, -300.0f, 1.0f, -1.0f);
	
	sprite = new Sprite(-100.0f, 100.0f, 200.0f, 200.0f);
	sprite->SetColor(maths::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	sprite->SetTexture("res/textures/cute doge.jpeg");
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


