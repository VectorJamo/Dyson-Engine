#pragma once
#include "core.h"

namespace ds {
	namespace graphics {
		class DS IndexBuffer
		{
		private:
			unsigned int pIBO;
			unsigned int pDataSize;

		public:
			IndexBuffer(unsigned int dataSize, const void* data);
			~IndexBuffer();

			void Bind();
			void Unbind();

			void SendDataIntoRegion(unsigned int dataOffset, unsigned int dataSize, const void* data);
		};
	}
}