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
	sprite = new Sprite(0.0f, 0.0f, 100.0f, 100.0f);
	sprite->SetTexture("res/textures/cute doge.jpeg");
	sprite->SetPosition(-400.0f, 300.0f);

	music = new Music("res/audio/breakout.mp3");
	music->SetDefaultVolume(0.8f);
	music->Play(true);

	sf = new SoundEffect("res/audio/high.wav");
	sf->SetDefaultVolume(0.2f);
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

	if (Input::IsKeyPressed(DS_KEY_SPACE))
	{
		music->Stop();
	}
	if (Input::IsKeyPressed(DS_KEY_LEFT_SHIFT))
	{
		sf->Play();
	}

	if (Input::IsMouseButtonPressed(DS_MOUSE_BUTTON_LEFT))
		std::cout << "LEFT" << std::endl;

}

void Application::Run()
{
	Setup();
	Update();
}


