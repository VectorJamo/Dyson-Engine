#include "Game.h"

#include <entry_point.h>

Game::Game()
{
	sprite = nullptr;
}

Game::~Game()
{
	delete sprite;
}

void Game::Setup()
{
	// This runs once in the beginning
	window->SetTitle("Game Window");

	block = new Texture("res/tilemap/tiles/block.png");
	wall = new Texture("res/tilemap/tiles/wall.jfif");

	sprite = new graphics::Sprite(0.0f, 0.0f, 100.0f, 100.0f);
	sprite->SetTexture(block);
}

void Game::Update()
{
	// This runs every frame
	HandleInput();

	sprite->Draw();
}

void Game::HandleInput()
{
	//util::OrthographicCamera::UpdateControls();

	// Handle user input
	if (Input::IsKeyPressed(DS_KEY_LEFT))
		sprite->SetTexture(wall);
	if (Input::IsKeyPressed(DS_KEY_RIGHT))
		sprite->SetTexture(block);

	if (Input::IsKeyPressed(DS_KEY_ESCAPE))
		window->SetShouldClose(true);

}
