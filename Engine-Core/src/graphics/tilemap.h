#pragma once
#include "graphics/texture.h"
#include "graphics/data_buffers/vertex_array.h"
#include "graphics/data_buffers/vertex_buffer.h"
#include "graphics/data_buffers/index_buffer.h"

#include "graphics/shader.h"

#include "core.h"

#include <vector>
#include <string>

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
			int tileWidth, tileHeight;
			int maxTilesPerRow, maxTileRows;
			std::vector<std::vector<Tile*>> tileSet;
			int totalTiles;

		private:
			void LoadMap();

		public:
			Tilemap(const char* filePath, int scrWidth, int scrHeight, int maxTilesPerRow, int maxTileRows);
			~Tilemap();

			void AllocateData();
			void LoadData();
			void BindTextures();

			VertexArray* GetVAO() { return pVAO; }
			IndexBuffer* GetIBO() { return pIBO; }
		};
	}
}
