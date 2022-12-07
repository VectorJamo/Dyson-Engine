#pragma once
#include "../../core.h"

namespace ds {
	namespace graphics {
		class DS VertexBuffer
		{
		private:
			unsigned int pVBO;
			unsigned int pDataSize;

		public:
			VertexBuffer();
			VertexBuffer(unsigned int dataSize, const void* data);
			~VertexBuffer();

			void Bind();
			void Unbind();

			void SendData(unsigned int dataSize, const void* data);
			void SendDataIntoRegion(unsigned int dataOffset, unsigned int dataSize, const void* data);
		};
	}
}
