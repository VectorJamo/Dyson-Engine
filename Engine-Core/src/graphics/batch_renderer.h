#pragma once

#include "shader.h"
#include "tilemap.h"

#include <memory>

namespace ds {
	namespace graphics {
		class DS BatchRenderer
		{
		private:
			static Shader* pShader;
	
		public:
			static void Init();
			static void Free();

			static void Draw(Tilemap* map);
			static void Draw(Tilemap* map, Shader* shader);
		};
	}
}

