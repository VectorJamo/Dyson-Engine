#include "tilemap.h"

#include <GL/glew.h>
#include <fstream>
#include "util/error_handling.h"

namespace ds {
	namespace graphics {
		Tile::Tile(int x, int y, int width, int height, Texture* texture, int textureUnit)
			:x(x), y(y), width(width), height(height), texture(texture), textureUnit(textureUnit)
		{
			ASSERT(textureUnit >= 1);
			SetTextureClipRect(0, 0, texture->GetWidth(), texture->GetHeight());
		}
		void Tile::SetTextureClipRect(int x, int y, int width, int height)
		{
			float newTextCoords[8] =
			{
						x / (float)(texture->GetWidth())                ,       ((texture->GetHeight()) - y) / (float)(texture->GetHeight()),
						x / (float)(texture->GetWidth())                ,       ((texture->GetHeight()) - (y + height)) / (float)(texture->GetHeight()),
					   (x + width) / (float)(texture->GetWidth())       ,      ((texture->GetHeight()) - (y + height)) / ((float)texture->GetHeight()),
					   (x + width) / (float)(texture->GetWidth())       ,      ((texture->GetHeight() - y) / (float)(texture->GetHeight())),
			};

			memcpy(textCoords, newTextCoords, sizeof(float) * 8);
		}


		void Tilemap::LoadMap()
		{
			std::ifstream stream(pFilePath.c_str());
			std::string line;
			while (std::getline(stream, line))
			{
				for (int i = 0; i < line.size(); i++)
				{
					if(line[i] != ' ')
						tileMap += line[i];
				}
			}
		}
		Tilemap::Tilemap(const char* filePath, int scrWidth, int scrHeight, int maxTilesPerRow, int maxTileRows)
			:pFilePath(filePath), totalTiles(0), scrWidth(scrWidth), scrHeight(scrHeight), maxTilesPerRow(maxTilesPerRow), maxTileRows(maxTileRows), pVAO(nullptr), pVBO(nullptr), pIBO(nullptr)
		{
			tileWidth = scrWidth / maxTilesPerRow;
			tileHeight = scrHeight / maxTileRows;

			LoadMap();

			tileSet.reserve(maxTileRows);
			memset(activeTextures, 0, sizeof(Texture*) * 32);
		}
		void Tilemap::AllocateData()
		{
			// Call this method after all the tiles are set in the tileSet array

			pVAO = new VertexArray();
			// Allocate memory
			pVBO = new VertexBuffer[3];
			pVBO[POS_BUFFER].SendData(sizeof(float) * 8 * totalTiles, 0);
			pVBO[TCOORD_BUFFER].SendData(sizeof(float) * 8 * totalTiles, 0);
			pVBO[TINDEX_BUFFER].SendData(sizeof(float) * 4 * totalTiles, 0);

			pIBO = new IndexBuffer(sizeof(unsigned short) * 6 * totalTiles, 0);

			// Define the buffer layout for the vertex array
			pVAO->Bind();

			pVBO[POS_BUFFER].Bind();
			pVAO->PushLayout(GL_FLOAT, 2, sizeof(float) * 2, 0);

			pVBO[TCOORD_BUFFER].Bind();
			pVAO->PushLayout(GL_FLOAT, 2, sizeof(float) * 2, 0);

			pVBO[TINDEX_BUFFER].Bind();
			pVAO->PushLayout(GL_FLOAT, 1, sizeof(float), 0);

			pIBO->Bind();

			pVAO->Unbind();
		}
		void Tilemap::AddTile(std::vector<Tile*>& tileRow, int i, int j, Texture* texture, int textureUnit)
		{
			Tile* tile = new Tile(j * tileWidth - scrWidth/2, scrHeight/2 - i * tileHeight, tileWidth, tileHeight, texture, textureUnit);
			totalTiles++;
			tileRow.push_back(tile);
		}
		void Tilemap::LoadData()
		{
			// Allocate the required memory to store the data first
			AllocateData();

			int posTextDataOffset = 0;
			int textIndexDataOffset = 0;

			int indexDataOffset = 0;
			int indexOffset = 0;

			for (auto& row : tileSet)
			{
				for (auto& tile : row)
				{
					// Populate the buffers with data from the tileset
					float positions[8] =
					{
						tile->x, tile->y,
						tile->x, tile->y - tile->height,
						tile->x + tile->width, tile->y - tile->height,
						tile->x + tile->width, tile->y
					};

					float textIndex[4] =
					{
						tile->textureUnit,
						tile->textureUnit,
						tile->textureUnit,
						tile->textureUnit,
					};

					// Map the texture units to the tile texture in a pseudo texture* arrays
					activeTextures[tile->textureUnit] = tile->texture;
										
					unsigned short indices[6] = { 0 + indexOffset, 1 + indexOffset, 2 + indexOffset, 2 + indexOffset, 3 + indexOffset, 0 + indexOffset };

					pVBO[POS_BUFFER].Bind();
					pVBO[POS_BUFFER].SendDataIntoRegion(posTextDataOffset, sizeof(float) * 8, positions);

					pVBO[TCOORD_BUFFER].Bind();
					pVBO[TCOORD_BUFFER].SendDataIntoRegion(posTextDataOffset, sizeof(float) * 8, tile->textCoords);

					pVBO[TINDEX_BUFFER].Bind();
					pVBO[TINDEX_BUFFER].SendDataIntoRegion(textIndexDataOffset, sizeof(float) * 4, textIndex);

					pIBO->Bind();
					pIBO->SendDataIntoRegion(indexDataOffset, sizeof(unsigned short) * 6, indices);

					posTextDataOffset += sizeof(float) * 8;
					textIndexDataOffset += sizeof(float) * 4;
					indexOffset += 4;
					indexDataOffset += sizeof(unsigned short) * 6;
				}
			}
		}
		void Tilemap::BindTextures()
		{
			// To be done before each draw call to ensure that correct textures are bound to the texture units in the GPU
			for (int i = 0; i < 32; i++)
			{
				if (activeTextures[i] != 0)
				{
					activeTextures[i]->Bind(i);
				}
			}
		}
		Tilemap::~Tilemap()
		{
			for (auto& tileRow : tileSet)
			{
				for (auto* tile : tileRow)
				{
					delete tile;
				}
			}

			delete pVAO;
			delete[] pVBO;
			delete pIBO;
		}
	}
}
