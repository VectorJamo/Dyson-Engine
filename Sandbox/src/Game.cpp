#include "Game.h"

#include <entry_point.h>

Game::Game()
{
	blue = nullptr;
	red = nullptr;
	blueAngle = 0.0f, redAngle = 0.0f;
}

Game::~Game()
{
	delete blue;
	delete red;
}

void Game::Setup()
{
	// This runs once in the beginning
	window->SetTitle("Game Window");
	window->SetVSyncEnabled(false);

	blue = new Sprite(-400.0f, 300.0f, 100.0f, 100.0f);
	blue->SetColor(maths::vec4(0.0f, 0.0f, 1.0f, 1.0f));

	red = new Sprite(300.0f, 300.0f, 100.0f, 100.0f);
	red->SetColor(maths::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

void Game::Update()
{
	// This runs every frame
	HandleInput();

	if (blue->CheckCollisisonSAT(red))
		std::cout << "Collided!" << std::endl;

	// Draw
	blue->Draw();
	red->Draw();
	
}

void Game::HandleInput()
{

	// Handle user input
	if (Input::IsKeyPressed(DS_KEY_ESCAPE))
		window->SetShouldClose(true);
	
	// -Sprite Controls
	if (Input::IsKeyHold(DS_KEY_W))
		blue->SetPosition(blue->GetPosition().x, blue->GetPosition().y + 200 * Timer::GetDeltaTime());
	if (Input::IsKeyHold(DS_KEY_S))
		blue->SetPosition(blue->GetPosition().x, blue->GetPosition().y - 200 * Timer::GetDeltaTime());
	if (Input::IsKeyHold(DS_KEY_A))
		blue->SetPosition(blue->GetPosition().x - 200 * Timer::GetDeltaTime(), blue->GetPosition().y);
	if (Input::IsKeyHold(DS_KEY_D))
		blue->SetPosition(blue->GetPosition().x + 200 * Timer::GetDeltaTime(), blue->GetPosition().y);
	if (Input::IsKeyHold(DS_KEY_SPACE))
	{
		blue->SetRotation(blueAngle);
		blueAngle += 200 * Timer::GetDeltaTime();
	}


	if (Input::IsKeyHold(DS_KEY_UP))
		red->SetPosition(red->GetPosition().x, red->GetPosition().y + 200 * Timer::GetDeltaTime());
	if (Input::IsKeyHold(DS_KEY_DOWN))
		red->SetPosition(red->GetPosition().x, red->GetPosition().y - 200 * Timer::GetDeltaTime());
	if (Input::IsKeyHold(DS_KEY_LEFT))
		red->SetPosition(red->GetPosition().x - 200 * Timer::GetDeltaTime(), red->GetPosition().y);
	if (Input::IsKeyHold(DS_KEY_RIGHT))
		red->SetPosition(red->GetPosition().x + 200 * Timer::GetDeltaTime(), red->GetPosition().y);
	if (Input::IsKeyHold(DS_KEY_RIGHT_SHIFT))
	{
		red->SetRotation(redAngle);
		redAngle -= 200 * Timer::GetDeltaTime();
	}

}