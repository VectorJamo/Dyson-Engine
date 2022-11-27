#include "Application.h"

#include <entry_point.h>

Application::Application()
	:window(nullptr), camera(nullptr), block(nullptr), wall(nullptr), tilemap(nullptr)
{
}

void Application::Setup()
{
	window = new graphics::Window(600, 600, "Dyson Engine");
	if (!window->Init())
		THROW_ERROR("Window initialization failed!");
	window->SetVSyncEnabled(false);

	// Initialize	
	block = new Texture("res/tilemap/tiles/block.png");
	wall = new Texture("res/tilemap/tiles/wall.jfif");

	tilemap = new Tilemap("res/tilemap/map.txt", 600, 600, 10, 10);
	
	std::vector<Tile*> tileRow;
	for (int i = 0; i < tilemap->maxTileRows; i++)
	{
		for (int j = 0; j < tilemap->maxTilesPerRow; j++)
		{
			if (tilemap->tileMap[i * tilemap->maxTilesPerRow + j] == '1')
			{
				Tile* tile = new Tile(j * tilemap->tileWidth - 300.0f, 300.0f - i * tilemap->tileHeight, tilemap->tileWidth, tilemap->tileHeight, wall, 1);
				tilemap->totalTiles++;
				tileRow.push_back(tile);
			}
			else if (tilemap->tileMap[i * tilemap->maxTilesPerRow + j] == '-')
			{
				Tile* tile = new Tile(j * tilemap->tileWidth - 300.0f, 300.0f - i * tilemap->tileHeight, tilemap->tileWidth, tilemap->tileHeight, block, 2);
				tilemap->totalTiles++;
				tileRow.push_back(tile);
			}
		}
		tilemap->tileSet.push_back(tileRow);
		tileRow.clear();
	}
	std::cout << "total tiles:" << tilemap->totalTiles << std::endl;

	tilemap->AllocateData();
	tilemap->LoadData();
}

void Application::Update()
{
	while (!window->IsClosed())
	{
		window->Clear(0.0f, 0.0f, 0.0f, 1.0f);
		HandleInput();

		// Draw
		BatchRenderer::Draw(tilemap);
		
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


