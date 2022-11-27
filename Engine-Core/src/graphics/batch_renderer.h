#pragma once

#include "graphics/shader.h"
#include "graphics/tilemap.h"

#include <memory>

namespace ds {
	namespace graphics {
		class DS BatchRenderer
		{
		private:
			static std::unique_ptr<Shader> pShader;
	
		public:
			static void Init();
			static void Draw(Tilemap* map);
		}; 
	}
}

