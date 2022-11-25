#include "vertex_buffer.h"

#include <GL/glew.h>

namespace ds {
	namespace graphics {
		VertexBuffer::VertexBuffer(unsigned int dataSize, const void* data)
			:pVBO(0), pDataSize(dataSize)
		{
			glGenBuffers(1, &pVBO);
			glBindBuffer(GL_ARRAY_BUFFER, pVBO);
			glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_DYNAMIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
		VertexBuffer::~VertexBuffer()
		{
			glDeleteBuffers(1, &pVBO);
		}
		void VertexBuffer::Bind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, pVBO);
		}

		void VertexBuffer::Unbind()
		{
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void VertexBuffer::SendDataIntoRegion(unsigned int dataOffset, unsigned int dataSize, const void* data)
		{
			pDataSize += dataSize;

			glBindBuffer(GL_ARRAY_BUFFER, pVBO);
			glBufferSubData(GL_ARRAY_BUFFER, dataOffset, dataSize, data);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
}