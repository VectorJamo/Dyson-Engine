#pragma once
#include "core.h"

namespace ds {
	namespace graphics {
		class DS VertexBuffer
		{
		private:
			unsigned int pVBO;
			unsigned int pDataSize;

		public:
			VertexBuffer(unsigned int dataSize, const void* data);
			~VertexBuffer();

			void Bind();
			void Unbind();

			void SendDataIntoRegion(unsigned int dataOffset, unsigned int dataSize, const void* data);
		};
	}
}
