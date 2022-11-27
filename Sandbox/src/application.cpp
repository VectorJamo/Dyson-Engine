#include "Application.h"

#include <entry_point.h>

Application::Application()
	:window(nullptr), camera(nullptr), block(nullptr), wall(nullptr), entryDoor(nullptr), exitDoor(nullptr), tilemap(nullptr)
{
}

void Application::Setup()
{
	window = new graphics::Window(600, 600, "Dyson Engine");
	window->Init();
	window->SetVSyncEnabled(false);

	// Initialize	
	block = new Texture("res/tilemap/tiles/block.png");
	wall = new Texture("res/tilemap/tiles/wall.jfif");
	entryDoor = new Texture("res/tilemap/tiles/entry door.jfif");
	exitDoor = new Texture("res/tilemap/tiles/exit door.jpg");

	tilemap = new Tilemap("res/tilemap/map.txt", 600, 600, 10, 10);
	
	std::vector<Tile*> tileRow;
	for (int i = 0; i < tilemap->maxTileRows; i++)
	{
		for (int j = 0; j < tilemap->maxTilesPerRow; j++)
		{
			if (tilemap->tileMap[i * tilemap->maxTilesPerRow + j] == '1')
			{
				tilemap->AddTile(tileRow, i, j, wall, 1);
			}
			else if (tilemap->tileMap[i * tilemap->maxTilesPerRow + j] == '-')
			{
				tilemap->AddTile(tileRow, i, j, block, 2);
			}
			else if (tilemap->tileMap[i * tilemap->maxTilesPerRow + j] == 'E')
			{
				tilemap->AddTile(tileRow, i, j, entryDoor, 3);
			}
			else if (tilemap->tileMap[i * tilemap->maxTilesPerRow + j] == 'D')
			{
				tilemap->AddTile(tileRow, i, j, exitDoor, 4);
			}
		}
		tilemap->tileSet.push_back(tileRow);
		tileRow.clear();
	}
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


