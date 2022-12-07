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

	sprite = new graphics::Sprite(0.0f, 0.0f, 100.0f, 100.0f);
	sprite->SetColor(maths::vec4(1.0f, 0.0f, 1.0f, 1.0f));

}

void Game::Update()
{
	// This runs every frame
	sprite->Draw();

	HandleInput();
}

void Game::HandleInput()
{
	util::OrthographicCamera::UpdateControls();
}
