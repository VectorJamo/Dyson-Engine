#pragma once
#include <core.h>
#include <vector>
#include <string>

#include "graphics/shader.h"
#include "graphics/texture.h"
#include "graphics/data_buffers/vertex_array.h"
#include "graphics/data_buffers/vertex_buffer.h"
#include "graphics/data_buffers/index_buffer.h"

namespace ds {
	namespace graphics {
		#define POS_BUFFER 0
		#define TCOORD_BUFFER 1
		#define TINDEX_BUFFER 2

		struct DS Tile
		{
			int x, y, width, height;
			Texture* texture;
			
			int textureUnit;
			float textCoords[8];

			Tile(int x, int y, int width, int height, Texture* texture, int textureUnit);

			void SetTextureClipRect(int x, int y, int width, int height);
		};

		class DS Tilemap
		{
		private:
			std::string pFilePath;

			Texture* activeTextures[32];

			VertexArray* pVAO;
			VertexBuffer* pVBO;
			IndexBuffer* pIBO;
		
		public:
			std::string tileMap;
			int scrWidth, scrHeight, tileWidth, tileHeight;
			int maxTilesPerRow, maxTileRows;
			std::vector<std::vector<Tile*>> tileSet;
			int totalTiles;

		private:
			void LoadMap();
			void AllocateData();

		public:
			Tilemap(const char* filePath, int scrWidth, int scrHeight, int maxTilesPerRow, int maxTileRows);
			~Tilemap();

			void AddTile(std::vector<Tile*>& tileRow, int i, int j, Texture* texture, int textureUnit);
			void LoadData();
			void BindTextures();

			VertexArray* GetVAO() { return pVAO; }
			IndexBuffer* GetIBO() { return pIBO; }
		};
	}
}
