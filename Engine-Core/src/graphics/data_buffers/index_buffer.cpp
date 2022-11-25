#include "index_buffer.h"

#include <GL/glew.h>

namespace ds {
	namespace graphics {
		IndexBuffer::IndexBuffer(unsigned int dataSize, const void* data)
			:pIBO(0), pDataSize(dataSize)
		{
			glGenBuffers(1, &pIBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		IndexBuffer::~IndexBuffer()
		{
			glDeleteBuffers(1, &pIBO);
		}
		void IndexBuffer::Bind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIBO);
		}

		void IndexBuffer::Unbind()
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		void IndexBuffer::SendDataIntoRegion(unsigned int dataOffset, unsigned int dataSize, const void* data)
		{
			pDataSize += dataSize;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIBO);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, dataOffset, dataSize, data);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	}
}